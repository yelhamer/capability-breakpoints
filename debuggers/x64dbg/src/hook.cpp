#include "hook.h"

#include "datastructure.h"
#include "engine.h"
#include "pluginsdk/_plugins.h"
#include "state.h"
#include "x64dbg-debugger.h"

#include <memory>

Hook::Hook(std::string apiName) : apiName(apiName) {
    this->callNodes = std::make_shared<Nodes::ApiNodeList>();

    duint address = debugger->getApiAddr(apiName);
    hooksByAddress[address] = this;
    _plugin_logprintf("Installed new hook for API with name: %s\tat address: %p\n", apiName.c_str(),
                      address);

    if (debugger->checkForBreakpoint(address)) {
        // bp exists already
        if (!debugger->installTag(address)) {
            debugger->log("failed to install breakpoint tag " + apiName + "at address" +
                          debugger->formatAddress(address));
        }

        this->ownsBreakpoint = false;
    } else {
        // bp does not exist, create it
        if (!debugger->setBreakpoint(address)) {
            debugger->log("failed to install breakpoint for " + apiName + "at address" +
                          debugger->formatAddress(address));

            this->ownsBreakpoint = false;
        } else {
            this->ownsBreakpoint = true;
        }
    }
}

bool Hook::attemptMatch() {
    bool matched = false;
    int tid = this->debugger->getThreadId();

    for (auto& node : *this->callNodes) {
        std::shared_ptr<Match> match = attemptMatchFromApiNode(tid, this->debugger, node.get());

        if (match) {
            matched = true;
            std::string output{"[+] matched rule: " + match->getRule()->getName() +
                               " with expression: \n\t\t" + match->getRule()->getExpression() +
                               "\n"};
            this->debugger->log(output);
        }
    }

    return matched;
}

Hook::~Hook() {
    const duint address = debugger->getApiAddr(apiName);

    if (ownsBreakpoint) {
        // Remove breakpoint installed by the Hook
        if (!debugger->removeBreakpoint(address)) {
            debugger->log("failed to remove breakpoint for " + apiName + "at address" +
                          debugger->formatAddress(address));
        }
    } else {
        // Remove plugin tag
        if (!debugger->removeTag(address)) {
            debugger->log("failed to remove breakpoint tag for " + apiName + "at address" +
                          debugger->formatAddress(address));
        }
    }

    // Remove Hook non-shared pointer from hooksByAddress
    hooksByAddress.erase(address);
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

    // did not match and hook owns breakpoint
    if (!hook->attemptMatch() && hook->ownsBreakpoint) {
        if (!hook->debugger->resumeExecution()) {
            debugger->log("failed to resume execution at hook for " + hook->apiName +
                          " with address " + debugger->formatAddress(info->breakpoint->addr));
        }
    }

    return;
}

void Hook::removeCallNodes(const Nodes::ApiNodeList& nodes) {
    for (const auto& node : nodes) {
        callNodes->erase(
            std::remove_if(callNodes->begin(), callNodes->end(),
                           [&node](const Nodes::ApiNodePtr& existing) { return existing == node; }),
            callNodes->end());
    }

    return;
}
