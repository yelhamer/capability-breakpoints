#ifndef ENGINE_H
#define ENGINE_H

#include "datastructure.h"
#include "debugger.h"
#include "state.h"

#include <memory>
#include <string>

class Rule {
  public:
    Rule(std::string ruleName, std::string ruleExpression,
         std::shared_ptr<Nodes::RootNode> rootNode,
         std::shared_ptr<Nodes::ApiNodeMap> apiCallNodesByApiName,
         std::shared_ptr<Nodes::ApiNodeList> orderedApiCallNodes)
        : active(true), name(ruleName), ruleExpression(ruleExpression), rootNode(rootNode),
          apiCallNodesByApiName(apiCallNodesByApiName), orderedApiCallNodes(orderedApiCallNodes) {};

    void setActive(bool state);
    bool getActive() const;
    void setName(const std::string& newName);
    std::string getName() const;
    std::vector<int> getMatchingThreads() const;
    std::string getExpression() const;
    std::shared_ptr<Nodes::RootNode> getRootNode();
    std::shared_ptr<Nodes::ApiNodeList> getOrderedApiCallNodes() const;
    std::shared_ptr<Nodes::ApiNodeMap> getApiCallNodesByApiName() const;
    bool getMatchByThread(int tid) const;
    bool evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger);

  private:
    mutable std::mutex stateMutex;
    bool active;
    std::string name;
    std::string ruleExpression;
    std::shared_ptr<Nodes::RootNode> rootNode;
    std::shared_ptr<Nodes::ApiNodeList> orderedApiCallNodes;
    std::shared_ptr<Nodes::ApiNodeMap> apiCallNodesByApiName;
    std::unordered_map<int, bool> matchesByTID;
};

class Match {
  public:
    Match(int tid, std::shared_ptr<Rule> rule,
          TidToApiNodeToStatePtrListMap allStatesByTIDandApiCallNode)
        : tid(tid), rule(rule) {
        auto nodes = rule->getOrderedApiCallNodes();
        this->statesByApiCallNode.reserve(nodes->size());
        for (auto& node : *nodes) {
            this->statesByApiCallNode[node] = allStatesByTIDandApiCallNode[tid][node];
        }
    }

    std::shared_ptr<Rule> getRule() const {
        return rule;
    }

    int getThreadId() const {
        return tid;
    }

    StatePtrList getStatesForApiNode(Nodes::ApiNodePtr apiNodePtr) {
        return statesByApiCallNode[apiNodePtr];
    }

    std::shared_ptr<Nodes::ApiNodeList> getOrderedApiCallNodes() const {
        return rule->getOrderedApiCallNodes();
    }

  private:
    int tid;
    std::shared_ptr<Rule> rule;
    ApiNodeToStatePtrListMap statesByApiCallNode;
};

std::shared_ptr<Rule> generateRuleFromExpression(std::string ruleName, std::string ruleExpression);

std::shared_ptr<Match> attemptMatchFromNode(int tid, std::shared_ptr<DebuggerInterface> debugger,
                                            Nodes::Node* node);

std::shared_ptr<Match> attemptMatchFromApiNode(int tid, std::shared_ptr<DebuggerInterface> debugger,
                                               Nodes::ApiCallNode* apiNode);

#endif // ENGINE_H