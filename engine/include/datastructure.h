#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H

#include "debugger.h"

#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

class Rule; // Forward declaration

enum class MemorySearchMode {
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
    virtual void setParent(Node* parent_) = 0;
    virtual bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) = 0;
    virtual bool getMatchByTID(int tid) const = 0;
    virtual ~Node() = default;
};

class RootNode : public Node {
  public:
    RootNode(std::shared_ptr<Node> child, Rule* rule) : child(child), rule(rule) {}

    Rule* getRule() {
        return rule;
    }
    void setParent(Node* parent_) override {
        return;
    }

    void setRule(Rule* rule_) {
        this->rule = rule_;
    }

    Node* parent() override {
        // Returns false by default.
        // Can return true in the future, for rules that reference other rules.
        return nullptr;
    }

    Node* operator[](int index) override;

    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) override;

    bool getMatchByTID(int tid) const override;

  private:
    Rule* rule;
    // Root nodes have one child only
    std::shared_ptr<Node> child;
    std::unordered_map<int, bool> matchesByTID;
};

class NotNode : public Node {
  public:
    NotNode(Node* parent, std::shared_ptr<Node> child) : parentNode(parent), child(child) {}

    Node* parent() override {
        return parentNode;
    }

    void setParent(Node* parent_) override {
        this->parentNode = parent_;
    }

    Node* operator[](int index) override;

    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) override;

    bool getMatchByTID(int tid) const override;

  private:
    Node* parentNode;
    std::shared_ptr<Node> child;
    std::unordered_map<int, bool> matchesByTID;
};

class AndNode : public Node {
  public:
    AndNode(Node* parent, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
        : parentNode(parent), left(left), right(right) {}

    Node* parent() override {
        return parentNode;
    }

    void setParent(Node* parent_) override {
        this->parentNode = parent_;
    }

    Node* operator[](int index) override;

    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) override;

    bool getMatchByTID(int tid) const override;

  private:
    Node* parentNode;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::unordered_map<int, bool> matchesByTID;
};

class OrNode : public Node {
  public:
    OrNode(Node* parent, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
        : parentNode(parent), left(left), right(right) {}

    Node* parent() override {
        return parentNode;
    }

    void setParent(Node* parent_) override {
        this->parentNode = parent_;
    }

    Node* operator[](int index) override;

    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) override;

    bool getMatchByTID(int tid) const override;

  private:
    Node* parentNode;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::unordered_map<int, bool> matchesByTID;
};

class ThenNode : public Node {
  public:
    ThenNode(Node* parent) : parentNode(parent), first(nullptr), second(nullptr) {}

    ThenNode(Node* parent, std::shared_ptr<Node> first, std::shared_ptr<Node> second)
        : parentNode(parent), first(first), second(second) {}

    Node* parent() override {
        return parentNode;
    }

    void setParent(Node* parent_) override {
        this->parentNode = parent_;
    }

    Node* operator[](int index) override;

    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) override;

    bool getMatchByTID(int tid) const override;

    void setFirst(std::shared_ptr<Node> first);

    void setSecond(std::shared_ptr<Node> second);

  private:
    Node* parentNode;
    std::shared_ptr<Node> first;
    std::shared_ptr<Node> second;
    std::unordered_map<int, bool> matchesByTID;
};

class PrimaryNode : public Node {
  public:
    PrimaryNode(Node* parent, int argNumber, std::vector<std::byte> value)
        : parentNode(parent), argNumber(argNumber), value(value) {}

    PrimaryNode(Node* parent, int argNumber, std::string value);

    PrimaryNode(Node* parent, int argNumber, long long value);

    Node* parent() override {
        return parentNode;
    }

    void setParent(Node* parent_) override {
        this->parentNode = parent_;
    }

    Node* operator[](int index) override {
        // PrimaryNode is a leaf node.
        return nullptr;
    }

    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) override;

    bool getMatchByTID(int tid) const override;

  private:
    Node* parentNode;
    int argNumber;
    std::vector<std::byte> value;
    std::unordered_map<int, bool> matchesByTID;
};

class MemoryNode : public Node {
  public:
    MemoryNode(Node* parent, int argNumber, const std::vector<short>& pattern,
               std::optional<uint64_t> offset, MemorySearchMode searchMode)
        : parentNode(parent), argNumber(argNumber), pattern(pattern), patternSize(pattern.size()),
          searchMode(searchMode), offset(offset) {}

    Node* parent() override {
        return parentNode;
    }

    void setParent(Node* parent_) override {
        this->parentNode = parent_;
    }

    Node* operator[](int index) override {
        // MemoryNode is a leaf node.
        return nullptr;
    }

    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) override;

    bool getMatchByTID(int tid) const override;

  private:
    Node* parentNode;
    const uint64_t argNumber;
    const std::vector<short> pattern;
    const size_t patternSize; // pattern size
    const std::optional<uint64_t> offset;
    const MemorySearchMode searchMode;
    std::unordered_map<int, bool> matchesByTID;
    bool evaluatePrefix_(int tid, std::shared_ptr<DebuggerInterface>);
    bool evaluateSuffix_(int tid, std::shared_ptr<DebuggerInterface>);
    bool evaluateOffset_(int tid, std::shared_ptr<DebuggerInterface>);
    bool evaluateContains_(int tid, std::shared_ptr<DebuggerInterface>);
};

class ApiCallNode : public Node {
  public:
    ApiCallNode(Node* parent, std::string apiName, std::vector<std::shared_ptr<Node>> args,
                std::shared_ptr<ThenNode> firstThenNode)
        : parentNode(parent), apiName(apiName), args(args), firstThenNode(firstThenNode) {};

    Node* parent() override {
        return parentNode;
    }

    void setParent(Node* parent_) override {
        this->parentNode = parent_;
    }

    Node* operator[](int index) override {
        // ApiCallNode is a leaf node.
        return nullptr;
    }

    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) override;

    bool getMatchByTID(int tid) const override;

    std::shared_ptr<ThenNode> getFirstThenNode() {
        return firstThenNode;
    }

  private:
    Node* parentNode;
    std::string apiName;
    std::vector<std::shared_ptr<Node>> args;
    std::unordered_map<int, bool> matchesByTID;
    std::shared_ptr<ThenNode> firstThenNode;
};

using ApiNodePtr = std::shared_ptr<Nodes::ApiCallNode>;
using ApiNodeList = std::vector<ApiNodePtr>;
using ApiNodeMap = std::unordered_map<std::string, ApiNodeList>;

} // namespace Nodes

class Rule {
  public:
    Rule(std::string ruleName, std::string ruleExpression,
         std::shared_ptr<Nodes::RootNode> rootNode,
         std::shared_ptr<Nodes::ApiNodeMap> apiCallNodesByApiName)
        : active(true), name(ruleName), ruleExpression(ruleExpression), rootNode(rootNode),
          apiCallNodesByApiName(apiCallNodesByApiName) {};

    void setActive(bool state) {
        this->active = state;
    }
    bool getActive() const {
        return this->active;
    }
    std::string getName() const {
        return this->name;
    }
    std::string getExpression() const {
        return this->ruleExpression;
    }
    std::shared_ptr<Nodes::RootNode> getRootNode() {
        return rootNode;
    }
    std::shared_ptr<Nodes::ApiNodeMap> getApiCallNodesByApiName() const {
        return apiCallNodesByApiName;
    }
    bool getMatchByThread(int tid) const;
    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger);

  private:
    bool active;
    std::string name;
    std::string ruleExpression;
    std::shared_ptr<Nodes::RootNode> rootNode;
    std::shared_ptr<Nodes::ApiNodeMap> apiCallNodesByApiName;
    std::unordered_map<int, bool> matchesByTID;
};

class Rules {};

#endif // DATASTRUCTURE_H