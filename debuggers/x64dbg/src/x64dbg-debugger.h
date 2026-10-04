#ifndef X64DBG
#define X64DBG

// clang-format: off
#include <cstddef>
#include <cstdio>
#include <memory>
#include <optional>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <windows.h>

// clang-format: on

#include "datastructure.h"
#include "debugger.h"
#include "pluginsdk/bridgemain.h"
#include "state.h"

#include <cstddef>
#include <vector>

#define BPNAME "\"hook-installed bp\""
#define BPTAG (std::string(" (") + BPNAME + ")")
#define BPTAGSZ (BPTAG).size()

using breakpoint = std::tuple<duint, std::string>;

class x64dbgDebugger : public DebuggerInterface {
  public:
    void log(const std::string& message) override;

    int getThreadId() const override;

    duint getApiAddr(std::string apiName);

    bool checkForBreakpoint(duint address);

    std::optional<breakpoint> getBreakpointsAddrName(duint address);
    std::vector<breakpoint> getBreakpointsAddrName();
    bool resumeExecution();
    bool setBreakpoint(duint address);
    bool removeBreakpoint(duint address);
    std::string formatAddress(duint address);

    bool installTag(duint address);
    bool removeTag(duint address);
    std::shared_ptr<Arguments<duint>> getArguments(int numberOfArgs);
    std::shared_ptr<StackTrace<duint>> getStackTrace();
    std::vector<std::byte> getArgValue(const int argNumber) const override;

    std::vector<std::byte> getArgMemAllContents(const int argNumber) const override;

    std::vector<std::byte> getArgMemLeadingContents(const int argNumber,
                                                    const size_t size) const override;

    std::vector<std::byte> getArgMemTrailingContents(const int argNumber,
                                                     const size_t size) const override;

    std::vector<std::byte> getArgMemContentsAtOffset(const int argNumber, const size_t offset,
                                                     const size_t size) const override;

    void saveApiState(int tid, std::shared_ptr<Nodes::ApiCallNode> apiCallNode) override;

    TidToApiNodeToStatePtrListMap getStates() const override {
        return allStatesByTIDandApiCallNode;
    }

  private:
    TidToApiNodeToStatePtrListMap allStatesByTIDandApiCallNode;
};

#endif // X64DBG