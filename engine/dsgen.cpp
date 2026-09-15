#include "language/generated/CapabilityDSLLexer.h"
#include "language/generated/CapabilityDSLParser.h"
#include "include/datastructure.h"
#include "include/dsgen.h"

#include <any>
#include <cstdint>
#include <string>
#include <optional>
#include <memory>
#include <unordered_map>
#include <vector>


using namespace antlr4;


std::any getTerminal(tree::TerminalNode* node){
    if (node->getSymbol()->getType() == CapabilityDSLLexer::HEX_INT) {
        return std::stol(node->getSymbol()->getText(), nullptr, 16);
    } else if (node->getSymbol()->getType() == CapabilityDSLLexer::INT) {
        return std::stol(node->getSymbol()->getText());
    } else if (node->getSymbol()->getType() == CapabilityDSLLexer::STRING) {
        return node->getSymbol()->getText();
    } else if (node->getSymbol()->getType() == CapabilityDSLLexer::WILDCARD) {
        return -1;
    } else if (node->getSymbol()->getType() == CapabilityDSLLexer::IDENTIFIER) {
        return node->getSymbol()->getText();
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

long walkPrimary(CapabilityDSLParser::PrimaryContext* node){
    if (auto* type = dynamic_cast<CapabilityDSLParser::PrimaryHexContext*>(node)) {
        return std::any_cast<long>(getTerminal(type->HEX_INT()));
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::PrimaryIntContext*>(node)) {
        return std::any_cast<long>(getTerminal(type->INT()));
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

std::shared_ptr<Nodes::PrimaryNode> walkPrimaryVal(CapabilityDSLParser::PrimaryValContext* node, Nodes::Node* parent, int argNumber){
    if (auto* type = dynamic_cast<CapabilityDSLParser::PrimaryValHexContext*>(node)) {
        return std::make_shared<Nodes::PrimaryNode> (
            parent,
            argNumber,
            std::any_cast<long>(getTerminal(type->HEX_INT()))
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::PrimaryValIntContext*>(node)) {
        return std::make_shared<Nodes::PrimaryNode> (
            parent,
            argNumber,
            std::any_cast<long>(getTerminal(type->INT()))
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::PrimaryValStrContext*>(node)) {
        return std::make_shared<Nodes::PrimaryNode> (
            parent,
            argNumber,
            std::any_cast<std::string>(getTerminal(type->STRING()))
        );
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

std::vector<short> walkIntList(CapabilityDSLParser::IntListContext* node){
    if (auto* type = dynamic_cast<CapabilityDSLParser::SingleIntContext*>(node)) {
        return std::vector<short>{std::any_cast<short>(getTerminal(type->INT()))};
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::MultiIntContext*>(node)) {
        auto intList1 = walkIntList(type->intList()[0]);
        auto intList2 = walkIntList(type->intList()[1]);
        intList1.insert(intList1.end(), intList2.begin(), intList2.end());
        return intList1;
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

std::vector<short> walkHexList(CapabilityDSLParser::HexListContext* node){
    if (auto* type = dynamic_cast<CapabilityDSLParser::SingleHexContext*>(node)) {
        return std::vector<short>{std::any_cast<short>(getTerminal(type->HEX_INT()))};
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::MultiHexContext*>(node)) {
        auto hexList1 = walkHexList(type->hexList()[0]);
        auto hexList2 = walkHexList(type->hexList()[1]);
        hexList1.insert(hexList1.end(), hexList2.begin(), hexList2.end());
        return hexList1;
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

std::vector<short> walkPatternElem(CapabilityDSLParser::PatternElemContext* node){
    std::vector<short> pattern;
    if (auto* type = dynamic_cast<CapabilityDSLParser::ElemStringRepeatContext*>(node)) {
        std::string strSubPattern = std::any_cast<std::string>(getTerminal(type->STRING()));
        for (int i = 0; i < std::any_cast<int>(getTerminal(type->INT())); ++i) {
            pattern.insert(pattern.end(), strSubPattern.begin(), strSubPattern.end());
        }
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ElemHexRepeatContext*>(node)) {
        std::vector<short> hexSubPattern = walkHexList(type->hexList());
        for (int i = 0; i < std::any_cast<int>(getTerminal(type->INT())); ++i) {
            pattern.insert(pattern.end(), hexSubPattern.begin(), hexSubPattern.end());
        }
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ElemIntRepeatContext*>(node)) {
        for (int i = 0; i < std::any_cast<int>(getTerminal(type->INT())); ++i) {
            std::vector<short> intSubPattern = walkIntList(type->intList());
            pattern.insert(pattern.end(), intSubPattern.begin(), intSubPattern.end());
        }
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ElemWildcardRepeatContext*>(node)) {
        for (int i = 0; i < type->WILDCARD().size() * std::any_cast<int>(getTerminal(type->INT())); ++i) {
            pattern.push_back(-1);
        }
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ElemWildcardContext*>(node)) {
        for (int i = 0; i < type->WILDCARD().size(); ++i) {
            pattern.push_back(-1);
        }
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ElemStringContext*>(node)) {
        std::string strPattern = std::any_cast<std::string>(getTerminal(type->STRING()));
        pattern.insert(pattern.end(), strPattern.begin(), strPattern.end());
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ElemHexContext*>(node)) {
        pattern.push_back(std::any_cast<short>(getTerminal(type->HEX_INT())));
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ElemIntContext*>(node)) {
        pattern.push_back(std::any_cast<int>(getTerminal(type->INT())));
    }

    return pattern;
}

std::vector<short> walkPatternElems(CapabilityDSLParser::PatternElemsContext* node){
    if (auto* type = dynamic_cast<CapabilityDSLParser::SingleElemContext*>(node)) {
        return walkPatternElem(type->patternElem());
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::MultiElemsContext*>(node)) {
        std::vector<short> patternElems1 = walkPatternElems(type->patternElems()[0]);
        std::vector<short> patternElems2 = walkPatternElems(type->patternElems()[1]);
        patternElems1.insert(patternElems1.end(), patternElems2.begin(), patternElems2.end());
        return patternElems1;
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

std::shared_ptr<Nodes::MemoryNode> walkPatternExpr(CapabilityDSLParser::PatternExprContext* node, Nodes::Node* parent, int argNumber){
    if (auto* type = dynamic_cast<CapabilityDSLParser::OffsetPatternContext*>(node)) {
        std::vector<short> pattern = walkPatternElems(type->patternElems());
        uint64_t offset = static_cast<uint64_t>(walkPrimary(type->primary()));
        return std::make_shared<Nodes::MemoryNode>(
            nullptr,
            argNumber,
            pattern,
            offset,
            MemorySearchMode::Offset       
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::PrefixPatternContext*>(node)) {
        std::vector<short> pattern = walkPatternElems(type->patternElems());
        return std::make_shared<Nodes::MemoryNode>(
            nullptr,
            argNumber,
            pattern,
            std::nullopt,
            MemorySearchMode::Prefix
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::SuffixPatternContext*>(node)) {
        std::vector<short> pattern = walkPatternElems(type->patternElems());
        return std::make_shared<Nodes::MemoryNode>(
            nullptr,
            argNumber,
            pattern,
            std::nullopt,
            MemorySearchMode::Suffix
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ContainsPatternContext*>(node)) {
        std::vector<short> pattern = walkPatternElems(type->patternElems());
        return std::make_shared<Nodes::MemoryNode>(
            nullptr,
            argNumber,
            pattern,
            std::nullopt,
            MemorySearchMode::Contains
        );
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}


std::shared_ptr<Nodes::Node> walkMemExpr(CapabilityDSLParser::MemExprContext* node, Nodes::Node* parent, int argNumber){
    if (auto* type = dynamic_cast<CapabilityDSLParser::MemParenContext*>(node)) {
        return walkMemExpr(type->memExpr(), parent, argNumber);
    } else if (auto* type =  dynamic_cast<CapabilityDSLParser::MemNotContext*>(node)) {
        return std::make_shared<Nodes::NotNode>(
            parent,
            walkMemExpr(type->memExpr(), parent, argNumber)
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::MemAndContext*>(node)) {
        return std::make_shared<Nodes::AndNode>(
            parent,
            walkMemExpr(type->memExpr()[0], parent, argNumber),
            walkMemExpr(type->memExpr()[1], parent, argNumber)
        );
    } else if (auto* type =  dynamic_cast<CapabilityDSLParser::MemOrContext*>(node)) {
        return std::make_shared<Nodes::OrNode>(
            parent,
            walkMemExpr(type->memExpr()[0], parent, argNumber),
            walkMemExpr(type->memExpr()[1], parent, argNumber)
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::MemLeafContext*>(node)) {
        auto* type_ = dynamic_cast<CapabilityDSLParser::MemDereferenceContext*>(type->memDereference());
        if(auto* type__ = dynamic_cast<CapabilityDSLParser::MemDerefContext*>(type_)){
            return walkPatternExpr(type__->patternExpr(), parent, argNumber);
        } else {
            throw antlr4::RuntimeException("Unhandled context");
        }
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}


std::shared_ptr<Nodes::Node> walkArgExpr(CapabilityDSLParser::ArgExprContext* node, Nodes::Node* parent, int argNumber){
    if (auto* type = dynamic_cast<CapabilityDSLParser::ArgParenContext*>(node)) {
        return walkArgExpr(type->argExpr(), parent, argNumber);
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ArgNotContext*>(node)) {
        return std::make_shared<Nodes::NotNode>(
            parent,
            walkArgExpr(type->argExpr(), parent, argNumber)
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::ArgOrContext*>(node)) {
        return std::make_shared<Nodes::OrNode>(
            parent,
            walkArgExpr(type->argExpr()[0], parent, argNumber),
            walkArgExpr(type->argExpr()[1], parent, argNumber)
        );
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::MemMatchContext*>(node)) {
        return walkMemExpr(type->memExpr(), parent, argNumber);
    } else if (auto* type = dynamic_cast<CapabilityDSLParser::PrimaryValueContext*>(node)) {
        return walkPrimaryVal(type->primaryVal(), parent, argNumber);
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

std::shared_ptr<Nodes::Node> walkApiArg(CapabilityDSLParser::ApiArgContext* node, Nodes::Node* parent, int argNumber){
    if (node->argExpr()) {
        return walkArgExpr(node->argExpr(), parent, argNumber);
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

std::vector<std::shared_ptr<Nodes::Node>> walkApiArgs(CapabilityDSLParser::ApiArgsContext* node, Nodes::Node* parent){
    std::vector<std::shared_ptr<Nodes::Node>> args;

    if (auto* type = dynamic_cast<CapabilityDSLParser::ArgListContainerContext*>(node)) {    
        for(int i; i< type->apiArg().size(); ++i) {
            args.push_back(walkApiArg(type->apiArg()[i], parent, i));
        }
    }

    return args;
}

std::shared_ptr<Nodes::ApiCallNode> walkApiCall(
    CapabilityDSLParser::ApiCallContext* node,
    Nodes::Node* parent,
    std::unordered_map<std::string, std::vector<std::shared_ptr<Nodes::ApiCallNode>>> callsByApiName,
    std::shared_ptr<Nodes::ThenNode> firstThenNode){
    if (auto* type = dynamic_cast<CapabilityDSLParser::ApiWithArgsContext*>(node)) {
        std::string apiName = type->apiName()->getText();
        std::vector<std::shared_ptr<Nodes::Node>> args = walkApiArgs(type->apiArgs(), parent);
        
        auto apiNode = std::make_shared<Nodes::ApiCallNode>(
            parent,
            apiName,
            args,
            firstThenNode
        );

        callsByApiName[apiName].push_back(apiNode);

        return apiNode;
    } else {
        throw antlr4::RuntimeException("Unhandled context");
    }
}

std::shared_ptr<Nodes::AndNode> walkAnd(
    CapabilityDSLParser::AndNodeContext* node,
    Nodes::Node* parent,
    std::unordered_map<std::string, std::vector<std::shared_ptr<Nodes::ApiCallNode>>> callsByApiName,
    std::shared_ptr<Nodes::ThenNode> firstThenNode){
    return std::make_shared<Nodes::AndNode>(
        parent,
        walk(node->ruleExpr()[0], parent, callsByApiName, firstThenNode),
        walk(node->ruleExpr()[1], parent, callsByApiName, firstThenNode)
    );
}

std::shared_ptr<Nodes::OrNode> walkOr(
    CapabilityDSLParser::OrNodeContext* node,
    Nodes::Node* parent,
    std::unordered_map<std::string, std::vector<std::shared_ptr<Nodes::ApiCallNode>>> callsByApiName,
    std::shared_ptr<Nodes::ThenNode> firstThenNode){
    return std::make_shared<Nodes::OrNode>(
        parent,
        walk(node->ruleExpr()[0], parent, callsByApiName, firstThenNode),
        walk(node->ruleExpr()[1], parent, callsByApiName, firstThenNode)
    );
}

std::shared_ptr<Nodes::ThenNode> walkThen(
    CapabilityDSLParser::ThenNodeContext* node,
    Nodes::Node* parent,
    std::unordered_map<std::string, std::vector<std::shared_ptr<Nodes::ApiCallNode>>> callsByApiName,
    std::shared_ptr<Nodes::ThenNode> firstThenNode){
        auto thenNode = std::make_shared<Nodes::ThenNode>(parent);
        
        thenNode->setFirst(
            walk(
                node->ruleExpr()[0],
                parent,
                callsByApiName,
                firstThenNode ? firstThenNode : thenNode
            )
        );

        thenNode->setSecond(
            walk(
                node->ruleExpr()[1],
                parent,
                callsByApiName,
                firstThenNode ? firstThenNode : thenNode
            )
        );
    
        return thenNode;
}

std::shared_ptr<Nodes::Node> walk(
    tree::ParseTree *node,
    Nodes::Node* parent,
    std::unordered_map<std::string, std::vector<std::shared_ptr<Nodes::ApiCallNode>>> callsByApiName,
    std::shared_ptr<Nodes::ThenNode> firstThenNode){
    if (auto* ApiNode = dynamic_cast<CapabilityDSLParser::ApiCallContext*>(node)) {
        // cannot have embeded argNumber
        return walkApiCall(ApiNode, parent, callsByApiName, firstThenNode);
    }

    if (auto* AndNode = dynamic_cast<CapabilityDSLParser::AndNodeContext*>(node)) {
        return walkAnd(AndNode, parent, callsByApiName, firstThenNode);
    }

    if (auto* OrNode = dynamic_cast<CapabilityDSLParser::OrNodeContext*>(node)) {
        return walkOr(OrNode, parent, callsByApiName, firstThenNode);
    }

    if (auto* ThenNode = dynamic_cast<CapabilityDSLParser::ThenNodeContext*>(node)) {
        return walkThen(ThenNode, parent, callsByApiName, firstThenNode);
    }

    throw antlr4::RuntimeException("Unhandled context");

}