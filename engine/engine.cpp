#include <memory>
#include <string>
#include <unordered_map>
#include "language/generated/CapabilityDSLLexer.h"
#include "language/generated/CapabilityDSLParser.h"
#include <antlr4-runtime.h>
#include "include/datastructure.h"
#include "include/debugger.h"
#include "include/dsgen.h"

using namespace antlr4;


Rule::Rule(std::string ruleName, std::string ruleText) : name(ruleName) {
    std::unordered_map<std::string, std::vector<std::shared_ptr<Nodes::ApiCallNode>>> callsByApiName;

    ANTLRInputStream input(ruleText);
    CapabilityDSLLexer lexer(&input);
    CommonTokenStream tokens(&lexer);
    CapabilityDSLParser parser(&tokens);

    this->RootNode = std::dynamic_pointer_cast<Nodes::RootNode>(walk(parser.ruleExpr(), nullptr, callsByApiName, nullptr));
}

bool Rule::getMatchByThread(int tid) {
    return matchesByTID[tid];
}

bool Rule::evaluate(int tid, std::shared_ptr<DebuggerInterface> debugger) {
    bool result = RootNode->evaluate(tid, debugger);

    if (result) {
        matchesByTID[tid] = true;
    }

    return result;
}


std::shared_ptr<Rule> attemptMatchFromNode(int tid, std::shared_ptr<DebuggerInterface> debugger, Nodes::Node* node) {
    bool result = node->evaluate(tid, debugger);
    
    if (!result) {
        return nullptr;
    }

    if (Nodes::RootNode* type = dynamic_cast<Nodes::RootNode*>(node)) {
        return type->getRule();
    }

    return attemptMatchFromNode(tid, debugger, node->parent());

}


std::shared_ptr<Rule> attemptMatchFromApiNode(int tid, std::shared_ptr<DebuggerInterface> debugger, std::shared_ptr<Nodes::ApiCallNode> apiNode) {
    bool result = apiNode->evaluate(tid, debugger);
    std::shared_ptr<Nodes::Node> node = apiNode;
    
    if (!result) {
        return nullptr;
    }

    // result == true
    std::shared_ptr<Nodes::ThenNode> firstThenNode = apiNode->getFirstThenNode();
    
    if (firstThenNode) {
        if (!firstThenNode->evaluate(tid,debugger)) {
            // Then evaluates to false, no need to evaluate higher up the tree.
            return nullptr;
        }

        node = firstThenNode;
    }
    
    return attemptMatchFromNode(tid, debugger, node.get());

}