
// Generated from CapabilityDSL.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "CapabilityDSLParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CapabilityDSLParser.
 */
class  CapabilityDSLVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CapabilityDSLParser.
   */
    virtual std::any visitParentNode(CapabilityDSLParser::ParentNodeContext *context) = 0;

    virtual std::any visitThenNode(CapabilityDSLParser::ThenNodeContext *context) = 0;

    virtual std::any visitAndNode(CapabilityDSLParser::AndNodeContext *context) = 0;

    virtual std::any visitCallNode(CapabilityDSLParser::CallNodeContext *context) = 0;

    virtual std::any visitOrNode(CapabilityDSLParser::OrNodeContext *context) = 0;

    virtual std::any visitApiWithArgs(CapabilityDSLParser::ApiWithArgsContext *context) = 0;

    virtual std::any visitIdentifierName(CapabilityDSLParser::IdentifierNameContext *context) = 0;

    virtual std::any visitArgListContainer(CapabilityDSLParser::ArgListContainerContext *context) = 0;

    virtual std::any visitApiArg(CapabilityDSLParser::ApiArgContext *context) = 0;

    virtual std::any visitArgOr(CapabilityDSLParser::ArgOrContext *context) = 0;

    virtual std::any visitPrimaryValue(CapabilityDSLParser::PrimaryValueContext *context) = 0;

    virtual std::any visitMemMatch(CapabilityDSLParser::MemMatchContext *context) = 0;

    virtual std::any visitArgNot(CapabilityDSLParser::ArgNotContext *context) = 0;

    virtual std::any visitArgParen(CapabilityDSLParser::ArgParenContext *context) = 0;

    virtual std::any visitMemParen(CapabilityDSLParser::MemParenContext *context) = 0;

    virtual std::any visitMemAnd(CapabilityDSLParser::MemAndContext *context) = 0;

    virtual std::any visitMemOr(CapabilityDSLParser::MemOrContext *context) = 0;

    virtual std::any visitMemNot(CapabilityDSLParser::MemNotContext *context) = 0;

    virtual std::any visitMemLeaf(CapabilityDSLParser::MemLeafContext *context) = 0;

    virtual std::any visitMemDeref(CapabilityDSLParser::MemDerefContext *context) = 0;

    virtual std::any visitOffsetPattern(CapabilityDSLParser::OffsetPatternContext *context) = 0;

    virtual std::any visitPrefixPattern(CapabilityDSLParser::PrefixPatternContext *context) = 0;

    virtual std::any visitSuffixPattern(CapabilityDSLParser::SuffixPatternContext *context) = 0;

    virtual std::any visitContainsPattern(CapabilityDSLParser::ContainsPatternContext *context) = 0;

    virtual std::any visitSingleElem(CapabilityDSLParser::SingleElemContext *context) = 0;

    virtual std::any visitMultiElems(CapabilityDSLParser::MultiElemsContext *context) = 0;

    virtual std::any visitElemStringRepeat(CapabilityDSLParser::ElemStringRepeatContext *context) = 0;

    virtual std::any visitElemString(CapabilityDSLParser::ElemStringContext *context) = 0;

    virtual std::any visitElemHexRepeat(CapabilityDSLParser::ElemHexRepeatContext *context) = 0;

    virtual std::any visitElemHex(CapabilityDSLParser::ElemHexContext *context) = 0;

    virtual std::any visitElemIntRepeat(CapabilityDSLParser::ElemIntRepeatContext *context) = 0;

    virtual std::any visitElemInt(CapabilityDSLParser::ElemIntContext *context) = 0;

    virtual std::any visitElemWildcardRepeat(CapabilityDSLParser::ElemWildcardRepeatContext *context) = 0;

    virtual std::any visitElemWildcard(CapabilityDSLParser::ElemWildcardContext *context) = 0;

    virtual std::any visitSingleHex(CapabilityDSLParser::SingleHexContext *context) = 0;

    virtual std::any visitMultiHex(CapabilityDSLParser::MultiHexContext *context) = 0;

    virtual std::any visitSingleInt(CapabilityDSLParser::SingleIntContext *context) = 0;

    virtual std::any visitMultiInt(CapabilityDSLParser::MultiIntContext *context) = 0;

    virtual std::any visitPrimaryHex(CapabilityDSLParser::PrimaryHexContext *context) = 0;

    virtual std::any visitPrimaryInt(CapabilityDSLParser::PrimaryIntContext *context) = 0;

    virtual std::any visitPrimaryValHex(CapabilityDSLParser::PrimaryValHexContext *context) = 0;

    virtual std::any visitPrimaryValInt(CapabilityDSLParser::PrimaryValIntContext *context) = 0;

    virtual std::any visitPrimaryValStr(CapabilityDSLParser::PrimaryValStrContext *context) = 0;


};

