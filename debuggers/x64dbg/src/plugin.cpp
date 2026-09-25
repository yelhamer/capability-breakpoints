#include "plugin.h"

#include "datastructure.h"
#include "engine.h"
#include "hook.h"
#include "pluginmain.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/bridgemain.h"
#include "x64dbg-debugger.h"

#include <memory>
#include <regex>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

// Examples: https://github.com/x64dbg/x64dbg/wiki/Plugins
// References:
// - https://help.x64dbg.com/en/latest/developers/plugins/index.html
// - https://x64dbg.com/blog/2016/10/04/architecture-of-x64dbg.html
// - https://x64dbg.com/blog/2016/10/20/threading-model.html
// - https://x64dbg.com/blog/2016/07/30/x64dbg-plugin-sdk.html

std::unordered_map<std::string, std::shared_ptr<Hook>> hooksByApiName;
std::vector<std::shared_ptr<Rule>> rules;

// Helper function to safely read the dynamic C++ type name in MSVC
std::string get_exception_type_name() {
    auto current_ex = std::current_exception();
    if (!current_ex)
        return "Unknown C++ Type";

    try {
        // Re-throw the active exception inside an isolated scope to read its metadata
        std::rethrow_exception(current_ex);
    } catch (const std::exception& e) {
        // Uses standard MSVC RTTI to extract the demangled class name automatically
        return typeid(e).name();
    } catch (...) {
        return "Custom/Raw Non-std::exception Object";
    }
}
static bool cbExampleCommand(int argc, char** argv) {
    //_plugin_logprintf("\n\n\n\ncb callback reached");
    //_plugin_logprintf(" %s\n\n\n\n\n", argv[0]);
    std::cmatch matches;
    std::regex pattern(R"(^([^ ]+) ([^ ]+) (.*)$)");

    if (!std::regex_match(argv[0], matches, pattern)) {
        dputs("Usage: " PLUGIN_COMMAND " <capability name> <capability expression>");
        return false;
    }

    std::string ruleName = matches[2];
    std::string ruleExpression = matches[3];

    try {
        std::shared_ptr<Rule> rule = generateRuleFromExpression(ruleName, ruleExpression);
        rules.push_back(rule);

        for (const auto& [name, nodes] : *(rule->getApiCallNodesByApiName())) {
            auto it = hooksByApiName.find(name);
            if (it != hooksByApiName.end()) {
                // Existing hook for apiname found
                it->second->addCallNodes(nodes);
            } else {
                auto newHook = std::make_shared<Hook>(name);
                newHook->addCallNodes(nodes);
                hooksByApiName.emplace(name, newHook);
            }
        }

        _plugin_logprintf("Added rule %s\n", rule->getName().c_str());

    } catch (const std::exception& exception) {
        _plugin_logprintf("Failed to create hooks. Exception with type: %s\n Message: %s\n",
                          typeid(exception).name(), exception.what());
        return false;
    }

    return true;
}

// Initialize your plugin data here.
bool pluginInit(PLUG_INITSTRUCT* initStruct) {
    dprintf("pluginInit(pluginHandle: %d)\n", pluginHandle);

    // Register callback
    _plugin_registercallback(pluginHandle, CB_BREAKPOINT, Hook::callback);
    _plugin_logprintf("cb callback registered");

    // Prefix of the functions to call here: _plugin_register
    _plugin_registercommand(pluginHandle, PLUGIN_COMMAND, cbExampleCommand, true);
    _plugin_logprintf("cb command registered");

    // Return false to cancel loading the plugin.
    return true;
}

// Deinitialize your plugin data here.
// NOTE: you are responsible for gracefully closing your GUI
// This function is not executed on the GUI thread, so you might need
// to use WaitForSingleObject or similar to wait for everything to close.
void pluginStop() {
    // Prefix of the functions to call here: _plugin_unregister
    dprintf("pluginStop(pluginHandle: %d)\n", pluginHandle);

    // Unregister callback
    _plugin_unregistercallback(pluginHandle, CB_BREAKPOINT);

    // Unregister command
    _plugin_unregistercommand(pluginHandle, PLUGIN_COMMAND);
}

// Do GUI/Menu related things here.
// This code runs on the GUI thread: GetCurrentThreadId() == GuiGetMainThreadId()
// You can get the HWND using GuiGetWindowHandle()
void pluginSetup() {
    // Prefix of the functions to call here: _plugin_menu

    dprintf("pluginSetup(pluginHandle: %d)\n", pluginHandle);
}
