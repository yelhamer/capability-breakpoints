#include "include/engine.h"

#include "include/datastructure.h"
#include "include/debugger.h"
#include "include/dsgen.h"
#include "language/generated/CapabilityDSLLexer.h"
#include "language/generated/CapabilityDSLParser.h"

#include <antlr4-runtime.h>
#include <cstddef>
#include <memory>
#include <string>

using namespace antlr4;

std::shared_ptr<Rule> generateRuleFromExpression(std::string ruleName, std::string ruleExpression) {
    std::shared_ptr<Nodes::ApiNodeMap> apiCallNodesByApiName =
        std::make_shared<Nodes::ApiNodeMap>();

    ANTLRInputStream input(ruleExpression);
    CapabilityDSLLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CapabilityDSLParser parser(&tokens);
    std::shared_ptr<Nodes::RootNode> rootNode = std::make_shared<Nodes::RootNode>(
        walk(parser.ruleExpr(), nullptr, apiCallNodesByApiName, nullptr), nullptr);
    (*rootNode)[0]->setParent(rootNode.get());

    std::shared_ptr<Rule> rule =
        std::make_shared<Rule>(ruleName, ruleExpression, rootNode, apiCallNodesByApiName);
    rule->getRootNode()->setRule(rule.get());

    return rule;
}

Rule* attemptMatchFromNode(int tid, std::shared_ptr<DebuggerInterface> debugger,
                           Nodes::Node* node) {
    Nodes::RootNode* node_ = dynamic_cast<Nodes::RootNode*>(node);
    if (!node_ || !node_->evaluate(tid, debugger)) {
        return nullptr;
    }

    if (Nodes::RootNode* type = dynamic_cast<Nodes::RootNode*>(node)) {
        return type->getRule();
    }

    return attemptMatchFromNode(tid, debugger, node->parent());
}

Rule* attemptMatchFromApiNode(int tid, std::shared_ptr<DebuggerInterface> debugger,
                              Nodes::ApiCallNode* apiNode) {
    bool result = apiNode->evaluate(tid, debugger);
    Nodes::Node* node = apiNode;

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
    return attemptMatchFromNode(tid, debugger, node->parent());
}