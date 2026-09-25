#include "hook.h"

#include "datastructure.h"
#include "engine.h"
#include "pluginsdk/_plugins.h"
#include "x64dbg-debugger.h"

#include <memory>

Hook::Hook(std::string apiName) : apiName(apiName) {
    this->callNodes = std::make_shared<Nodes::ApiNodeList>();

    duint address = debugger->getApiAddr(apiName);
    hooksByAddress[address] = this;
    _plugin_logprintf("Installed new hook for API with name: %s\tat address: %p\n", apiName.c_str(),
                      address);

    // Set breakpoint if not already set
    debugger->setBreakpoint(address);
}

void Hook::attemptMatch() {
    int tid = this->debugger->getThreadId();

    for (auto& node : *this->callNodes) {
        auto rule = attemptMatchFromApiNode(tid, this->debugger, node.get());

        if (rule) {
            std::string output{"[+] matched rule: " + rule->getName() + " with expression: \n\t\t" +
                               rule->getExpression() + "\n"};
            this->debugger->log(output);
        }
    }

    return;
}

void Hook::addCallNodes(const Nodes::ApiNodeList& nodes) {
    this->callNodes->insert(this->callNodes->end(), nodes.begin(), nodes.end());

    return;
}

void Hook::callback(CBTYPE type, void* callbackInfo) {
    if (type != CB_BREAKPOINT || callbackInfo == nullptr)
        return;

    auto* info = static_cast<PLUG_CB_BREAKPOINT*>(callbackInfo);
    if (info->breakpoint == nullptr)
        return;

    auto it = hooksByAddress.find(info->breakpoint->addr);
    if (it == hooksByAddress.end())
        return;
    Hook* hook = it->second;

    hook->attemptMatch();
    return;
}

std::unordered_map<duint, Hook*> Hook::hooksByAddress;
std::shared_ptr<x64dbgDebugger> Hook::debugger = std::make_shared<x64dbgDebugger>();