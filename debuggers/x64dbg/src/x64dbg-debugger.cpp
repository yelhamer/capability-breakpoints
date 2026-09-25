#include "x64dbg-debugger.h"

#include "pluginsdk/_plugins.h"

#include <string>

void x64dbgDebugger::log(const std::string& message) {
    _plugin_logprintf("[%s]: %s\n", PLUGIN_NAME, message.c_str());
}

int x64dbgDebugger::getThreadId() const {
    return static_cast<int>(DbgEval("tid()"));
}

duint x64dbgDebugger::getApiAddr(std::string apiName) {
    return DbgEval(apiName.c_str());
}

void x64dbgDebugger::setBreakpoint(duint address) {
    constexpr int pad_width = sizeof(void*) * 2;
    char addr_buf[32];

    if constexpr (pad_width == 16) {
        sprintf_s(addr_buf, "0x%016llx", (unsigned long long)address); // 64-bit padding
    } else {
        sprintf_s(addr_buf, "0x%08llx", (unsigned long long)address); // 32-bit padding
    }

    std::string command = "bp " + std::string(addr_buf) + ", \"hook-installed bp\"";
    DbgCmdExecDirect(command.c_str());
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