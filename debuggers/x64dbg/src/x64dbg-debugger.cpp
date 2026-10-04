#include "x64dbg-debugger.h"

#include "datastructure.h"
#include "pluginsdk/_dbgfunctions.h"
#include "pluginsdk/_plugins.h"
#include "pluginsdk/bridgemain.h"

#include <cstddef>
#include <iomanip>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

void x64dbgDebugger::log(const std::string& message) {
    _plugin_logprintf("[%s]: %s\n", PLUGIN_NAME, message.c_str());
}

int x64dbgDebugger::getThreadId() const {
    return static_cast<int>(DbgEval("tid()"));
}

duint x64dbgDebugger::getApiAddr(std::string apiName) {
    return DbgEval(apiName.c_str());
}

std::vector<breakpoint> x64dbgDebugger::getBreakpointsAddrName() {
    std::vector<breakpoint> breakpoints{};
    BPMAP map{};

    if (DbgGetBpList(bp_normal, &map)) {
        breakpoints.reserve(map.count);
        for (int i = 0; i < map.count; ++i) {
            const BRIDGEBP& bp = map.bp[i];
            breakpoints.push_back({bp.addr, bp.name});
        }

        BridgeFree(map.bp);
    }

    return breakpoints;
}

std::optional<breakpoint> x64dbgDebugger::getBreakpointsAddrName(duint address) {
    BPMAP map{};

    if (DbgGetBpList(bp_normal, &map)) {
        for (int i = 0; i < map.count; ++i) {
            const BRIDGEBP& bp = map.bp[i];
            if (bp.addr == address) {
                breakpoint ret{address, bp.name};
                BridgeFree(map.bp);
                return ret;
            }
        }

        BridgeFree(map.bp);
    }

    return std::nullopt;
}

bool x64dbgDebugger::resumeExecution() {
    return DbgCmdExecDirect("run");
}

bool x64dbgDebugger::checkForBreakpoint(duint address) {
    return getBreakpointsAddrName(address).has_value();
}

bool x64dbgDebugger::installTag(duint address) {
    const auto ret = getBreakpointsAddrName(address);
    std::string command;

    if (!ret.has_value()) {
        // bp does not exist
        return false;
    }

    const auto& [addr, name] = ret.value();
    command = "bpname " + formatAddress(address) + ", " + name + BPTAG;
    return DbgCmdExecDirect(command.c_str());
}

std::string x64dbgDebugger::formatAddress(duint address) {
    std::stringstream ss;
    ss << "0x" << std::setfill('0') << std::hex;

    // Evaluated at compile time in C++17
    if constexpr (sizeof(void*) == 8) {
        ss << std::setw(16); // 64-bit padding
    } else {
        ss << std::setw(8); // 32-bit padding
    }

    ss << (unsigned long long)address;
    return ss.str();
}

bool x64dbgDebugger::setBreakpoint(duint address) {
    constexpr int pad_width = sizeof(void*) * 2;
    char addr_buf[32];
    bool ownsBreakpoint = true;

    if constexpr (pad_width == 16) {
        sprintf_s(addr_buf, "0x%016llx", (unsigned long long)address); // 64-bit padding
    } else {
        sprintf_s(addr_buf, "0x%08llx", (unsigned long long)address); // 32-bit padding
    }

    std::string command = "bp " + std::string(addr_buf) + ", " + BPNAME;

    const auto ret = getBreakpointsAddrName(address);
    if (ret.has_value()) {
        // bp already exists
        const auto& [addr, name] = ret.value();
        ownsBreakpoint = false;
        command = "bpname " + std::string(addr_buf) + ", " + name + BPTAG;
    }

    return DbgCmdExecDirect(command.c_str());
}

bool x64dbgDebugger::removeTag(duint address) {
    constexpr int pad_width = sizeof(void*) * 2;
    char addr_buf[32];

    if constexpr (pad_width == 16) {
        sprintf_s(addr_buf, "0x%016llx", (unsigned long long)address); // 64-bit padding
    } else {
        sprintf_s(addr_buf, "0x%08llx", (unsigned long long)address); // 32-bit padding
    }

    std::string command;
    for (auto [addr, name] : this->getBreakpointsAddrName()) {
        if (addr == address) {
            std::string newName = name.substr(0, name.size() - BPTAGSZ);
            command = "bpname " + std::string(addr_buf) + ", " + newName;
        }
    }

    return DbgCmdExecDirect(command.c_str());
}

bool x64dbgDebugger::removeBreakpoint(duint address) {
    constexpr int pad_width = sizeof(void*) * 2;
    char addr_buf[32];

    if constexpr (pad_width == 16) {
        sprintf_s(addr_buf, "0x%016llx", (unsigned long long)address); // 64-bit padding
    } else {
        sprintf_s(addr_buf, "0x%08llx", (unsigned long long)address); // 32-bit padding
    }

    std::string command = "bc " + std::string(addr_buf);
    return DbgCmdExecDirect(command.c_str());
}

std::vector<std::byte> x64dbgDebugger::getArgValue(const int argNumber) const {
    std::string expression = "arg.get(" + std::to_string(argNumber - 1) + ")";
    const duint value = DbgEval(expression.c_str());
    const std::byte* byte_ptr = reinterpret_cast<const std::byte*>(&value);

    // Construct the vector using the pointer range
    std::vector<std::byte> bytes(byte_ptr, byte_ptr + sizeof(value));

    return bytes;
}

std::vector<std::byte> x64dbgDebugger::getArgMemAllContents(const int argNumber) const {
    std::string expression = "arg.get(" + std::to_string(argNumber - 1) + ")";
    duint address = DbgEval(expression.c_str());

    size_t regionSize = 0;
    duint regionBase = DbgMemFindBaseAddr(address, &regionSize);

    std::vector<std::byte> buf(regionSize);
    DbgMemRead(regionBase, reinterpret_cast<unsigned char*>(buf.data()), regionSize);

    return buf;
}

std::vector<std::byte> x64dbgDebugger::getArgMemLeadingContents(const int argNumber,
                                                                const size_t size) const {
    std::string expression = "arg.get(" + std::to_string(argNumber - 1) + ")";
    duint address = DbgEval(expression.c_str());

    std::vector<std::byte> buf(size);
    DbgMemRead(address, reinterpret_cast<unsigned char*>(buf.data()), size);

    return buf;
}

std::vector<std::byte> x64dbgDebugger::getArgMemTrailingContents(const int argNumber,
                                                                 const size_t size) const {
    std::string expression = "arg.get(" + std::to_string(argNumber - 1) + ")";
    duint address = DbgEval(expression.c_str());

    size_t regionSize = 0;
    duint regionBase = DbgMemFindBaseAddr(address, &regionSize);

    std::vector<std::byte> buf(size);
    if (size <= regionSize) {
        DbgMemRead(regionBase + regionSize - size, reinterpret_cast<unsigned char*>(buf.data()),
                   size);
    } else {
        DbgMemRead(regionBase, reinterpret_cast<unsigned char*>(buf.data()), size);
    }

    return buf;
}

std::vector<std::byte> x64dbgDebugger::getArgMemContentsAtOffset(const int argNumber,
                                                                 const size_t offset,
                                                                 const size_t size) const {
    std::string expression = "arg.get(" + std::to_string(argNumber - 1) + ")";
    duint address = DbgEval(expression.c_str());

    std::vector<std::byte> buf(size);
    DbgMemRead(address + offset, reinterpret_cast<unsigned char*>(buf.data()), size);

    return buf;
}

std::shared_ptr<Arguments<duint>> x64dbgDebugger::getArguments(int numberOfArgs) {
    auto args = std::make_shared<Arguments<duint>>();

    for (int i = 0; i < numberOfArgs; i++) {
        args->addArgument(std::make_shared<ValueArgument>(getArgValue(i)));
    }

    return args;
}

std::shared_ptr<StackTrace<duint>> x64dbgDebugger::getStackTrace() {
    auto stackTrace = std::make_shared<StackTrace<duint>>();

    const auto* funcs = DbgFunctions();

    if (!funcs) {
        _plugin_logprintf("[PluginTemplate] DbgFunctions() == nullptr\n");
        return stackTrace;
    }

    if (!funcs->GetCallStackEx) {
        _plugin_logprintf("[PluginTemplate] GetCallStackEx == nullptr\n");
        return stackTrace;
    }

    DBGCALLSTACK callstack{};

    funcs->GetCallStackEx(&callstack, false);

    if (!callstack.entries || callstack.total <= 0) {
        if (callstack.entries)
            BridgeFree(callstack.entries);

        return stackTrace;
    }

    stackTrace->reserveFrames(callstack.total);

    for (int i = 0; i < callstack.total; ++i) {
        const auto& entry = callstack.entries[i];

        _plugin_logprintf("[PluginTemplate] frame[%d] addr=%p from=%p to=%p comment=%s\n", i,
                          reinterpret_cast<void*>(entry.addr), reinterpret_cast<void*>(entry.from),
                          reinterpret_cast<void*>(entry.to), entry.comment);

        stackTrace->addFrame(
            std::make_shared<Frame<duint>>(entry.addr, entry.from, entry.to, entry.comment));
    }

    BridgeFree(callstack.entries);

    return stackTrace;
}

void x64dbgDebugger::saveApiState(int tid, std::shared_ptr<Nodes::ApiCallNode> apiCallNode) {
    int numberOfArgs = apiCallNode->getNumberOfArgs();
    auto args = getArguments(numberOfArgs - 1);
    auto stackTrace = getStackTrace();

    auto state =
        std::dynamic_pointer_cast<State>(std::make_shared<TypedState<duint>>(args, stackTrace));
    this->allStatesByTIDandApiCallNode[tid][apiCallNode].push_back(state);

    return;
}
