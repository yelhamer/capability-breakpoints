#include "engine.h"

#include "datastructure.h"
#include "debugger.h"
#include "dsgen.h"
#include "language/generated/CapabilityDSLLexer.h"
#include "language/generated/CapabilityDSLParser.h"
#include "state.h"

#include <antlr4-runtime.h>
#include <any>
#include <cstddef>
#include <memory>
#include <string>

using namespace antlr4;

std::shared_ptr<Rule> generateRuleFromExpression(std::string ruleName, std::string ruleExpression) {
    std::shared_ptr<Nodes::ApiNodeList> orderedApiCallNodes =
        std::make_shared<Nodes::ApiNodeList>();
    std::shared_ptr<Nodes::ApiNodeMap> apiCallNodesByApiName =
        std::make_shared<Nodes::ApiNodeMap>();

    ANTLRInputStream input(ruleExpression);
    CapabilityDSLLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CapabilityDSLParser parser(&tokens);
    std::shared_ptr<Nodes::RootNode> rootNode = std::make_shared<Nodes::RootNode>(
        walk(parser.ruleExpr(), nullptr, orderedApiCallNodes, apiCallNodesByApiName, nullptr),
        nullptr);
    (*rootNode)[0]->setParent(rootNode.get());

    std::shared_ptr<Rule> rule = std::make_shared<Rule>(ruleName, ruleExpression, rootNode,
                                                        apiCallNodesByApiName, orderedApiCallNodes);
    rule->getRootNode()->setRule(rule.get());

    return rule;
}

std::shared_ptr<Match> attemptMatchFromNode(int tid, std::shared_ptr<DebuggerInterface> debugger,
                                            Nodes::Node* node) {
    if (!node || !node->evaluate(tid, debugger)) {
        return nullptr;
    }

    if (Nodes::RootNode* type = dynamic_cast<Nodes::RootNode*>(node)) {
        auto match = std::make_shared<Match>(tid, type->getRule(), debugger->getStates());
        type->getRule()->addMatch(tid, match);
        return match;
    }

    return attemptMatchFromNode(tid, debugger, node->parent());
}

std::shared_ptr<Match> attemptMatchFromApiNode(int tid, std::shared_ptr<DebuggerInterface> debugger,
                                               Nodes::ApiCallNode* apiNode) {
    bool result = apiNode->evaluate(tid, debugger);
    Nodes::Node* node = apiNode->parent();

    if (!result) {
        return nullptr;
    }

    // result == true
    Nodes::ThenNode* firstThenNode = apiNode->getFirstThenNode().get();

    if (firstThenNode) {
        if (!firstThenNode->evaluate(tid, debugger)) {
            // Then evaluates to false, no need to evaluate higher up the tree.
            return nullptr;
        }

        node = firstThenNode;
    }
    return attemptMatchFromNode(tid, debugger, node);
}

void Rule::setActive(bool state) {
    std::lock_guard<std::mutex> lock(stateMutex);
    this->active = state;
}

bool Rule::getActive() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return this->active;
}

void Rule::setName(const std::string& newName) {
    std::lock_guard<std::mutex> lock(stateMutex);
    name = newName;
}

std::string Rule::getName() const {
    std::lock_guard<std::mutex> lock(stateMutex);
    return this->name;
}
std::string Rule::getExpression() const {
    return this->ruleExpression;
}

std::shared_ptr<Nodes::RootNode> Rule::getRootNode() {
    return this->rootNode;
}

std::shared_ptr<Nodes::ApiNodeList> Rule::getOrderedApiCallNodes() const {
    return this->orderedApiCallNodes;
}

std::shared_ptr<Nodes::ApiNodeMap> Rule::getApiCallNodesByApiName() const {
    return apiCallNodesByApiName;
}

std::vector<int> Rule::getMatchingThreads() const {
    std::lock_guard<std::mutex> lock(stateMutex);

    std::vector<int> result;
    result.reserve(matchesByTID.size());

    for (const auto& [tid, matched] : matchesByTID) {
        if (!matched.empty())
            result.push_back(tid);
    }

    std::sort(result.begin(), result.end());

    return result;
}

bool Rule::getMatchByThread(int tid) const {
    std::lock_guard<std::mutex> lock(stateMutex);
    const auto it = matchesByTID.find(tid);
    return it != matchesByTID.end() && !it->second.empty();
}

void Rule::addMatch(int tid, std::shared_ptr<Match> match) {
    std::lock_guard<std::mutex> lock(stateMutex);
    this->matchesByTID[tid].push_back(match);
}

std::vector<std::shared_ptr<Match>> Rule::getMatches() const {
    std::lock_guard<std::mutex> lock(stateMutex);

    std::vector<std::shared_ptr<Match>> result;

    for (const auto& [tid, matches] : matchesByTID) {
        result.insert(result.end(), matches.begin(), matches.end());
    }

    return result;
}

/*bool Rule::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    if (!this->rootNode->evaluate(tid, debugger)) {
        return false;
    }

    std::lock_guard<std::mutex> lock(stateMutex);
    this->matchesByTID[tid] = true;

    return true;
}*/
