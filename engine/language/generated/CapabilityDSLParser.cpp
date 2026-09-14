
// Generated from CapabilityDSL.g4 by ANTLR 4.10


#include "CapabilityDSLVisitor.h"

#include "CapabilityDSLParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct CapabilityDSLParserStaticData final {
  CapabilityDSLParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  CapabilityDSLParserStaticData(const CapabilityDSLParserStaticData&) = delete;
  CapabilityDSLParserStaticData(CapabilityDSLParserStaticData&&) = delete;
  CapabilityDSLParserStaticData& operator=(const CapabilityDSLParserStaticData&) = delete;
  CapabilityDSLParserStaticData& operator=(CapabilityDSLParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

std::once_flag capabilitydslParserOnceFlag;
CapabilityDSLParserStaticData *capabilitydslParserStaticData = nullptr;

void capabilitydslParserInitialize() {
  assert(capabilitydslParserStaticData == nullptr);
  auto staticData = std::make_unique<CapabilityDSLParserStaticData>(
    std::vector<std::string>{
      "ruleExpr", "apiCall", "apiName", "apiArgs", "apiArg", "argExpr", 
      "memExpr", "memDereference", "patternExpr", "patternElems", "patternElem", 
      "hexList", "intList", "primary", "primaryVal"
    },
    std::vector<std::string>{
      "", "'('", "')'", "','", "'['", "']'", "'@'", "':'", "'*'", "", "", 
      "", "", "'\\u003F'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "AND", "OR", "THEN", "NOT", "WILDCARD", 
      "HEX_INT", "INT", "IDENTIFIER", "STRING", "COMMENT", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,19,209,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,1,0,1,0,1,0,1,0,1,0,1,0,3,0,37,8,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,
  	1,0,5,0,48,8,0,10,0,12,0,51,9,0,1,1,1,1,1,1,1,1,1,1,1,2,1,2,1,3,1,3,1,
  	3,5,3,63,8,3,10,3,12,3,66,9,3,1,4,3,4,69,8,4,1,5,1,5,1,5,1,5,1,5,1,5,
  	1,5,1,5,1,5,3,5,80,8,5,1,5,1,5,1,5,5,5,85,8,5,10,5,12,5,88,9,5,1,6,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,6,3,6,98,8,6,1,6,1,6,1,6,1,6,1,6,1,6,5,6,106,
  	8,6,10,6,12,6,109,9,6,1,7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,3,8,128,8,8,1,9,1,9,1,9,1,9,1,9,5,9,135,8,9,10,9,
  	12,9,138,9,9,1,9,1,9,3,9,142,8,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,
  	10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,4,10,159,8,10,11,10,12,10,160,1,
  	10,1,10,1,10,4,10,166,8,10,11,10,12,10,167,3,10,170,8,10,1,11,1,11,1,
  	11,1,11,1,11,5,11,177,8,11,10,11,12,11,180,9,11,1,11,1,11,3,11,184,8,
  	11,1,12,1,12,1,12,1,12,1,12,5,12,191,8,12,10,12,12,12,194,9,12,1,12,1,
  	12,3,12,198,8,12,1,13,1,13,3,13,202,8,13,1,14,1,14,1,14,3,14,207,8,14,
  	1,14,0,3,0,10,12,15,0,2,4,6,8,10,12,14,16,18,20,22,24,26,28,0,0,228,0,
  	36,1,0,0,0,2,52,1,0,0,0,4,57,1,0,0,0,6,59,1,0,0,0,8,68,1,0,0,0,10,79,
  	1,0,0,0,12,97,1,0,0,0,14,110,1,0,0,0,16,127,1,0,0,0,18,141,1,0,0,0,20,
  	169,1,0,0,0,22,183,1,0,0,0,24,197,1,0,0,0,26,201,1,0,0,0,28,206,1,0,0,
  	0,30,31,6,0,-1,0,31,32,5,1,0,0,32,33,3,0,0,0,33,34,5,2,0,0,34,37,1,0,
  	0,0,35,37,3,2,1,0,36,30,1,0,0,0,36,35,1,0,0,0,37,49,1,0,0,0,38,39,10,
  	3,0,0,39,40,5,9,0,0,40,48,3,0,0,4,41,42,10,2,0,0,42,43,5,10,0,0,43,48,
  	3,0,0,3,44,45,10,1,0,0,45,46,5,11,0,0,46,48,3,0,0,2,47,38,1,0,0,0,47,
  	41,1,0,0,0,47,44,1,0,0,0,48,51,1,0,0,0,49,47,1,0,0,0,49,50,1,0,0,0,50,
  	1,1,0,0,0,51,49,1,0,0,0,52,53,3,4,2,0,53,54,5,1,0,0,54,55,3,6,3,0,55,
  	56,5,2,0,0,56,3,1,0,0,0,57,58,5,16,0,0,58,5,1,0,0,0,59,64,3,8,4,0,60,
  	61,5,3,0,0,61,63,3,8,4,0,62,60,1,0,0,0,63,66,1,0,0,0,64,62,1,0,0,0,64,
  	65,1,0,0,0,65,7,1,0,0,0,66,64,1,0,0,0,67,69,3,10,5,0,68,67,1,0,0,0,68,
  	69,1,0,0,0,69,9,1,0,0,0,70,71,6,5,-1,0,71,72,5,1,0,0,72,73,3,10,5,0,73,
  	74,5,2,0,0,74,80,1,0,0,0,75,76,5,12,0,0,76,80,3,10,5,4,77,80,3,12,6,0,
  	78,80,3,28,14,0,79,70,1,0,0,0,79,75,1,0,0,0,79,77,1,0,0,0,79,78,1,0,0,
  	0,80,86,1,0,0,0,81,82,10,3,0,0,82,83,5,10,0,0,83,85,3,10,5,4,84,81,1,
  	0,0,0,85,88,1,0,0,0,86,84,1,0,0,0,86,87,1,0,0,0,87,11,1,0,0,0,88,86,1,
  	0,0,0,89,90,6,6,-1,0,90,91,5,1,0,0,91,92,3,12,6,0,92,93,5,2,0,0,93,98,
  	1,0,0,0,94,95,5,12,0,0,95,98,3,12,6,4,96,98,3,14,7,0,97,89,1,0,0,0,97,
  	94,1,0,0,0,97,96,1,0,0,0,98,107,1,0,0,0,99,100,10,3,0,0,100,101,5,9,0,
  	0,101,106,3,12,6,4,102,103,10,2,0,0,103,104,5,10,0,0,104,106,3,12,6,3,
  	105,99,1,0,0,0,105,102,1,0,0,0,106,109,1,0,0,0,107,105,1,0,0,0,107,108,
  	1,0,0,0,108,13,1,0,0,0,109,107,1,0,0,0,110,111,5,4,0,0,111,112,3,16,8,
  	0,112,113,5,5,0,0,113,15,1,0,0,0,114,115,3,18,9,0,115,116,5,6,0,0,116,
  	117,3,26,13,0,117,128,1,0,0,0,118,119,3,18,9,0,119,120,5,7,0,0,120,128,
  	1,0,0,0,121,122,5,7,0,0,122,128,3,18,9,0,123,124,5,7,0,0,124,125,3,18,
  	9,0,125,126,5,7,0,0,126,128,1,0,0,0,127,114,1,0,0,0,127,118,1,0,0,0,127,
  	121,1,0,0,0,127,123,1,0,0,0,128,17,1,0,0,0,129,142,3,20,10,0,130,131,
  	5,1,0,0,131,136,3,18,9,0,132,133,5,3,0,0,133,135,3,18,9,0,134,132,1,0,
  	0,0,135,138,1,0,0,0,136,134,1,0,0,0,136,137,1,0,0,0,137,139,1,0,0,0,138,
  	136,1,0,0,0,139,140,5,2,0,0,140,142,1,0,0,0,141,129,1,0,0,0,141,130,1,
  	0,0,0,142,19,1,0,0,0,143,144,5,17,0,0,144,145,5,8,0,0,145,170,5,15,0,
  	0,146,170,5,17,0,0,147,148,3,22,11,0,148,149,5,8,0,0,149,150,5,15,0,0,
  	150,170,1,0,0,0,151,170,5,14,0,0,152,153,3,24,12,0,153,154,5,8,0,0,154,
  	155,5,15,0,0,155,170,1,0,0,0,156,170,5,15,0,0,157,159,5,13,0,0,158,157,
  	1,0,0,0,159,160,1,0,0,0,160,158,1,0,0,0,160,161,1,0,0,0,161,162,1,0,0,
  	0,162,163,5,8,0,0,163,170,5,15,0,0,164,166,5,13,0,0,165,164,1,0,0,0,166,
  	167,1,0,0,0,167,165,1,0,0,0,167,168,1,0,0,0,168,170,1,0,0,0,169,143,1,
  	0,0,0,169,146,1,0,0,0,169,147,1,0,0,0,169,151,1,0,0,0,169,152,1,0,0,0,
  	169,156,1,0,0,0,169,158,1,0,0,0,169,165,1,0,0,0,170,21,1,0,0,0,171,184,
  	5,14,0,0,172,173,5,1,0,0,173,178,3,22,11,0,174,175,5,3,0,0,175,177,3,
  	22,11,0,176,174,1,0,0,0,177,180,1,0,0,0,178,176,1,0,0,0,178,179,1,0,0,
  	0,179,181,1,0,0,0,180,178,1,0,0,0,181,182,5,2,0,0,182,184,1,0,0,0,183,
  	171,1,0,0,0,183,172,1,0,0,0,184,23,1,0,0,0,185,198,5,15,0,0,186,187,5,
  	1,0,0,187,192,3,24,12,0,188,189,5,3,0,0,189,191,3,24,12,0,190,188,1,0,
  	0,0,191,194,1,0,0,0,192,190,1,0,0,0,192,193,1,0,0,0,193,195,1,0,0,0,194,
  	192,1,0,0,0,195,196,5,2,0,0,196,198,1,0,0,0,197,185,1,0,0,0,197,186,1,
  	0,0,0,198,25,1,0,0,0,199,202,5,14,0,0,200,202,5,15,0,0,201,199,1,0,0,
  	0,201,200,1,0,0,0,202,27,1,0,0,0,203,207,5,14,0,0,204,207,5,15,0,0,205,
  	207,5,17,0,0,206,203,1,0,0,0,206,204,1,0,0,0,206,205,1,0,0,0,207,29,1,
  	0,0,0,22,36,47,49,64,68,79,86,97,105,107,127,136,141,160,167,169,178,
  	183,192,197,201,206
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  capabilitydslParserStaticData = staticData.release();
}

}

CapabilityDSLParser::CapabilityDSLParser(TokenStream *input) : CapabilityDSLParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

CapabilityDSLParser::CapabilityDSLParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  CapabilityDSLParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *capabilitydslParserStaticData->atn, capabilitydslParserStaticData->decisionToDFA, capabilitydslParserStaticData->sharedContextCache, options);
}

CapabilityDSLParser::~CapabilityDSLParser() {
  delete _interpreter;
}

const atn::ATN& CapabilityDSLParser::getATN() const {
  return *capabilitydslParserStaticData->atn;
}

std::string CapabilityDSLParser::getGrammarFileName() const {
  return "CapabilityDSL.g4";
}

const std::vector<std::string>& CapabilityDSLParser::getRuleNames() const {
  return capabilitydslParserStaticData->ruleNames;
}

const dfa::Vocabulary& CapabilityDSLParser::getVocabulary() const {
  return capabilitydslParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView CapabilityDSLParser::getSerializedATN() const {
  return capabilitydslParserStaticData->serializedATN;
}


//----------------- RuleExprContext ------------------------------------------------------------------

CapabilityDSLParser::RuleExprContext::RuleExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::RuleExprContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleRuleExpr;
}

void CapabilityDSLParser::RuleExprContext::copyFrom(RuleExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ParentNodeContext ------------------------------------------------------------------

CapabilityDSLParser::RuleExprContext* CapabilityDSLParser::ParentNodeContext::ruleExpr() {
  return getRuleContext<CapabilityDSLParser::RuleExprContext>(0);
}

CapabilityDSLParser::ParentNodeContext::ParentNodeContext(RuleExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ParentNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitParentNode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ThenNodeContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::RuleExprContext *> CapabilityDSLParser::ThenNodeContext::ruleExpr() {
  return getRuleContexts<CapabilityDSLParser::RuleExprContext>();
}

CapabilityDSLParser::RuleExprContext* CapabilityDSLParser::ThenNodeContext::ruleExpr(size_t i) {
  return getRuleContext<CapabilityDSLParser::RuleExprContext>(i);
}

tree::TerminalNode* CapabilityDSLParser::ThenNodeContext::THEN() {
  return getToken(CapabilityDSLParser::THEN, 0);
}

CapabilityDSLParser::ThenNodeContext::ThenNodeContext(RuleExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ThenNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitThenNode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndNodeContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::RuleExprContext *> CapabilityDSLParser::AndNodeContext::ruleExpr() {
  return getRuleContexts<CapabilityDSLParser::RuleExprContext>();
}

CapabilityDSLParser::RuleExprContext* CapabilityDSLParser::AndNodeContext::ruleExpr(size_t i) {
  return getRuleContext<CapabilityDSLParser::RuleExprContext>(i);
}

tree::TerminalNode* CapabilityDSLParser::AndNodeContext::AND() {
  return getToken(CapabilityDSLParser::AND, 0);
}

CapabilityDSLParser::AndNodeContext::AndNodeContext(RuleExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::AndNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitAndNode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- CallNodeContext ------------------------------------------------------------------

CapabilityDSLParser::ApiCallContext* CapabilityDSLParser::CallNodeContext::apiCall() {
  return getRuleContext<CapabilityDSLParser::ApiCallContext>(0);
}

CapabilityDSLParser::CallNodeContext::CallNodeContext(RuleExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::CallNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitCallNode(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrNodeContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::RuleExprContext *> CapabilityDSLParser::OrNodeContext::ruleExpr() {
  return getRuleContexts<CapabilityDSLParser::RuleExprContext>();
}

CapabilityDSLParser::RuleExprContext* CapabilityDSLParser::OrNodeContext::ruleExpr(size_t i) {
  return getRuleContext<CapabilityDSLParser::RuleExprContext>(i);
}

tree::TerminalNode* CapabilityDSLParser::OrNodeContext::OR() {
  return getToken(CapabilityDSLParser::OR, 0);
}

CapabilityDSLParser::OrNodeContext::OrNodeContext(RuleExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::OrNodeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitOrNode(this);
  else
    return visitor->visitChildren(this);
}

CapabilityDSLParser::RuleExprContext* CapabilityDSLParser::ruleExpr() {
   return ruleExpr(0);
}

CapabilityDSLParser::RuleExprContext* CapabilityDSLParser::ruleExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CapabilityDSLParser::RuleExprContext *_localctx = _tracker.createInstance<RuleExprContext>(_ctx, parentState);
  CapabilityDSLParser::RuleExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 0;
  enterRecursionRule(_localctx, 0, CapabilityDSLParser::RuleRuleExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(36);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CapabilityDSLParser::T__0: {
        _localctx = _tracker.createInstance<ParentNodeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(31);
        match(CapabilityDSLParser::T__0);
        setState(32);
        ruleExpr(0);
        setState(33);
        match(CapabilityDSLParser::T__1);
        break;
      }

      case CapabilityDSLParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<CallNodeContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(35);
        apiCall();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(49);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(47);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AndNodeContext>(_tracker.createInstance<RuleExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleRuleExpr);
          setState(38);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(39);
          match(CapabilityDSLParser::AND);
          setState(40);
          ruleExpr(4);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<OrNodeContext>(_tracker.createInstance<RuleExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleRuleExpr);
          setState(41);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(42);
          match(CapabilityDSLParser::OR);
          setState(43);
          ruleExpr(3);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ThenNodeContext>(_tracker.createInstance<RuleExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleRuleExpr);
          setState(44);

          if (!(precpred(_ctx, 1))) throw FailedPredicateException(this, "precpred(_ctx, 1)");
          setState(45);
          match(CapabilityDSLParser::THEN);
          setState(46);
          ruleExpr(2);
          break;
        }

        default:
          break;
        } 
      }
      setState(51);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ApiCallContext ------------------------------------------------------------------

CapabilityDSLParser::ApiCallContext::ApiCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::ApiCallContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleApiCall;
}

void CapabilityDSLParser::ApiCallContext::copyFrom(ApiCallContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ApiWithArgsContext ------------------------------------------------------------------

CapabilityDSLParser::ApiNameContext* CapabilityDSLParser::ApiWithArgsContext::apiName() {
  return getRuleContext<CapabilityDSLParser::ApiNameContext>(0);
}

CapabilityDSLParser::ApiArgsContext* CapabilityDSLParser::ApiWithArgsContext::apiArgs() {
  return getRuleContext<CapabilityDSLParser::ApiArgsContext>(0);
}

CapabilityDSLParser::ApiWithArgsContext::ApiWithArgsContext(ApiCallContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ApiWithArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitApiWithArgs(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::ApiCallContext* CapabilityDSLParser::apiCall() {
  ApiCallContext *_localctx = _tracker.createInstance<ApiCallContext>(_ctx, getState());
  enterRule(_localctx, 2, CapabilityDSLParser::RuleApiCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<CapabilityDSLParser::ApiWithArgsContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(52);
    apiName();
    setState(53);
    match(CapabilityDSLParser::T__0);
    setState(54);
    apiArgs();
    setState(55);
    match(CapabilityDSLParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ApiNameContext ------------------------------------------------------------------

CapabilityDSLParser::ApiNameContext::ApiNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::ApiNameContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleApiName;
}

void CapabilityDSLParser::ApiNameContext::copyFrom(ApiNameContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- IdentifierNameContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::IdentifierNameContext::IDENTIFIER() {
  return getToken(CapabilityDSLParser::IDENTIFIER, 0);
}

CapabilityDSLParser::IdentifierNameContext::IdentifierNameContext(ApiNameContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::IdentifierNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitIdentifierName(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::ApiNameContext* CapabilityDSLParser::apiName() {
  ApiNameContext *_localctx = _tracker.createInstance<ApiNameContext>(_ctx, getState());
  enterRule(_localctx, 4, CapabilityDSLParser::RuleApiName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<CapabilityDSLParser::IdentifierNameContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(57);
    match(CapabilityDSLParser::IDENTIFIER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ApiArgsContext ------------------------------------------------------------------

CapabilityDSLParser::ApiArgsContext::ApiArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::ApiArgsContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleApiArgs;
}

void CapabilityDSLParser::ApiArgsContext::copyFrom(ApiArgsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ArgListContainerContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::ApiArgContext *> CapabilityDSLParser::ArgListContainerContext::apiArg() {
  return getRuleContexts<CapabilityDSLParser::ApiArgContext>();
}

CapabilityDSLParser::ApiArgContext* CapabilityDSLParser::ArgListContainerContext::apiArg(size_t i) {
  return getRuleContext<CapabilityDSLParser::ApiArgContext>(i);
}

CapabilityDSLParser::ArgListContainerContext::ArgListContainerContext(ApiArgsContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ArgListContainerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitArgListContainer(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::ApiArgsContext* CapabilityDSLParser::apiArgs() {
  ApiArgsContext *_localctx = _tracker.createInstance<ApiArgsContext>(_ctx, getState());
  enterRule(_localctx, 6, CapabilityDSLParser::RuleApiArgs);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<CapabilityDSLParser::ArgListContainerContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(59);
    apiArg();
    setState(64);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CapabilityDSLParser::T__2) {
      setState(60);
      match(CapabilityDSLParser::T__2);
      setState(61);
      apiArg();
      setState(66);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ApiArgContext ------------------------------------------------------------------

CapabilityDSLParser::ApiArgContext::ApiArgContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CapabilityDSLParser::ArgExprContext* CapabilityDSLParser::ApiArgContext::argExpr() {
  return getRuleContext<CapabilityDSLParser::ArgExprContext>(0);
}


size_t CapabilityDSLParser::ApiArgContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleApiArg;
}


std::any CapabilityDSLParser::ApiArgContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitApiArg(this);
  else
    return visitor->visitChildren(this);
}

CapabilityDSLParser::ApiArgContext* CapabilityDSLParser::apiArg() {
  ApiArgContext *_localctx = _tracker.createInstance<ApiArgContext>(_ctx, getState());
  enterRule(_localctx, 8, CapabilityDSLParser::RuleApiArg);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(68);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CapabilityDSLParser::T__0)
      | (1ULL << CapabilityDSLParser::T__3)
      | (1ULL << CapabilityDSLParser::NOT)
      | (1ULL << CapabilityDSLParser::HEX_INT)
      | (1ULL << CapabilityDSLParser::INT)
      | (1ULL << CapabilityDSLParser::STRING))) != 0)) {
      setState(67);
      argExpr(0);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgExprContext ------------------------------------------------------------------

CapabilityDSLParser::ArgExprContext::ArgExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::ArgExprContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleArgExpr;
}

void CapabilityDSLParser::ArgExprContext::copyFrom(ArgExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ArgOrContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::ArgExprContext *> CapabilityDSLParser::ArgOrContext::argExpr() {
  return getRuleContexts<CapabilityDSLParser::ArgExprContext>();
}

CapabilityDSLParser::ArgExprContext* CapabilityDSLParser::ArgOrContext::argExpr(size_t i) {
  return getRuleContext<CapabilityDSLParser::ArgExprContext>(i);
}

tree::TerminalNode* CapabilityDSLParser::ArgOrContext::OR() {
  return getToken(CapabilityDSLParser::OR, 0);
}

CapabilityDSLParser::ArgOrContext::ArgOrContext(ArgExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ArgOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitArgOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryValueContext ------------------------------------------------------------------

CapabilityDSLParser::PrimaryValContext* CapabilityDSLParser::PrimaryValueContext::primaryVal() {
  return getRuleContext<CapabilityDSLParser::PrimaryValContext>(0);
}

CapabilityDSLParser::PrimaryValueContext::PrimaryValueContext(ArgExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::PrimaryValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitPrimaryValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemMatchContext ------------------------------------------------------------------

CapabilityDSLParser::MemExprContext* CapabilityDSLParser::MemMatchContext::memExpr() {
  return getRuleContext<CapabilityDSLParser::MemExprContext>(0);
}

CapabilityDSLParser::MemMatchContext::MemMatchContext(ArgExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MemMatchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMemMatch(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArgNotContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::ArgNotContext::NOT() {
  return getToken(CapabilityDSLParser::NOT, 0);
}

CapabilityDSLParser::ArgExprContext* CapabilityDSLParser::ArgNotContext::argExpr() {
  return getRuleContext<CapabilityDSLParser::ArgExprContext>(0);
}

CapabilityDSLParser::ArgNotContext::ArgNotContext(ArgExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ArgNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitArgNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ArgParenContext ------------------------------------------------------------------

CapabilityDSLParser::ArgExprContext* CapabilityDSLParser::ArgParenContext::argExpr() {
  return getRuleContext<CapabilityDSLParser::ArgExprContext>(0);
}

CapabilityDSLParser::ArgParenContext::ArgParenContext(ArgExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ArgParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitArgParen(this);
  else
    return visitor->visitChildren(this);
}

CapabilityDSLParser::ArgExprContext* CapabilityDSLParser::argExpr() {
   return argExpr(0);
}

CapabilityDSLParser::ArgExprContext* CapabilityDSLParser::argExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CapabilityDSLParser::ArgExprContext *_localctx = _tracker.createInstance<ArgExprContext>(_ctx, parentState);
  CapabilityDSLParser::ArgExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 10;
  enterRecursionRule(_localctx, 10, CapabilityDSLParser::RuleArgExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(79);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ArgParenContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(71);
      match(CapabilityDSLParser::T__0);
      setState(72);
      argExpr(0);
      setState(73);
      match(CapabilityDSLParser::T__1);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<ArgNotContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(75);
      match(CapabilityDSLParser::NOT);
      setState(76);
      argExpr(4);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<MemMatchContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(77);
      memExpr(0);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<PrimaryValueContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(78);
      primaryVal();
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(86);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        auto newContext = _tracker.createInstance<ArgOrContext>(_tracker.createInstance<ArgExprContext>(parentContext, parentState));
        _localctx = newContext;
        pushNewRecursionContext(newContext, startState, RuleArgExpr);
        setState(81);

        if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
        setState(82);
        match(CapabilityDSLParser::OR);
        setState(83);
        argExpr(4); 
      }
      setState(88);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MemExprContext ------------------------------------------------------------------

CapabilityDSLParser::MemExprContext::MemExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::MemExprContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleMemExpr;
}

void CapabilityDSLParser::MemExprContext::copyFrom(MemExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MemParenContext ------------------------------------------------------------------

CapabilityDSLParser::MemExprContext* CapabilityDSLParser::MemParenContext::memExpr() {
  return getRuleContext<CapabilityDSLParser::MemExprContext>(0);
}

CapabilityDSLParser::MemParenContext::MemParenContext(MemExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MemParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMemParen(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemAndContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::MemExprContext *> CapabilityDSLParser::MemAndContext::memExpr() {
  return getRuleContexts<CapabilityDSLParser::MemExprContext>();
}

CapabilityDSLParser::MemExprContext* CapabilityDSLParser::MemAndContext::memExpr(size_t i) {
  return getRuleContext<CapabilityDSLParser::MemExprContext>(i);
}

tree::TerminalNode* CapabilityDSLParser::MemAndContext::AND() {
  return getToken(CapabilityDSLParser::AND, 0);
}

CapabilityDSLParser::MemAndContext::MemAndContext(MemExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MemAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMemAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemOrContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::MemExprContext *> CapabilityDSLParser::MemOrContext::memExpr() {
  return getRuleContexts<CapabilityDSLParser::MemExprContext>();
}

CapabilityDSLParser::MemExprContext* CapabilityDSLParser::MemOrContext::memExpr(size_t i) {
  return getRuleContext<CapabilityDSLParser::MemExprContext>(i);
}

tree::TerminalNode* CapabilityDSLParser::MemOrContext::OR() {
  return getToken(CapabilityDSLParser::OR, 0);
}

CapabilityDSLParser::MemOrContext::MemOrContext(MemExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MemOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMemOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemNotContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::MemNotContext::NOT() {
  return getToken(CapabilityDSLParser::NOT, 0);
}

CapabilityDSLParser::MemExprContext* CapabilityDSLParser::MemNotContext::memExpr() {
  return getRuleContext<CapabilityDSLParser::MemExprContext>(0);
}

CapabilityDSLParser::MemNotContext::MemNotContext(MemExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MemNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMemNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MemLeafContext ------------------------------------------------------------------

CapabilityDSLParser::MemDereferenceContext* CapabilityDSLParser::MemLeafContext::memDereference() {
  return getRuleContext<CapabilityDSLParser::MemDereferenceContext>(0);
}

CapabilityDSLParser::MemLeafContext::MemLeafContext(MemExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MemLeafContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMemLeaf(this);
  else
    return visitor->visitChildren(this);
}

CapabilityDSLParser::MemExprContext* CapabilityDSLParser::memExpr() {
   return memExpr(0);
}

CapabilityDSLParser::MemExprContext* CapabilityDSLParser::memExpr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CapabilityDSLParser::MemExprContext *_localctx = _tracker.createInstance<MemExprContext>(_ctx, parentState);
  CapabilityDSLParser::MemExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 12;
  enterRecursionRule(_localctx, 12, CapabilityDSLParser::RuleMemExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(97);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CapabilityDSLParser::T__0: {
        _localctx = _tracker.createInstance<MemParenContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(90);
        match(CapabilityDSLParser::T__0);
        setState(91);
        memExpr(0);
        setState(92);
        match(CapabilityDSLParser::T__1);
        break;
      }

      case CapabilityDSLParser::NOT: {
        _localctx = _tracker.createInstance<MemNotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(94);
        match(CapabilityDSLParser::NOT);
        setState(95);
        memExpr(4);
        break;
      }

      case CapabilityDSLParser::T__3: {
        _localctx = _tracker.createInstance<MemLeafContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(96);
        memDereference();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(107);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(105);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<MemAndContext>(_tracker.createInstance<MemExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleMemExpr);
          setState(99);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(100);
          match(CapabilityDSLParser::AND);
          setState(101);
          memExpr(4);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<MemOrContext>(_tracker.createInstance<MemExprContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleMemExpr);
          setState(102);

          if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
          setState(103);
          match(CapabilityDSLParser::OR);
          setState(104);
          memExpr(3);
          break;
        }

        default:
          break;
        } 
      }
      setState(109);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MemDereferenceContext ------------------------------------------------------------------

CapabilityDSLParser::MemDereferenceContext::MemDereferenceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::MemDereferenceContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleMemDereference;
}

void CapabilityDSLParser::MemDereferenceContext::copyFrom(MemDereferenceContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MemDerefContext ------------------------------------------------------------------

CapabilityDSLParser::PatternExprContext* CapabilityDSLParser::MemDerefContext::patternExpr() {
  return getRuleContext<CapabilityDSLParser::PatternExprContext>(0);
}

CapabilityDSLParser::MemDerefContext::MemDerefContext(MemDereferenceContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MemDerefContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMemDeref(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::MemDereferenceContext* CapabilityDSLParser::memDereference() {
  MemDereferenceContext *_localctx = _tracker.createInstance<MemDereferenceContext>(_ctx, getState());
  enterRule(_localctx, 14, CapabilityDSLParser::RuleMemDereference);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    _localctx = _tracker.createInstance<CapabilityDSLParser::MemDerefContext>(_localctx);
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(CapabilityDSLParser::T__3);
    setState(111);
    patternExpr();
    setState(112);
    match(CapabilityDSLParser::T__4);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternExprContext ------------------------------------------------------------------

CapabilityDSLParser::PatternExprContext::PatternExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::PatternExprContext::getRuleIndex() const {
  return CapabilityDSLParser::RulePatternExpr;
}

void CapabilityDSLParser::PatternExprContext::copyFrom(PatternExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- OffsetPatternContext ------------------------------------------------------------------

CapabilityDSLParser::PatternElemsContext* CapabilityDSLParser::OffsetPatternContext::patternElems() {
  return getRuleContext<CapabilityDSLParser::PatternElemsContext>(0);
}

CapabilityDSLParser::PrimaryContext* CapabilityDSLParser::OffsetPatternContext::primary() {
  return getRuleContext<CapabilityDSLParser::PrimaryContext>(0);
}

CapabilityDSLParser::OffsetPatternContext::OffsetPatternContext(PatternExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::OffsetPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitOffsetPattern(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SuffixPatternContext ------------------------------------------------------------------

CapabilityDSLParser::PatternElemsContext* CapabilityDSLParser::SuffixPatternContext::patternElems() {
  return getRuleContext<CapabilityDSLParser::PatternElemsContext>(0);
}

CapabilityDSLParser::SuffixPatternContext::SuffixPatternContext(PatternExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::SuffixPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitSuffixPattern(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrefixPatternContext ------------------------------------------------------------------

CapabilityDSLParser::PatternElemsContext* CapabilityDSLParser::PrefixPatternContext::patternElems() {
  return getRuleContext<CapabilityDSLParser::PatternElemsContext>(0);
}

CapabilityDSLParser::PrefixPatternContext::PrefixPatternContext(PatternExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::PrefixPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitPrefixPattern(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ContainsPatternContext ------------------------------------------------------------------

CapabilityDSLParser::PatternElemsContext* CapabilityDSLParser::ContainsPatternContext::patternElems() {
  return getRuleContext<CapabilityDSLParser::PatternElemsContext>(0);
}

CapabilityDSLParser::ContainsPatternContext::ContainsPatternContext(PatternExprContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ContainsPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitContainsPattern(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::PatternExprContext* CapabilityDSLParser::patternExpr() {
  PatternExprContext *_localctx = _tracker.createInstance<PatternExprContext>(_ctx, getState());
  enterRule(_localctx, 16, CapabilityDSLParser::RulePatternExpr);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(127);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::OffsetPatternContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(114);
      patternElems();
      setState(115);
      match(CapabilityDSLParser::T__5);
      setState(116);
      primary();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::PrefixPatternContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(118);
      patternElems();
      setState(119);
      match(CapabilityDSLParser::T__6);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::SuffixPatternContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(121);
      match(CapabilityDSLParser::T__6);
      setState(122);
      patternElems();
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ContainsPatternContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(123);
      match(CapabilityDSLParser::T__6);
      setState(124);
      patternElems();
      setState(125);
      match(CapabilityDSLParser::T__6);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternElemsContext ------------------------------------------------------------------

CapabilityDSLParser::PatternElemsContext::PatternElemsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::PatternElemsContext::getRuleIndex() const {
  return CapabilityDSLParser::RulePatternElems;
}

void CapabilityDSLParser::PatternElemsContext::copyFrom(PatternElemsContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MultiElemsContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::PatternElemsContext *> CapabilityDSLParser::MultiElemsContext::patternElems() {
  return getRuleContexts<CapabilityDSLParser::PatternElemsContext>();
}

CapabilityDSLParser::PatternElemsContext* CapabilityDSLParser::MultiElemsContext::patternElems(size_t i) {
  return getRuleContext<CapabilityDSLParser::PatternElemsContext>(i);
}

CapabilityDSLParser::MultiElemsContext::MultiElemsContext(PatternElemsContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MultiElemsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMultiElems(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleElemContext ------------------------------------------------------------------

CapabilityDSLParser::PatternElemContext* CapabilityDSLParser::SingleElemContext::patternElem() {
  return getRuleContext<CapabilityDSLParser::PatternElemContext>(0);
}

CapabilityDSLParser::SingleElemContext::SingleElemContext(PatternElemsContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::SingleElemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitSingleElem(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::PatternElemsContext* CapabilityDSLParser::patternElems() {
  PatternElemsContext *_localctx = _tracker.createInstance<PatternElemsContext>(_ctx, getState());
  enterRule(_localctx, 18, CapabilityDSLParser::RulePatternElems);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(141);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::SingleElemContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(129);
      patternElem();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::MultiElemsContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(130);
      match(CapabilityDSLParser::T__0);
      setState(131);
      patternElems();
      setState(136);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CapabilityDSLParser::T__2) {
        setState(132);
        match(CapabilityDSLParser::T__2);
        setState(133);
        patternElems();
        setState(138);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(139);
      match(CapabilityDSLParser::T__1);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PatternElemContext ------------------------------------------------------------------

CapabilityDSLParser::PatternElemContext::PatternElemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::PatternElemContext::getRuleIndex() const {
  return CapabilityDSLParser::RulePatternElem;
}

void CapabilityDSLParser::PatternElemContext::copyFrom(PatternElemContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ElemIntRepeatContext ------------------------------------------------------------------

CapabilityDSLParser::IntListContext* CapabilityDSLParser::ElemIntRepeatContext::intList() {
  return getRuleContext<CapabilityDSLParser::IntListContext>(0);
}

tree::TerminalNode* CapabilityDSLParser::ElemIntRepeatContext::INT() {
  return getToken(CapabilityDSLParser::INT, 0);
}

CapabilityDSLParser::ElemIntRepeatContext::ElemIntRepeatContext(PatternElemContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ElemIntRepeatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitElemIntRepeat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ElemWildcardRepeatContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::ElemWildcardRepeatContext::INT() {
  return getToken(CapabilityDSLParser::INT, 0);
}

std::vector<tree::TerminalNode *> CapabilityDSLParser::ElemWildcardRepeatContext::WILDCARD() {
  return getTokens(CapabilityDSLParser::WILDCARD);
}

tree::TerminalNode* CapabilityDSLParser::ElemWildcardRepeatContext::WILDCARD(size_t i) {
  return getToken(CapabilityDSLParser::WILDCARD, i);
}

CapabilityDSLParser::ElemWildcardRepeatContext::ElemWildcardRepeatContext(PatternElemContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ElemWildcardRepeatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitElemWildcardRepeat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ElemWildcardContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> CapabilityDSLParser::ElemWildcardContext::WILDCARD() {
  return getTokens(CapabilityDSLParser::WILDCARD);
}

tree::TerminalNode* CapabilityDSLParser::ElemWildcardContext::WILDCARD(size_t i) {
  return getToken(CapabilityDSLParser::WILDCARD, i);
}

CapabilityDSLParser::ElemWildcardContext::ElemWildcardContext(PatternElemContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ElemWildcardContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitElemWildcard(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ElemStringContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::ElemStringContext::STRING() {
  return getToken(CapabilityDSLParser::STRING, 0);
}

CapabilityDSLParser::ElemStringContext::ElemStringContext(PatternElemContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ElemStringContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitElemString(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ElemHexRepeatContext ------------------------------------------------------------------

CapabilityDSLParser::HexListContext* CapabilityDSLParser::ElemHexRepeatContext::hexList() {
  return getRuleContext<CapabilityDSLParser::HexListContext>(0);
}

tree::TerminalNode* CapabilityDSLParser::ElemHexRepeatContext::INT() {
  return getToken(CapabilityDSLParser::INT, 0);
}

CapabilityDSLParser::ElemHexRepeatContext::ElemHexRepeatContext(PatternElemContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ElemHexRepeatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitElemHexRepeat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ElemStringRepeatContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::ElemStringRepeatContext::STRING() {
  return getToken(CapabilityDSLParser::STRING, 0);
}

tree::TerminalNode* CapabilityDSLParser::ElemStringRepeatContext::INT() {
  return getToken(CapabilityDSLParser::INT, 0);
}

CapabilityDSLParser::ElemStringRepeatContext::ElemStringRepeatContext(PatternElemContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ElemStringRepeatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitElemStringRepeat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ElemHexContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::ElemHexContext::HEX_INT() {
  return getToken(CapabilityDSLParser::HEX_INT, 0);
}

CapabilityDSLParser::ElemHexContext::ElemHexContext(PatternElemContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ElemHexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitElemHex(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ElemIntContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::ElemIntContext::INT() {
  return getToken(CapabilityDSLParser::INT, 0);
}

CapabilityDSLParser::ElemIntContext::ElemIntContext(PatternElemContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::ElemIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitElemInt(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::PatternElemContext* CapabilityDSLParser::patternElem() {
  PatternElemContext *_localctx = _tracker.createInstance<PatternElemContext>(_ctx, getState());
  enterRule(_localctx, 20, CapabilityDSLParser::RulePatternElem);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(169);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ElemStringRepeatContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(143);
      match(CapabilityDSLParser::STRING);
      setState(144);
      match(CapabilityDSLParser::T__7);
      setState(145);
      match(CapabilityDSLParser::INT);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ElemStringContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(146);
      match(CapabilityDSLParser::STRING);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ElemHexRepeatContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(147);
      hexList();
      setState(148);
      match(CapabilityDSLParser::T__7);
      setState(149);
      match(CapabilityDSLParser::INT);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ElemHexContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(151);
      match(CapabilityDSLParser::HEX_INT);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ElemIntRepeatContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(152);
      intList();
      setState(153);
      match(CapabilityDSLParser::T__7);
      setState(154);
      match(CapabilityDSLParser::INT);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ElemIntContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(156);
      match(CapabilityDSLParser::INT);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ElemWildcardRepeatContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(158); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(157);
        match(CapabilityDSLParser::WILDCARD);
        setState(160); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == CapabilityDSLParser::WILDCARD);
      setState(162);
      match(CapabilityDSLParser::T__7);
      setState(163);
      match(CapabilityDSLParser::INT);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<CapabilityDSLParser::ElemWildcardContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(165); 
      _errHandler->sync(this);
      _la = _input->LA(1);
      do {
        setState(164);
        match(CapabilityDSLParser::WILDCARD);
        setState(167); 
        _errHandler->sync(this);
        _la = _input->LA(1);
      } while (_la == CapabilityDSLParser::WILDCARD);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- HexListContext ------------------------------------------------------------------

CapabilityDSLParser::HexListContext::HexListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::HexListContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleHexList;
}

void CapabilityDSLParser::HexListContext::copyFrom(HexListContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MultiHexContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::HexListContext *> CapabilityDSLParser::MultiHexContext::hexList() {
  return getRuleContexts<CapabilityDSLParser::HexListContext>();
}

CapabilityDSLParser::HexListContext* CapabilityDSLParser::MultiHexContext::hexList(size_t i) {
  return getRuleContext<CapabilityDSLParser::HexListContext>(i);
}

CapabilityDSLParser::MultiHexContext::MultiHexContext(HexListContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MultiHexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMultiHex(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleHexContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::SingleHexContext::HEX_INT() {
  return getToken(CapabilityDSLParser::HEX_INT, 0);
}

CapabilityDSLParser::SingleHexContext::SingleHexContext(HexListContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::SingleHexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitSingleHex(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::HexListContext* CapabilityDSLParser::hexList() {
  HexListContext *_localctx = _tracker.createInstance<HexListContext>(_ctx, getState());
  enterRule(_localctx, 22, CapabilityDSLParser::RuleHexList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(183);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CapabilityDSLParser::HEX_INT: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::SingleHexContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(171);
        match(CapabilityDSLParser::HEX_INT);
        break;
      }

      case CapabilityDSLParser::T__0: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::MultiHexContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(172);
        match(CapabilityDSLParser::T__0);
        setState(173);
        hexList();
        setState(178);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CapabilityDSLParser::T__2) {
          setState(174);
          match(CapabilityDSLParser::T__2);
          setState(175);
          hexList();
          setState(180);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(181);
        match(CapabilityDSLParser::T__1);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntListContext ------------------------------------------------------------------

CapabilityDSLParser::IntListContext::IntListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::IntListContext::getRuleIndex() const {
  return CapabilityDSLParser::RuleIntList;
}

void CapabilityDSLParser::IntListContext::copyFrom(IntListContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- MultiIntContext ------------------------------------------------------------------

std::vector<CapabilityDSLParser::IntListContext *> CapabilityDSLParser::MultiIntContext::intList() {
  return getRuleContexts<CapabilityDSLParser::IntListContext>();
}

CapabilityDSLParser::IntListContext* CapabilityDSLParser::MultiIntContext::intList(size_t i) {
  return getRuleContext<CapabilityDSLParser::IntListContext>(i);
}

CapabilityDSLParser::MultiIntContext::MultiIntContext(IntListContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::MultiIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitMultiInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SingleIntContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::SingleIntContext::INT() {
  return getToken(CapabilityDSLParser::INT, 0);
}

CapabilityDSLParser::SingleIntContext::SingleIntContext(IntListContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::SingleIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitSingleInt(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::IntListContext* CapabilityDSLParser::intList() {
  IntListContext *_localctx = _tracker.createInstance<IntListContext>(_ctx, getState());
  enterRule(_localctx, 24, CapabilityDSLParser::RuleIntList);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(197);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CapabilityDSLParser::INT: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::SingleIntContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(185);
        match(CapabilityDSLParser::INT);
        break;
      }

      case CapabilityDSLParser::T__0: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::MultiIntContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(186);
        match(CapabilityDSLParser::T__0);
        setState(187);
        intList();
        setState(192);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CapabilityDSLParser::T__2) {
          setState(188);
          match(CapabilityDSLParser::T__2);
          setState(189);
          intList();
          setState(194);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        setState(195);
        match(CapabilityDSLParser::T__1);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryContext ------------------------------------------------------------------

CapabilityDSLParser::PrimaryContext::PrimaryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::PrimaryContext::getRuleIndex() const {
  return CapabilityDSLParser::RulePrimary;
}

void CapabilityDSLParser::PrimaryContext::copyFrom(PrimaryContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PrimaryIntContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::PrimaryIntContext::INT() {
  return getToken(CapabilityDSLParser::INT, 0);
}

CapabilityDSLParser::PrimaryIntContext::PrimaryIntContext(PrimaryContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::PrimaryIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitPrimaryInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryHexContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::PrimaryHexContext::HEX_INT() {
  return getToken(CapabilityDSLParser::HEX_INT, 0);
}

CapabilityDSLParser::PrimaryHexContext::PrimaryHexContext(PrimaryContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::PrimaryHexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitPrimaryHex(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::PrimaryContext* CapabilityDSLParser::primary() {
  PrimaryContext *_localctx = _tracker.createInstance<PrimaryContext>(_ctx, getState());
  enterRule(_localctx, 26, CapabilityDSLParser::RulePrimary);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(201);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CapabilityDSLParser::HEX_INT: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::PrimaryHexContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(199);
        match(CapabilityDSLParser::HEX_INT);
        break;
      }

      case CapabilityDSLParser::INT: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::PrimaryIntContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(200);
        match(CapabilityDSLParser::INT);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PrimaryValContext ------------------------------------------------------------------

CapabilityDSLParser::PrimaryValContext::PrimaryValContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CapabilityDSLParser::PrimaryValContext::getRuleIndex() const {
  return CapabilityDSLParser::RulePrimaryVal;
}

void CapabilityDSLParser::PrimaryValContext::copyFrom(PrimaryValContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- PrimaryValIntContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::PrimaryValIntContext::INT() {
  return getToken(CapabilityDSLParser::INT, 0);
}

CapabilityDSLParser::PrimaryValIntContext::PrimaryValIntContext(PrimaryValContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::PrimaryValIntContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitPrimaryValInt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryValStrContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::PrimaryValStrContext::STRING() {
  return getToken(CapabilityDSLParser::STRING, 0);
}

CapabilityDSLParser::PrimaryValStrContext::PrimaryValStrContext(PrimaryValContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::PrimaryValStrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitPrimaryValStr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- PrimaryValHexContext ------------------------------------------------------------------

tree::TerminalNode* CapabilityDSLParser::PrimaryValHexContext::HEX_INT() {
  return getToken(CapabilityDSLParser::HEX_INT, 0);
}

CapabilityDSLParser::PrimaryValHexContext::PrimaryValHexContext(PrimaryValContext *ctx) { copyFrom(ctx); }


std::any CapabilityDSLParser::PrimaryValHexContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CapabilityDSLVisitor*>(visitor))
    return parserVisitor->visitPrimaryValHex(this);
  else
    return visitor->visitChildren(this);
}
CapabilityDSLParser::PrimaryValContext* CapabilityDSLParser::primaryVal() {
  PrimaryValContext *_localctx = _tracker.createInstance<PrimaryValContext>(_ctx, getState());
  enterRule(_localctx, 28, CapabilityDSLParser::RulePrimaryVal);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(206);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CapabilityDSLParser::HEX_INT: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::PrimaryValHexContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(203);
        match(CapabilityDSLParser::HEX_INT);
        break;
      }

      case CapabilityDSLParser::INT: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::PrimaryValIntContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(204);
        match(CapabilityDSLParser::INT);
        break;
      }

      case CapabilityDSLParser::STRING: {
        _localctx = _tracker.createInstance<CapabilityDSLParser::PrimaryValStrContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(205);
        match(CapabilityDSLParser::STRING);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool CapabilityDSLParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 0: return ruleExprSempred(antlrcpp::downCast<RuleExprContext *>(context), predicateIndex);
    case 5: return argExprSempred(antlrcpp::downCast<ArgExprContext *>(context), predicateIndex);
    case 6: return memExprSempred(antlrcpp::downCast<MemExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CapabilityDSLParser::ruleExprSempred(RuleExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 3);
    case 1: return precpred(_ctx, 2);
    case 2: return precpred(_ctx, 1);

  default:
    break;
  }
  return true;
}

bool CapabilityDSLParser::argExprSempred(ArgExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool CapabilityDSLParser::memExprSempred(MemExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return precpred(_ctx, 3);
    case 5: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

void CapabilityDSLParser::initialize() {
  std::call_once(capabilitydslParserOnceFlag, capabilitydslParserInitialize);
}
