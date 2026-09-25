#ifndef X64DBG
#define X64DBG

// clang-format: off
#include <cstddef>
#include <cstdio>
#include <string>
#include <vector>
#include <windows.h>

// clang-format: on

#include "debugger.h"
#include "pluginsdk/bridgemain.h"

#include <cstddef>
#include <vector>

class x64dbgDebugger : public DebuggerInterface {
  public:
    void log(const std::string& message) override;

    int getThreadId() const override;

    duint getApiAddr(std::string apiName);

    void setBreakpoint(duint address);

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