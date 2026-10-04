#ifndef DEBUGGER_INTERFACE_H
#define DEBUGGER_INTERFACE_H

#include "state.h"

#include <any>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace Nodes {
class ApiCallNode;
}; // namespace Nodes

class State;

class DebuggerInterface {
  public:
    virtual void log(const std::string& message) = 0;
    virtual int getThreadId() const = 0;
    virtual std::vector<std::byte> getArgValue(const int argNumber) const = 0;
    virtual std::vector<std::byte> getArgMemAllContents(const int argNumber) const = 0;
    virtual std::vector<std::byte> getArgMemLeadingContents(const int argNumber,
                                                            const size_t size) const = 0;
    virtual std::vector<std::byte> getArgMemTrailingContents(const int argNumber,
                                                             const size_t size) const = 0;
    virtual std::vector<std::byte> getArgMemContentsAtOffset(const int argNumber,
                                                             const size_t offset,
                                                             const size_t size) const = 0;
    virtual void saveApiState(int tid, std::shared_ptr<Nodes::ApiCallNode> apiCallNode) = 0;
    virtual TidToApiNodeToStatePtrListMap getStates() const = 0;
    virtual ~DebuggerInterface() = default;
};

#endif // DEBUGGER_INTERFACE_H