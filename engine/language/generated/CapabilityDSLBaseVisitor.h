
// Generated from CapabilityDSL.g4 by ANTLR 4.10

#pragma once


#include "antlr4-runtime.h"
#include "CapabilityDSLVisitor.h"


/**
 * This class provides an empty implementation of CapabilityDSLVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CapabilityDSLBaseVisitor : public CapabilityDSLVisitor {
public:

  virtual std::any visitParentNode(CapabilityDSLParser::ParentNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitThenNode(CapabilityDSLParser::ThenNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndNode(CapabilityDSLParser::AndNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallNode(CapabilityDSLParser::CallNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrNode(CapabilityDSLParser::OrNodeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitApiWithArgs(CapabilityDSLParser::ApiWithArgsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierName(CapabilityDSLParser::IdentifierNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgListContainer(CapabilityDSLParser::ArgListContainerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitApiArg(CapabilityDSLParser::ApiArgContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgOr(CapabilityDSLParser::ArgOrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryValue(CapabilityDSLParser::PrimaryValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemMatch(CapabilityDSLParser::MemMatchContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgNot(CapabilityDSLParser::ArgNotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgParen(CapabilityDSLParser::ArgParenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemParen(CapabilityDSLParser::MemParenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemAnd(CapabilityDSLParser::MemAndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemOr(CapabilityDSLParser::MemOrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemNot(CapabilityDSLParser::MemNotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemLeaf(CapabilityDSLParser::MemLeafContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMemDeref(CapabilityDSLParser::MemDerefContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOffsetPattern(CapabilityDSLParser::OffsetPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrefixPattern(CapabilityDSLParser::PrefixPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSuffixPattern(CapabilityDSLParser::SuffixPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitContainsPattern(CapabilityDSLParser::ContainsPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleElem(CapabilityDSLParser::SingleElemContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiElems(CapabilityDSLParser::MultiElemsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemStringRepeat(CapabilityDSLParser::ElemStringRepeatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemString(CapabilityDSLParser::ElemStringContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemHexRepeat(CapabilityDSLParser::ElemHexRepeatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemHex(CapabilityDSLParser::ElemHexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemIntRepeat(CapabilityDSLParser::ElemIntRepeatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemInt(CapabilityDSLParser::ElemIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemWildcardRepeat(CapabilityDSLParser::ElemWildcardRepeatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElemWildcard(CapabilityDSLParser::ElemWildcardContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleHex(CapabilityDSLParser::SingleHexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiHex(CapabilityDSLParser::MultiHexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingleInt(CapabilityDSLParser::SingleIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiInt(CapabilityDSLParser::MultiIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryHex(CapabilityDSLParser::PrimaryHexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryInt(CapabilityDSLParser::PrimaryIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryValHex(CapabilityDSLParser::PrimaryValHexContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryValInt(CapabilityDSLParser::PrimaryValIntContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryValStr(CapabilityDSLParser::PrimaryValStrContext *ctx) override {
    return visitChildren(ctx);
  }


};

