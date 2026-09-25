#include "include/datastructure.h"

#include "include/debugger.h"

#include <algorithm>
#include <cstddef>
#include <limits>
#include <memory>
#include <optional>
#include <stdexcept>
#include <string>
#include <vector>

namespace Nodes {

Node* RootNode::operator[](int index) {
    if (index == 0) {
        return child.get();
    }
    throw std::out_of_range("RootNode has only one child");
}

bool RootNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    // Empty rules are considered to match everything, so if the root has no child, return true.
    bool result = child ? child->getMatchByTID(tid) : true;

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool RootNode::getMatchByTID(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

Node* NotNode::operator[](int index) {
    if (index == 0) {
        return child.get();
    }

    throw std::out_of_range("AndNode has only two children");
}

bool NotNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    bool result = !child->getMatchByTID(tid);

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool NotNode::getMatchByTID(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

Node* AndNode::operator[](int index) {
    if (index == 0) {
        return left.get();
    } else if (index == 1) {
        return right.get();
    }
    throw std::out_of_range("AndNode has only two children");
}

bool AndNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    bool result = true;

    if (!left->getMatchByTID(tid))
        result = false;
    if (!right->getMatchByTID(tid))
        result = false;

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool AndNode::getMatchByTID(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

Node* OrNode::operator[](int index) {
    if (index == 0) {
        return left.get();
    } else if (index == 1) {
        return right.get();
    }
    throw std::out_of_range("OrNode has only two children");
}

bool OrNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    bool result = false;

    if (left->getMatchByTID(tid))
        result = true;
    if (right->getMatchByTID(tid))
        result = true;

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool OrNode::getMatchByTID(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

Node* ThenNode::operator[](int index) {
    if (index == 0) {
        return first.get();
    } else if (index == 1) {
        return second.get();
    }
    throw std::out_of_range("ThenNode has only two children");
}

bool ThenNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    if (!first || !second) {
        throw std::logic_error("Attempt to evaluate Then node before its children are set.");
    }

    bool result = false;

    if (!first->getMatchByTID(tid))
        result = false;
    result = second->getMatchByTID(tid);

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool ThenNode::getMatchByTID(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

void ThenNode::setFirst(std::shared_ptr<Node> first) {
    this->first = first;
}

void ThenNode::setSecond(std::shared_ptr<Node> second) {
    this->second = second;
}

PrimaryNode::PrimaryNode(Node* parent, int argNumber, std::string value)
    : parentNode(parent), argNumber(argNumber) {
    std::vector<std::byte> result;
    result.reserve(value.size());

    for (unsigned char c : value) {
        result.push_back(static_cast<std::byte>(c));
    }

    this->value = std::move(result);
}

PrimaryNode::PrimaryNode(Node* parent, int argNumber, long long value)
    : parentNode(parent), argNumber(argNumber) {
    std::byte* byte_ptr;
    if (sizeof(void*) == 4) {
        long val = static_cast<long>(value);
        byte_ptr = reinterpret_cast<std::byte*>(&val);
        // Construct the vector using the pointer range
        std::vector<std::byte> bytes(byte_ptr, byte_ptr + sizeof(val));
        this->value = bytes;
    } else {
        byte_ptr = reinterpret_cast<std::byte*>(&value);
        // Construct the vector using the pointer range
        std::vector<std::byte> bytes(byte_ptr, byte_ptr + sizeof(value));
        this->value = bytes;
    }
}

bool PrimaryNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    // Placeholder for actual evaluation logic
    // For now, just return true to indicate a successful match
    bool result = value == debugger->getArgValue(argNumber);

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool PrimaryNode::getMatchByTID(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

bool MemoryNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    bool result;

    switch (searchMode) {
    case MemorySearchMode::Prefix:
        result = evaluatePrefix_(tid, debugger);
        break;
    case MemorySearchMode::Suffix:
        result = evaluateSuffix_(tid, debugger);
        break;
    case MemorySearchMode::Offset:
        result = evaluateOffset_(tid, debugger);
        break;
    case MemorySearchMode::Contains:
        result = evaluateContains_(tid, debugger);
        break;
    }

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool MemoryNode::evaluatePrefix_(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    std::vector<std::byte> val = debugger->getArgMemLeadingContents(argNumber, patternSize);
    return std::equal(val.begin(), val.end(), pattern.begin(), pattern.end(),
                      [](std::byte a, short b) {
                          if (b == -1)
                              return true;
                          return a == static_cast<std::byte>(b);
                      });
}

bool MemoryNode::evaluateSuffix_(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    std::vector<std::byte> val = debugger->getArgMemTrailingContents(argNumber, patternSize);
    return std::equal(val.begin(), val.end(), pattern.begin(), pattern.end(),
                      [](std::byte a, short b) {
                          if (b == -1)
                              return true;
                          return a == static_cast<std::byte>(b);
                      });
}

bool MemoryNode::evaluateOffset_(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    std::vector<std::byte> val =
        debugger->getArgMemContentsAtOffset(argNumber, offset.value(), patternSize);
    return std::equal(val.begin(), val.end(), pattern.begin(), pattern.end(),
                      [](std::byte a, short b) {
                          if (b == -1)
                              return true;
                          return a == static_cast<std::byte>(b);
                      });
}

bool MemoryNode::evaluateContains_(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    std::vector<std::byte> val = debugger->getArgMemAllContents(argNumber);
    return std::search(val.begin(), val.end(), pattern.begin(), pattern.end(),
                       [](std::byte a, short b) {
                           if (b == -1)
                               return true;
                           return a == static_cast<std::byte>(b);
                       }) != val.end();
}

bool MemoryNode::getMatchByTID(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

bool ApiCallNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    bool result = true;

    for (auto arg : args) {
        // All arguments must bool evaluate to true for the API call to be considered a match
        if (!arg->evaluate(tid, debugger)) {
            return false;
        }
    }

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool ApiCallNode::getMatchByTID(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

} // namespace Nodes

bool Rule::getMatchByThread(int tid) const {
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && it->second;
}

bool Rule::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    if (!this->rootNode->evaluate(tid, debugger)) {
        return false;
    }

    this->matchesByTID[tid] = true;

    return true;
}
