#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <optional>
#include <memory>
#include "debugger.h"


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

    Node* operator[](int index) override;

    bool evaluate(DebuggerInterface* debugger) override;

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

    Node* operator[](int index) override;

    bool evaluate(DebuggerInterface* debugger) override;

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

    Node* operator[](int index) override;

    bool evaluate(DebuggerInterface* debugger) override;

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

    Node* operator[](int index) override;

    bool evaluate(DebuggerInterface* debugger) override;

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

    Node* operator[](int index) override;

    bool evaluate(DebuggerInterface* debugger) override;

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
        std::string value);

    PrimaryNode(
        Node* parent,
        int argNumber,
        long value);

    Node* parent() override {
        return parentNode;
    }

    Node* operator[](int index) override {
        // PrimaryNode is a leaf node.
        return nullptr;
    }

    bool evaluate(DebuggerInterface* debugger) override;

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

    bool evaluate(DebuggerInterface* debugger) override;

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

    bool evaluate(DebuggerInterface* debugger) override;

private:
    Node* parentNode;
    std::string apiName;
    std::vector<std::shared_ptr<Node>> args;
};

}