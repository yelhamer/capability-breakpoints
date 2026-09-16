#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <optional>
#include <memory>
#include "include/datastructure.h"
#include "include/debugger.h"
#include "include/dsgen.h"

namespace Nodes {

Node* RootNode::operator[](int index) {
    if (index == 0) {
        return child.get();
    }
    throw std::out_of_range("RootNode has only one child");
}

bool RootNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    // Empty rules are considered to match everything, so if the root has no child, return true.
    bool result = child ? child->evaluate(tid, debugger) : true;
    
    if (result) {
        matchesByTID[tid] = true;
    }

    return result;

}

bool RootNode::getMatchByTID(int tid) {
    return matchesByTID[tid];
}


Node* NotNode::operator[](int index) {
    if (index == 0) {
        return child.get();
    }

    throw std::out_of_range("AndNode has only two children");
}

bool NotNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    // short circuit
    bool result = !child->evaluate(tid, debugger);
    
    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool NotNode::getMatchByTID(int tid) {
    return matchesByTID[tid];
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
    // short circuit
    bool result = true;

    if(!left->evaluate(tid, debugger))
        result = false;
    if(!right->evaluate(tid, debugger))
        result = false;
    
    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool AndNode::getMatchByTID(int tid) {
    return matchesByTID[tid];
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

    // short circuit
    if(left->evaluate(tid, debugger))
        result = true;
    if(right->evaluate(tid, debugger))
        result = true;
    
    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool OrNode::getMatchByTID(int tid) {
    return matchesByTID[tid];
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
    if (!first or !second){
        throw std::logic_error("Attempt to evaluate Then node before its children are set.");
    }

    bool result = false;

    // short circuit
    if(!first->evaluate(tid, debugger))
        result = false;
    result = second->evaluate(tid, debugger);

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

bool ThenNode::getMatchByTID(int tid) {
    return matchesByTID[tid];
}

void ThenNode::setFirst(std::shared_ptr<Node> first) {
    this->first = first;
}

void ThenNode::setSecond(std::shared_ptr<Node> second) {
    this->second = second;
}

PrimaryNode::PrimaryNode(
    Node* parent,
    int argNumber,
    std::string value)
    : parentNode(parent),
    argNumber(argNumber) {
        std::vector<std::byte> result;
        result.reserve(value.size());

        for (unsigned char c : value) {
            result.push_back(static_cast<std::byte>(c));
        }

        this->value = std::move(result);
    }

PrimaryNode::PrimaryNode(
    Node* parent,
    int argNumber,
    long value)
    : parentNode(parent),
    argNumber(argNumber) {
        const std::byte* byte_ptr = reinterpret_cast<const std::byte*>(&value);
        
        // Construct the vector using the pointer range
        std::vector<std::byte> bytes(byte_ptr, byte_ptr + sizeof(value));

        this->value = bytes;
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

bool PrimaryNode::getMatchByTID(int tid) {
    return matchesByTID[tid];
}


bool MemoryNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    bool result;

    switch(searchMode) {
        case MemorySearchMode::Prefix:
            result = evaluatePrefix_(tid, debugger);
        case MemorySearchMode::Suffix:
            result = evaluateSuffix_(tid, debugger);
        case MemorySearchMode::Offset:
            result = evaluateOffset_(tid, debugger);
        case MemorySearchMode::Contains:
            result = evaluateContains_(tid, debugger);
    }

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}


bool MemoryNode::evaluatePrefix_(int tid, std::shared_ptr<DebuggerInterface> debugger) {
std::vector<std::byte> val = debugger->getArgMemLeadingContents(argNumber, patternSize);
return std::equal(val.begin(), val.end(),
                        pattern.begin(), pattern.end(),
                        [](std::byte a, short b) {
                            if(b == -1)
                                return true;
                            return a == static_cast<std::byte>(b);
                        });
}

bool MemoryNode::evaluateSuffix_(int tid, std::shared_ptr<DebuggerInterface> debugger) {
std::vector<std::byte> val = debugger->getArgMemTrailingContents(argNumber, patternSize);
return std::equal(val.begin(), val.end(),
                        pattern.begin(), pattern.end(),
                        [](std::byte a, short b) {
                            if(b == -1)
                                return true;
                            return a == static_cast<std::byte>(b);
                        });
}

bool MemoryNode::evaluateOffset_(int tid, std::shared_ptr<DebuggerInterface> debugger) {
std::vector<std::byte> val = debugger->getArgMemContentsAtOffset(argNumber, offset.value(), patternSize);
return std::equal(val.begin(), val.end(),
                        pattern.begin(), pattern.end(),
                        [](std::byte a, short b) {
                            if(b == -1)
                                return true;
                            return a == static_cast<std::byte>(b);
                        });
}

bool MemoryNode::evaluateContains_(int tid, std::shared_ptr<DebuggerInterface> debugger) {
std::vector<std::byte> val = debugger->getArgMemAllContents(argNumber);
return std::search(val.begin(), val.end(),
                        pattern.begin(), pattern.end(),
                        [](std::byte a, short b) {
                            if(b == -1)
                                return true;
                            return a == static_cast<std::byte>(b);
                        }) != val.end();
}


bool MemoryNode::getMatchByTID(int tid) {
    return matchesByTID[tid];
}


bool ApiCallNode::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    bool result = true;

    for(auto arg : args) {
        // All arguments must bool evaluate to true for the API call to be considered a match
        if(!arg->evaluate(tid, debugger)) {
            return false;
        }
    }

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}

}

bool Rule::getMatchByThread(int tid) const {
    return this->getMatchByThread(tid);
}

bool Rule::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    if (!this->rootNode->evaluate(tid, debugger)) {
        return false;
    }

    this->matchesByTID[tid] = true;

    return true;
}
