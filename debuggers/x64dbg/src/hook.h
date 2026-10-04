#ifndef HOOK
#define HOOK

#include "datastructure.h"
#include "engine.h"
#include "pluginmain.h"
#include "pluginsdk/bridgemain.h"
#include "state.h"
#include "x64dbg-debugger.h"

#include <memory>
#include <string>
#include <unordered_map>


// functions
bool pluginInit(PLUG_INITSTRUCT* initStruct);
void pluginStop();
void pluginSetup();

class Hook {
  public:
    Hook(std::string apiName);

    bool attemptMatch();
    void addCallNodes(const Nodes::ApiNodeList& nodes);
    void removeCallNodes(const Nodes::ApiNodeList& nodes);
    bool isEmpty() {
        return callNodes->empty();
    }
    void removeBreakpoint();
    ~Hook();

    static std::shared_ptr<Nodes::ApiNodeList> getCallNodes();

    static void callback(CBTYPE type, void* callbackInfo);

  private:
    const std::string apiName;
    bool ownsBreakpoint;
    std::shared_ptr<Nodes::ApiNodeList> callNodes;

  protected:
    static std::unordered_map<duint, Hook*> hooksByAddress;
    static std::shared_ptr<x64dbgDebugger> debugger;
};

#endif // HOOK