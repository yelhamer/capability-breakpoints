
// Generated from C:/Users/yacin/src/capability-breakpoints/engine/language/CapabilityDSL.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  CapabilityDSLParser : public antlr4::Parser {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, AND = 9, OR = 10, THEN = 11, NOT = 12, WILDCARD = 13, HEX_INT = 14, 
    INT = 15, IDENTIFIER = 16, STRING = 17, COMMENT = 18, WS = 19
  };

  enum {
    RuleRuleExpr = 0, RuleApiCall = 1, RuleApiName = 2, RuleApiArgs = 3, 
    RuleApiArg = 4, RuleArgExpr = 5, RuleMemExpr = 6, RuleMemDereference = 7, 
    RulePatternExpr = 8, RulePatternElems = 9, RulePatternElem = 10, RuleHexList = 11, 
    RuleIntList = 12, RulePrimary = 13, RulePrimaryVal = 14
  };

  explicit CapabilityDSLParser(antlr4::TokenStream *input);

  CapabilityDSLParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~CapabilityDSLParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class RuleExprContext;
  class ApiCallContext;
  class ApiNameContext;
  class ApiArgsContext;
  class ApiArgContext;
  class ArgExprContext;
  class MemExprContext;
  class MemDereferenceContext;
  class PatternExprContext;
  class PatternElemsContext;
  class PatternElemContext;
  class HexListContext;
  class IntListContext;
  class PrimaryContext;
  class PrimaryValContext; 

  class  RuleExprContext : public antlr4::ParserRuleContext {
  public:
    RuleExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    RuleExprContext() = default;
    void copyFrom(RuleExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ParentNodeContext : public RuleExprContext {
  public:
    ParentNodeContext(RuleExprContext *ctx);

    RuleExprContext *ruleExpr();
  };

  class  ThenNodeContext : public RuleExprContext {
  public:
    ThenNodeContext(RuleExprContext *ctx);

    std::vector<RuleExprContext *> ruleExpr();
    RuleExprContext* ruleExpr(size_t i);
    antlr4::tree::TerminalNode *THEN();
  };

  class  AndNodeContext : public RuleExprContext {
  public:
    AndNodeContext(RuleExprContext *ctx);

    std::vector<RuleExprContext *> ruleExpr();
    RuleExprContext* ruleExpr(size_t i);
    antlr4::tree::TerminalNode *AND();
  };

  class  CallNodeContext : public RuleExprContext {
  public:
    CallNodeContext(RuleExprContext *ctx);

    ApiCallContext *apiCall();
  };

  class  OrNodeContext : public RuleExprContext {
  public:
    OrNodeContext(RuleExprContext *ctx);

    std::vector<RuleExprContext *> ruleExpr();
    RuleExprContext* ruleExpr(size_t i);
    antlr4::tree::TerminalNode *OR();
  };

  RuleExprContext* ruleExpr();
  RuleExprContext* ruleExpr(int precedence);
  class  ApiCallContext : public antlr4::ParserRuleContext {
  public:
    ApiCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ApiCallContext() = default;
    void copyFrom(ApiCallContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ApiWithArgsContext : public ApiCallContext {
  public:
    ApiWithArgsContext(ApiCallContext *ctx);

    ApiNameContext *apiName();
    ApiArgsContext *apiArgs();
  };

  ApiCallContext* apiCall();

  class  ApiNameContext : public antlr4::ParserRuleContext {
  public:
    ApiNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ApiNameContext() = default;
    void copyFrom(ApiNameContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  IdentifierNameContext : public ApiNameContext {
  public:
    IdentifierNameContext(ApiNameContext *ctx);

    antlr4::tree::TerminalNode *IDENTIFIER();
  };

  ApiNameContext* apiName();

  class  ApiArgsContext : public antlr4::ParserRuleContext {
  public:
    ApiArgsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ApiArgsContext() = default;
    void copyFrom(ApiArgsContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ArgListContainerContext : public ApiArgsContext {
  public:
    ArgListContainerContext(ApiArgsContext *ctx);

    std::vector<ApiArgContext *> apiArg();
    ApiArgContext* apiArg(size_t i);
  };

  ApiArgsContext* apiArgs();

  class  ApiArgContext : public antlr4::ParserRuleContext {
  public:
    ApiArgContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ArgExprContext *argExpr();

   
  };

  ApiArgContext* apiArg();

  class  ArgExprContext : public antlr4::ParserRuleContext {
  public:
    ArgExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ArgExprContext() = default;
    void copyFrom(ArgExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ArgOrContext : public ArgExprContext {
  public:
    ArgOrContext(ArgExprContext *ctx);

    std::vector<ArgExprContext *> argExpr();
    ArgExprContext* argExpr(size_t i);
    antlr4::tree::TerminalNode *OR();
  };

  class  PrimaryValueContext : public ArgExprContext {
  public:
    PrimaryValueContext(ArgExprContext *ctx);

    PrimaryValContext *primaryVal();
  };

  class  MemMatchContext : public ArgExprContext {
  public:
    MemMatchContext(ArgExprContext *ctx);

    MemExprContext *memExpr();
  };

  class  ArgNotContext : public ArgExprContext {
  public:
    ArgNotContext(ArgExprContext *ctx);

    antlr4::tree::TerminalNode *NOT();
    ArgExprContext *argExpr();
  };

  class  ArgParenContext : public ArgExprContext {
  public:
    ArgParenContext(ArgExprContext *ctx);

    ArgExprContext *argExpr();
  };

  ArgExprContext* argExpr();
  ArgExprContext* argExpr(int precedence);
  class  MemExprContext : public antlr4::ParserRuleContext {
  public:
    MemExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MemExprContext() = default;
    void copyFrom(MemExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MemParenContext : public MemExprContext {
  public:
    MemParenContext(MemExprContext *ctx);

    MemExprContext *memExpr();
  };

  class  MemAndContext : public MemExprContext {
  public:
    MemAndContext(MemExprContext *ctx);

    std::vector<MemExprContext *> memExpr();
    MemExprContext* memExpr(size_t i);
    antlr4::tree::TerminalNode *AND();
  };

  class  MemOrContext : public MemExprContext {
  public:
    MemOrContext(MemExprContext *ctx);

    std::vector<MemExprContext *> memExpr();
    MemExprContext* memExpr(size_t i);
    antlr4::tree::TerminalNode *OR();
  };

  class  MemNotContext : public MemExprContext {
  public:
    MemNotContext(MemExprContext *ctx);

    antlr4::tree::TerminalNode *NOT();
    MemExprContext *memExpr();
  };

  class  MemLeafContext : public MemExprContext {
  public:
    MemLeafContext(MemExprContext *ctx);

    MemDereferenceContext *memDereference();
  };

  MemExprContext* memExpr();
  MemExprContext* memExpr(int precedence);
  class  MemDereferenceContext : public antlr4::ParserRuleContext {
  public:
    MemDereferenceContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MemDereferenceContext() = default;
    void copyFrom(MemDereferenceContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MemDerefContext : public MemDereferenceContext {
  public:
    MemDerefContext(MemDereferenceContext *ctx);

    PatternExprContext *patternExpr();
  };

  MemDereferenceContext* memDereference();

  class  PatternExprContext : public antlr4::ParserRuleContext {
  public:
    PatternExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PatternExprContext() = default;
    void copyFrom(PatternExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  OffsetPatternContext : public PatternExprContext {
  public:
    OffsetPatternContext(PatternExprContext *ctx);

    PatternElemsContext *patternElems();
    PrimaryContext *primary();
  };

  class  SuffixPatternContext : public PatternExprContext {
  public:
    SuffixPatternContext(PatternExprContext *ctx);

    PatternElemsContext *patternElems();
  };

  class  PrefixPatternContext : public PatternExprContext {
  public:
    PrefixPatternContext(PatternExprContext *ctx);

    PatternElemsContext *patternElems();
  };

  class  ContainsPatternContext : public PatternExprContext {
  public:
    ContainsPatternContext(PatternExprContext *ctx);

    PatternElemsContext *patternElems();
  };

  PatternExprContext* patternExpr();

  class  PatternElemsContext : public antlr4::ParserRuleContext {
  public:
    PatternElemsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PatternElemsContext() = default;
    void copyFrom(PatternElemsContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MultiElemsContext : public PatternElemsContext {
  public:
    MultiElemsContext(PatternElemsContext *ctx);

    std::vector<PatternElemsContext *> patternElems();
    PatternElemsContext* patternElems(size_t i);
  };

  class  SingleElemContext : public PatternElemsContext {
  public:
    SingleElemContext(PatternElemsContext *ctx);

    PatternElemContext *patternElem();
  };

  PatternElemsContext* patternElems();

  class  PatternElemContext : public antlr4::ParserRuleContext {
  public:
    PatternElemContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PatternElemContext() = default;
    void copyFrom(PatternElemContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ElemIntRepeatContext : public PatternElemContext {
  public:
    ElemIntRepeatContext(PatternElemContext *ctx);

    IntListContext *intList();
    antlr4::tree::TerminalNode *INT();
  };

  class  ElemWildcardRepeatContext : public PatternElemContext {
  public:
    ElemWildcardRepeatContext(PatternElemContext *ctx);

    antlr4::tree::TerminalNode *INT();
    std::vector<antlr4::tree::TerminalNode *> WILDCARD();
    antlr4::tree::TerminalNode* WILDCARD(size_t i);
  };

  class  ElemWildcardContext : public PatternElemContext {
  public:
    ElemWildcardContext(PatternElemContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> WILDCARD();
    antlr4::tree::TerminalNode* WILDCARD(size_t i);
  };

  class  ElemStringContext : public PatternElemContext {
  public:
    ElemStringContext(PatternElemContext *ctx);

    antlr4::tree::TerminalNode *STRING();
  };

  class  ElemHexRepeatContext : public PatternElemContext {
  public:
    ElemHexRepeatContext(PatternElemContext *ctx);

    HexListContext *hexList();
    antlr4::tree::TerminalNode *INT();
  };

  class  ElemStringRepeatContext : public PatternElemContext {
  public:
    ElemStringRepeatContext(PatternElemContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *INT();
  };

  class  ElemHexContext : public PatternElemContext {
  public:
    ElemHexContext(PatternElemContext *ctx);

    antlr4::tree::TerminalNode *HEX_INT();
  };

  class  ElemIntContext : public PatternElemContext {
  public:
    ElemIntContext(PatternElemContext *ctx);

    antlr4::tree::TerminalNode *INT();
  };

  PatternElemContext* patternElem();

  class  HexListContext : public antlr4::ParserRuleContext {
  public:
    HexListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    HexListContext() = default;
    void copyFrom(HexListContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MultiHexContext : public HexListContext {
  public:
    MultiHexContext(HexListContext *ctx);

    std::vector<HexListContext *> hexList();
    HexListContext* hexList(size_t i);
  };

  class  SingleHexContext : public HexListContext {
  public:
    SingleHexContext(HexListContext *ctx);

    antlr4::tree::TerminalNode *HEX_INT();
  };

  HexListContext* hexList();

  class  IntListContext : public antlr4::ParserRuleContext {
  public:
    IntListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    IntListContext() = default;
    void copyFrom(IntListContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  MultiIntContext : public IntListContext {
  public:
    MultiIntContext(IntListContext *ctx);

    std::vector<IntListContext *> intList();
    IntListContext* intList(size_t i);
  };

  class  SingleIntContext : public IntListContext {
  public:
    SingleIntContext(IntListContext *ctx);

    antlr4::tree::TerminalNode *INT();
  };

  IntListContext* intList();

  class  PrimaryContext : public antlr4::ParserRuleContext {
  public:
    PrimaryContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrimaryContext() = default;
    void copyFrom(PrimaryContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PrimaryIntContext : public PrimaryContext {
  public:
    PrimaryIntContext(PrimaryContext *ctx);

    antlr4::tree::TerminalNode *INT();
  };

  class  PrimaryHexContext : public PrimaryContext {
  public:
    PrimaryHexContext(PrimaryContext *ctx);

    antlr4::tree::TerminalNode *HEX_INT();
  };

  PrimaryContext* primary();

  class  PrimaryValContext : public antlr4::ParserRuleContext {
  public:
    PrimaryValContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PrimaryValContext() = default;
    void copyFrom(PrimaryValContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  PrimaryValIntContext : public PrimaryValContext {
  public:
    PrimaryValIntContext(PrimaryValContext *ctx);

    antlr4::tree::TerminalNode *INT();
  };

  class  PrimaryValStrContext : public PrimaryValContext {
  public:
    PrimaryValStrContext(PrimaryValContext *ctx);

    antlr4::tree::TerminalNode *STRING();
  };

  class  PrimaryValHexContext : public PrimaryValContext {
  public:
    PrimaryValHexContext(PrimaryValContext *ctx);

    antlr4::tree::TerminalNode *HEX_INT();
  };

  PrimaryValContext* primaryVal();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool ruleExprSempred(RuleExprContext *_localctx, size_t predicateIndex);
  bool argExprSempred(ArgExprContext *_localctx, size_t predicateIndex);
  bool memExprSempred(MemExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

