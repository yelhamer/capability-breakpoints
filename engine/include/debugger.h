#ifndef DEBUGGER_INTERFACE_H
#define DEBUGGER_INTERFACE_H

#include <vector>
#include <string>


class DebuggerInterface {
public:
    virtual void log(const std::string& message) = 0;
    virtual uint getThreadId() const = 0;
    virtual std::string getApiName() const = 0;
    virtual std::vector<std::byte> getArgValue(const int argNumber) const = 0;
    virtual std::vector<std::byte> getArgMemAllContents(const int argNumber) const = 0;
    virtual std::vector<std::byte> getArgMemLeadingContents(const int argNumber, const size_t size) const = 0;
    virtual std::vector<std::byte> getArgMemTrailingContents(const int argNumber, const size_t size) const = 0;
    virtual std::vector<std::byte> getArgMemContentsAtOffset(const int argNumber, const size_t offset, const size_t size) const = 0;
    virtual ~DebuggerInterface() = default;
private:
};

#endif // DEBUGGER_INTERFACE_H