#ifndef X64DBG
#define X64DBG

// clang-format: off
#include <cstddef>
#include <cstdio>
#include <optional>
#include <string>
#include <tuple>
#include <vector>
#include <windows.h>

// clang-format: on

#include "debugger.h"
#include "pluginsdk/bridgemain.h"

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

    std::vector<std::byte> getArgValue(const int argNumber) const override;

    std::vector<std::byte> getArgMemAllContents(const int argNumber) const override;

    std::vector<std::byte> getArgMemLeadingContents(const int argNumber,
                                                    const size_t size) const override;

    std::vector<std::byte> getArgMemTrailingContents(const int argNumber,
                                                     const size_t size) const override;

    std::vector<std::byte> getArgMemContentsAtOffset(const int argNumber, const size_t offset,
                                                     const size_t size) const override;
};

#endif // X64DBG