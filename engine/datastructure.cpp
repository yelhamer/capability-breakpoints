#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <optional>
#include <memory>
#include "include/debugger.h"


enum class MemorySearchMode{
    Prefix,
    Suffix,
    Offset,
    Contains,
};


namespace Nodes {


class Node {
public:
    virtual Node* parent() = 0;
    virtual Node* operator[](int index) = 0;
    virtual bool evaluate(DebuggerInterface* debugger) = 0;
    virtual ~Node() = default;
};


class RootNode : public Node {
public:
    RootNode(std::shared_ptr<Node> child) : child(child) {}
    
    Node* parent() override {
        return nullptr;
    }

    Node* operator[](int index) override {
        if (index == 0) {
            return child.get();
        }
        throw std::out_of_range("RootNode has only one child");
    }

    bool evaluate(DebuggerInterface* debugger) override {
        // Empty rules are considered to match everything, so if the root has no child, return true.
        return child ? child->evaluate(debugger) : true;
    }

private:
    // Root nodes have one child only
    std::shared_ptr<Node> child;
};


class NotNode : public Node {
public:
    NotNode(
        Node* parent,
        std::shared_ptr<Node> child)
        : parentNode(parent),
        child(child) {}
    
    Node* parent() override {
        return parentNode;
    }

    Node* operator[](int index) override {
        if (index == 0) {
            return child.get();
        }

        throw std::out_of_range("AndNode has only two children");
    }

    bool evaluate(DebuggerInterface* debugger) override {
        // short circuit
        return !child->evaluate(debugger);
    }

private:
    Node* parentNode;
    std::shared_ptr<Node> child;
};


class AndNode : public Node {
public:
    AndNode(
        Node* parent,
        std::shared_ptr<Node> left,
        std::shared_ptr<Node> right)
        : parentNode(parent),
        left(left),
        right(right) {}

    
    Node* parent() override {
        return parentNode;
    }

    Node* operator[](int index) override {
        if (index == 0) {
            return left.get();
        } else if (index == 1) {
            return right.get();
        }
        throw std::out_of_range("AndNode has only two children");
    }

    bool evaluate(DebuggerInterface* debugger) override {
        // short circuit
        if(!left->evaluate(debugger))
            return false;
        if(!right->evaluate(debugger))
            return false;
        return true;
    }

private:
    Node* parentNode;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};


class OrNode : public Node {
public:
    OrNode(
        Node* parent,
        std::shared_ptr<Node> left,
        std::shared_ptr<Node> right)
        : parentNode(parent),
        left(left),
        right(right) {}

    Node* parent() override {
        return parentNode;
    }

    Node* operator[](int index) override {
        if (index == 0) {
            return left.get();
        } else if (index == 1) {
            return right.get();
        }
        throw std::out_of_range("OrNode has only two children");
    }

    bool evaluate(DebuggerInterface* debugger) override {
        // short circuit
        if(left->evaluate(debugger))
            return true;
        if(right->evaluate(debugger))
            return true;
        return false;
    }

private:
    Node* parentNode;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
};


class ThenNode : public Node {
public:
    ThenNode(
        Node* parent,
        std::shared_ptr<Node> first,
        std::shared_ptr<Node> second)
        : parentNode(parent),
        first(first),
        second(second) {}


    Node* parent() override {
        return parentNode;
    }

    Node* operator[](int index) override {
        if (index == 0) {
            return first.get();
        } else if (index == 1) {
            return second.get();
        }
        throw std::out_of_range("ThenNode has only two children");
    }

    bool evaluate(DebuggerInterface* debugger) override {
        // short circuit
        if(!first->evaluate(debugger))
            return false;
        return second->evaluate(debugger);
    }

private:
    Node* parentNode;
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> second;
};


class PrimaryNode : public Node {
public:
    PrimaryNode(
        Node* parent,
        int argNumber,
        std::vector<std::byte> value)
        : parentNode(parent),
        argNumber(argNumber),
        value(value) {}

    PrimaryNode(
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

    PrimaryNode(
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

    Node* parent() override {
        return parentNode;
    }

    Node* operator[](int index) override {
        // PrimaryNode is a leaf node.
        return nullptr;
    }

    bool evaluate(DebuggerInterface* debugger) override {
        // Placeholder for actual evaluation logic
        // For now, just return true to indicate a successful match
        return (value == debugger->getArgValue(argNumber));
    }

private:
    Node* parentNode;
    int argNumber;
    std::vector<std::byte> value;
};


class MemoryNode : public Node {
public:
    MemoryNode(
        Node* parent,
        int argNumber,
        const std::vector<short>& pattern,
        std::optional<uint64_t> offset,
        MemorySearchMode searchMode)
        : parentNode(parent),
          argNumber(argNumber),
          pattern(pattern),
          patternSize(pattern.size()),
          searchMode(searchMode),
          offset(offset) {}

    Node* parent() override {
        return parentNode;
    }

    Node* operator[](int index) override {
        // MemoryNode is a leaf node.
        return nullptr;
    }

    bool evaluate(DebuggerInterface* debugger) override {
        switch(searchMode) {
            case MemorySearchMode::Prefix:
                return evaluatePrefix_(debugger);
            case MemorySearchMode::Suffix:
                return evaluateSuffix_(debugger);
            case MemorySearchMode::Offset:
                return evaluateOffset_(debugger);
            case MemorySearchMode::Contains:
                return evaluateContains_(debugger);
        }
    }

private:
    Node* parentNode;
    const uint64_t argNumber;
    const std::vector<short> pattern;
    const size_t patternSize; // pattern size
    const std::optional<uint64_t> offset;
    const MemorySearchMode searchMode;
    bool evaluatePrefix_(DebuggerInterface*);
    bool evaluateSuffix_(DebuggerInterface*);
    bool evaluateOffset_(DebuggerInterface*);
    bool evaluateContains_(DebuggerInterface*);
};

bool MemoryNode::evaluatePrefix_(DebuggerInterface* debugger) {
    std::vector<std::byte> val = debugger->getArgMemLeadingContents(argNumber, patternSize);
    return std::equal(val.begin(), val.end(),
                            pattern.begin(), pattern.end(),
                            [](std::byte a, short b) {
                                if(b == -1)
                                    return true;
                                return a == static_cast<std::byte>(b);
                            });
}

bool MemoryNode::evaluateSuffix_(DebuggerInterface* debugger) {
    std::vector<std::byte> val = debugger->getArgMemTrailingContents(argNumber, patternSize);
    return std::equal(val.begin(), val.end(),
                            pattern.begin(), pattern.end(),
                            [](std::byte a, short b) {
                                if(b == -1)
                                    return true;
                                return a == static_cast<std::byte>(b);
                            });
}

bool MemoryNode::evaluateOffset_(DebuggerInterface* debugger) {
    std::vector<std::byte> val = debugger->getArgMemContentsAtOffset(argNumber, offset.value(), patternSize);
    return std::equal(val.begin(), val.end(),
                            pattern.begin(), pattern.end(),
                            [](std::byte a, short b) {
                                if(b == -1)
                                    return true;
                                return a == static_cast<std::byte>(b);
                            });
}

bool MemoryNode::evaluateContains_(DebuggerInterface* debugger) {
    std::vector<std::byte> val = debugger->getArgMemAllContents(argNumber);
    return std::search(val.begin(), val.end(),
                            pattern.begin(), pattern.end(),
                            [](std::byte a, short b) {
                                if(b == -1)
                                    return true;
                                return a == static_cast<std::byte>(b);
                            }) != val.end();
}





class ApiCallNode : public Node {
public:
    ApiCallNode(
        Node* parent,
        std::string apiName,
        std::vector<std::shared_ptr<Node>> args
    ) 
    : parentNode(parent),
      apiName(apiName),
      args(args) {};

    Node* parent() override {
        return parentNode;
    }

    Node* operator[](int index) override {
        // ApiCallNode is a leaf node.
        return nullptr;
    }

    bool evaluate(DebuggerInterface* debugger) override {
        for(auto arg : args) {
            // All arguments must evaluate to true for the API call to be considered a match
            if(!arg->evaluate(debugger)) {
                return false;
            }
        }
        return true;
    }

private:
    Node* parentNode;
    std::string apiName;
    std::vector<std::shared_ptr<Node>> args;
};

}