
// Generated from Hml.g4 by ANTLR 4.13.2


#include "HmlListener.h"
#include "HmlVisitor.h"

#include "HmlParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct HmlParserStaticData final {
  HmlParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  HmlParserStaticData(const HmlParserStaticData&) = delete;
  HmlParserStaticData(HmlParserStaticData&&) = delete;
  HmlParserStaticData& operator=(const HmlParserStaticData&) = delete;
  HmlParserStaticData& operator=(HmlParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag hmlParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<HmlParserStaticData> hmlParserStaticData = nullptr;

void hmlParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (hmlParserStaticData != nullptr) {
    return;
  }
#else
  assert(hmlParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<HmlParserStaticData>(
    std::vector<std::string>{
      "hml", "element", "elementBody", "includeStatement", "importStatement", 
      "variableDeclaration", "signalDeclaration", "typeAnnotation", "parameterList", 
      "parameter", "conditionalStatement", "conditionalExpression", "property", 
      "propertyName", "eventHandler", "propertyValue", "complexExpression", 
      "scriptStatement", "functionCall", "argumentList", "elementType"
    },
    std::vector<std::string>{
      "", "'='", "'int'", "'string'", "'bool'", "'any'", "'on'", "'+'", 
      "'-'", "'*'", "'/'", "'include'", "'import'", "'script'", "'defer'", 
      "'async'", "'var'", "'signal'", "'if'", "'else'", "'=='", "'!='", 
      "'>'", "'<'", "'>='", "'<='", "'&&'", "'||'", "'!'", "", "", "", "", 
      "", "", "", "", "", "", "'{'", "'}'", "'('", "')'", "':'", "','", 
      "';'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "INCLUDE", "IMPORT", "SCRIPT", 
      "DEFER", "ASYNC", "VAR", "SIGNAL", "IF", "ELSE", "EQ", "NE", "GT", 
      "LT", "GE", "LE", "AND", "OR", "NOT", "ID", "STRING", "SCRIPT_CONTENT", 
      "EXPRESSION", "NUMBER", "COLOR", "BOOLEAN", "WS", "LINE_COMMENT", 
      "BLOCK_COMMENT", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "COLON", 
      "COMMA", "SEMICOLON"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,45,267,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,2,18,7,18,2,19,7,19,2,20,7,20,1,0,5,
  	0,44,8,0,10,0,12,0,47,9,0,1,0,5,0,50,8,0,10,0,12,0,53,9,0,1,0,1,0,4,0,
  	57,8,0,11,0,12,0,58,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,72,
  	8,1,1,2,1,2,1,2,1,2,1,2,1,2,1,2,4,2,81,8,2,11,2,12,2,82,1,3,1,3,1,3,1,
  	4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,1,5,3,5,102,8,5,1,6,
  	1,6,1,6,1,6,3,6,108,8,6,1,6,1,6,1,7,1,7,1,8,1,8,1,8,5,8,117,8,8,10,8,
  	12,8,120,9,8,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,10,1,10,1,10,1,10,
  	1,10,1,10,1,10,1,10,3,10,138,8,10,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,1,11,1,11,1,11,1,11,1,11,3,11,167,8,11,1,11,1,11,1,11,1,11,1,11,
  	1,11,5,11,175,8,11,10,11,12,11,178,9,11,1,12,1,12,1,12,1,12,1,12,1,12,
  	1,12,1,12,3,12,188,8,12,1,13,1,13,1,14,1,14,1,14,1,15,1,15,1,15,1,15,
  	1,15,1,15,1,15,1,15,1,15,3,15,204,8,15,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,3,16,213,8,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,1,16,
  	1,16,1,16,5,16,227,8,16,10,16,12,16,230,9,16,1,17,1,17,1,17,1,17,1,17,
  	1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,1,17,3,17,248,8,17,
  	1,18,1,18,1,18,3,18,253,8,18,1,18,1,18,1,19,1,19,1,19,5,19,260,8,19,10,
  	19,12,19,263,9,19,1,20,1,20,1,20,0,2,22,32,21,0,2,4,6,8,10,12,14,16,18,
  	20,22,24,26,28,30,32,34,36,38,40,0,1,1,0,2,5,294,0,45,1,0,0,0,2,71,1,
  	0,0,0,4,80,1,0,0,0,6,84,1,0,0,0,8,87,1,0,0,0,10,101,1,0,0,0,12,103,1,
  	0,0,0,14,111,1,0,0,0,16,113,1,0,0,0,18,121,1,0,0,0,20,125,1,0,0,0,22,
  	166,1,0,0,0,24,187,1,0,0,0,26,189,1,0,0,0,28,191,1,0,0,0,30,203,1,0,0,
  	0,32,212,1,0,0,0,34,247,1,0,0,0,36,249,1,0,0,0,38,256,1,0,0,0,40,264,
  	1,0,0,0,42,44,3,8,4,0,43,42,1,0,0,0,44,47,1,0,0,0,45,43,1,0,0,0,45,46,
  	1,0,0,0,46,51,1,0,0,0,47,45,1,0,0,0,48,50,3,10,5,0,49,48,1,0,0,0,50,53,
  	1,0,0,0,51,49,1,0,0,0,51,52,1,0,0,0,52,56,1,0,0,0,53,51,1,0,0,0,54,57,
  	3,6,3,0,55,57,3,2,1,0,56,54,1,0,0,0,56,55,1,0,0,0,57,58,1,0,0,0,58,56,
  	1,0,0,0,58,59,1,0,0,0,59,60,1,0,0,0,60,61,5,0,0,1,61,1,1,0,0,0,62,63,
  	3,40,20,0,63,64,5,39,0,0,64,65,3,4,2,0,65,66,5,40,0,0,66,72,1,0,0,0,67,
  	68,3,40,20,0,68,69,5,39,0,0,69,70,5,40,0,0,70,72,1,0,0,0,71,62,1,0,0,
  	0,71,67,1,0,0,0,72,3,1,0,0,0,73,81,3,24,12,0,74,81,3,2,1,0,75,81,3,6,
  	3,0,76,81,3,34,17,0,77,81,3,10,5,0,78,81,3,20,10,0,79,81,3,12,6,0,80,
  	73,1,0,0,0,80,74,1,0,0,0,80,75,1,0,0,0,80,76,1,0,0,0,80,77,1,0,0,0,80,
  	78,1,0,0,0,80,79,1,0,0,0,81,82,1,0,0,0,82,80,1,0,0,0,82,83,1,0,0,0,83,
  	5,1,0,0,0,84,85,5,11,0,0,85,86,5,30,0,0,86,7,1,0,0,0,87,88,5,12,0,0,88,
  	89,5,30,0,0,89,9,1,0,0,0,90,91,5,16,0,0,91,92,5,29,0,0,92,93,5,43,0,0,
  	93,94,3,14,7,0,94,95,5,1,0,0,95,96,3,30,15,0,96,102,1,0,0,0,97,98,5,16,
  	0,0,98,99,5,29,0,0,99,100,5,43,0,0,100,102,3,30,15,0,101,90,1,0,0,0,101,
  	97,1,0,0,0,102,11,1,0,0,0,103,104,5,17,0,0,104,105,5,29,0,0,105,107,5,
  	41,0,0,106,108,3,16,8,0,107,106,1,0,0,0,107,108,1,0,0,0,108,109,1,0,0,
  	0,109,110,5,42,0,0,110,13,1,0,0,0,111,112,7,0,0,0,112,15,1,0,0,0,113,
  	118,3,18,9,0,114,115,5,44,0,0,115,117,3,18,9,0,116,114,1,0,0,0,117,120,
  	1,0,0,0,118,116,1,0,0,0,118,119,1,0,0,0,119,17,1,0,0,0,120,118,1,0,0,
  	0,121,122,5,29,0,0,122,123,5,43,0,0,123,124,3,14,7,0,124,19,1,0,0,0,125,
  	126,5,18,0,0,126,127,5,41,0,0,127,128,3,22,11,0,128,129,5,42,0,0,129,
  	130,5,39,0,0,130,131,3,4,2,0,131,137,5,40,0,0,132,133,5,19,0,0,133,134,
  	5,39,0,0,134,135,3,4,2,0,135,136,5,40,0,0,136,138,1,0,0,0,137,132,1,0,
  	0,0,137,138,1,0,0,0,138,21,1,0,0,0,139,140,6,11,-1,0,140,141,5,29,0,0,
  	141,142,5,20,0,0,142,167,3,30,15,0,143,144,5,29,0,0,144,145,5,21,0,0,
  	145,167,3,30,15,0,146,147,5,29,0,0,147,148,5,22,0,0,148,167,5,33,0,0,
  	149,150,5,29,0,0,150,151,5,23,0,0,151,167,5,33,0,0,152,153,5,29,0,0,153,
  	154,5,24,0,0,154,167,5,33,0,0,155,156,5,29,0,0,156,157,5,25,0,0,157,167,
  	5,33,0,0,158,167,5,35,0,0,159,167,5,29,0,0,160,161,5,28,0,0,161,167,3,
  	22,11,2,162,163,5,41,0,0,163,164,3,22,11,0,164,165,5,42,0,0,165,167,1,
  	0,0,0,166,139,1,0,0,0,166,143,1,0,0,0,166,146,1,0,0,0,166,149,1,0,0,0,
  	166,152,1,0,0,0,166,155,1,0,0,0,166,158,1,0,0,0,166,159,1,0,0,0,166,160,
  	1,0,0,0,166,162,1,0,0,0,167,176,1,0,0,0,168,169,10,4,0,0,169,170,5,26,
  	0,0,170,175,3,22,11,5,171,172,10,3,0,0,172,173,5,27,0,0,173,175,3,22,
  	11,4,174,168,1,0,0,0,174,171,1,0,0,0,175,178,1,0,0,0,176,174,1,0,0,0,
  	176,177,1,0,0,0,177,23,1,0,0,0,178,176,1,0,0,0,179,180,3,26,13,0,180,
  	181,5,43,0,0,181,182,3,30,15,0,182,188,1,0,0,0,183,184,3,28,14,0,184,
  	185,5,43,0,0,185,186,3,30,15,0,186,188,1,0,0,0,187,179,1,0,0,0,187,183,
  	1,0,0,0,188,25,1,0,0,0,189,190,5,29,0,0,190,27,1,0,0,0,191,192,5,6,0,
  	0,192,193,5,29,0,0,193,29,1,0,0,0,194,204,5,30,0,0,195,204,5,33,0,0,196,
  	204,5,34,0,0,197,204,5,35,0,0,198,204,5,31,0,0,199,204,3,36,18,0,200,
  	204,5,29,0,0,201,204,5,32,0,0,202,204,3,32,16,0,203,194,1,0,0,0,203,195,
  	1,0,0,0,203,196,1,0,0,0,203,197,1,0,0,0,203,198,1,0,0,0,203,199,1,0,0,
  	0,203,200,1,0,0,0,203,201,1,0,0,0,203,202,1,0,0,0,204,31,1,0,0,0,205,
  	206,6,16,-1,0,206,213,5,32,0,0,207,208,5,41,0,0,208,209,3,32,16,0,209,
  	210,5,42,0,0,210,213,1,0,0,0,211,213,5,33,0,0,212,205,1,0,0,0,212,207,
  	1,0,0,0,212,211,1,0,0,0,213,228,1,0,0,0,214,215,10,6,0,0,215,216,5,7,
  	0,0,216,227,3,32,16,7,217,218,10,5,0,0,218,219,5,8,0,0,219,227,3,32,16,
  	6,220,221,10,4,0,0,221,222,5,9,0,0,222,227,3,32,16,5,223,224,10,3,0,0,
  	224,225,5,10,0,0,225,227,3,32,16,4,226,214,1,0,0,0,226,217,1,0,0,0,226,
  	220,1,0,0,0,226,223,1,0,0,0,227,230,1,0,0,0,228,226,1,0,0,0,228,229,1,
  	0,0,0,229,33,1,0,0,0,230,228,1,0,0,0,231,232,5,13,0,0,232,248,5,30,0,
  	0,233,234,5,13,0,0,234,235,5,14,0,0,235,248,5,30,0,0,236,237,5,13,0,0,
  	237,238,5,15,0,0,238,248,5,30,0,0,239,240,5,13,0,0,240,248,5,31,0,0,241,
  	242,5,13,0,0,242,243,5,14,0,0,243,248,5,31,0,0,244,245,5,13,0,0,245,246,
  	5,15,0,0,246,248,5,31,0,0,247,231,1,0,0,0,247,233,1,0,0,0,247,236,1,0,
  	0,0,247,239,1,0,0,0,247,241,1,0,0,0,247,244,1,0,0,0,248,35,1,0,0,0,249,
  	250,5,29,0,0,250,252,5,41,0,0,251,253,3,38,19,0,252,251,1,0,0,0,252,253,
  	1,0,0,0,253,254,1,0,0,0,254,255,5,42,0,0,255,37,1,0,0,0,256,261,3,30,
  	15,0,257,258,5,44,0,0,258,260,3,30,15,0,259,257,1,0,0,0,260,263,1,0,0,
  	0,261,259,1,0,0,0,261,262,1,0,0,0,262,39,1,0,0,0,263,261,1,0,0,0,264,
  	265,5,29,0,0,265,41,1,0,0,0,22,45,51,56,58,71,80,82,101,107,118,137,166,
  	174,176,187,203,212,226,228,247,252,261
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  hmlParserStaticData = std::move(staticData);
}

}

HmlParser::HmlParser(TokenStream *input) : HmlParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

HmlParser::HmlParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  HmlParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *hmlParserStaticData->atn, hmlParserStaticData->decisionToDFA, hmlParserStaticData->sharedContextCache, options);
}

HmlParser::~HmlParser() {
  delete _interpreter;
}

const atn::ATN& HmlParser::getATN() const {
  return *hmlParserStaticData->atn;
}

std::string HmlParser::getGrammarFileName() const {
  return "Hml.g4";
}

const std::vector<std::string>& HmlParser::getRuleNames() const {
  return hmlParserStaticData->ruleNames;
}

const dfa::Vocabulary& HmlParser::getVocabulary() const {
  return hmlParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView HmlParser::getSerializedATN() const {
  return hmlParserStaticData->serializedATN;
}


//----------------- HmlContext ------------------------------------------------------------------

HmlParser::HmlContext::HmlContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::HmlContext::EOF() {
  return getToken(HmlParser::EOF, 0);
}

std::vector<HmlParser::ImportStatementContext *> HmlParser::HmlContext::importStatement() {
  return getRuleContexts<HmlParser::ImportStatementContext>();
}

HmlParser::ImportStatementContext* HmlParser::HmlContext::importStatement(size_t i) {
  return getRuleContext<HmlParser::ImportStatementContext>(i);
}

std::vector<HmlParser::VariableDeclarationContext *> HmlParser::HmlContext::variableDeclaration() {
  return getRuleContexts<HmlParser::VariableDeclarationContext>();
}

HmlParser::VariableDeclarationContext* HmlParser::HmlContext::variableDeclaration(size_t i) {
  return getRuleContext<HmlParser::VariableDeclarationContext>(i);
}

std::vector<HmlParser::IncludeStatementContext *> HmlParser::HmlContext::includeStatement() {
  return getRuleContexts<HmlParser::IncludeStatementContext>();
}

HmlParser::IncludeStatementContext* HmlParser::HmlContext::includeStatement(size_t i) {
  return getRuleContext<HmlParser::IncludeStatementContext>(i);
}

std::vector<HmlParser::ElementContext *> HmlParser::HmlContext::element() {
  return getRuleContexts<HmlParser::ElementContext>();
}

HmlParser::ElementContext* HmlParser::HmlContext::element(size_t i) {
  return getRuleContext<HmlParser::ElementContext>(i);
}


size_t HmlParser::HmlContext::getRuleIndex() const {
  return HmlParser::RuleHml;
}

void HmlParser::HmlContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterHml(this);
}

void HmlParser::HmlContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitHml(this);
}


std::any HmlParser::HmlContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitHml(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::HmlContext* HmlParser::hml() {
  HmlContext *_localctx = _tracker.createInstance<HmlContext>(_ctx, getState());
  enterRule(_localctx, 0, HmlParser::RuleHml);
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
    setState(45);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HmlParser::IMPORT) {
      setState(42);
      importStatement();
      setState(47);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(51);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HmlParser::VAR) {
      setState(48);
      variableDeclaration();
      setState(53);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(56); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(56);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case HmlParser::INCLUDE: {
          setState(54);
          includeStatement();
          break;
        }

        case HmlParser::ID: {
          setState(55);
          element();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      setState(58); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == HmlParser::INCLUDE

    || _la == HmlParser::ID);
    setState(60);
    match(HmlParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ElementContext ------------------------------------------------------------------

HmlParser::ElementContext::ElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HmlParser::ElementTypeContext* HmlParser::ElementContext::elementType() {
  return getRuleContext<HmlParser::ElementTypeContext>(0);
}

tree::TerminalNode* HmlParser::ElementContext::LBRACE() {
  return getToken(HmlParser::LBRACE, 0);
}

HmlParser::ElementBodyContext* HmlParser::ElementContext::elementBody() {
  return getRuleContext<HmlParser::ElementBodyContext>(0);
}

tree::TerminalNode* HmlParser::ElementContext::RBRACE() {
  return getToken(HmlParser::RBRACE, 0);
}


size_t HmlParser::ElementContext::getRuleIndex() const {
  return HmlParser::RuleElement;
}

void HmlParser::ElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElement(this);
}

void HmlParser::ElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElement(this);
}


std::any HmlParser::ElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitElement(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ElementContext* HmlParser::element() {
  ElementContext *_localctx = _tracker.createInstance<ElementContext>(_ctx, getState());
  enterRule(_localctx, 2, HmlParser::RuleElement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(71);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(62);
      elementType();
      setState(63);
      match(HmlParser::LBRACE);
      setState(64);
      elementBody();
      setState(65);
      match(HmlParser::RBRACE);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(67);
      elementType();
      setState(68);
      match(HmlParser::LBRACE);
      setState(69);
      match(HmlParser::RBRACE);
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

//----------------- ElementBodyContext ------------------------------------------------------------------

HmlParser::ElementBodyContext::ElementBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HmlParser::PropertyContext *> HmlParser::ElementBodyContext::property() {
  return getRuleContexts<HmlParser::PropertyContext>();
}

HmlParser::PropertyContext* HmlParser::ElementBodyContext::property(size_t i) {
  return getRuleContext<HmlParser::PropertyContext>(i);
}

std::vector<HmlParser::ElementContext *> HmlParser::ElementBodyContext::element() {
  return getRuleContexts<HmlParser::ElementContext>();
}

HmlParser::ElementContext* HmlParser::ElementBodyContext::element(size_t i) {
  return getRuleContext<HmlParser::ElementContext>(i);
}

std::vector<HmlParser::IncludeStatementContext *> HmlParser::ElementBodyContext::includeStatement() {
  return getRuleContexts<HmlParser::IncludeStatementContext>();
}

HmlParser::IncludeStatementContext* HmlParser::ElementBodyContext::includeStatement(size_t i) {
  return getRuleContext<HmlParser::IncludeStatementContext>(i);
}

std::vector<HmlParser::ScriptStatementContext *> HmlParser::ElementBodyContext::scriptStatement() {
  return getRuleContexts<HmlParser::ScriptStatementContext>();
}

HmlParser::ScriptStatementContext* HmlParser::ElementBodyContext::scriptStatement(size_t i) {
  return getRuleContext<HmlParser::ScriptStatementContext>(i);
}

std::vector<HmlParser::VariableDeclarationContext *> HmlParser::ElementBodyContext::variableDeclaration() {
  return getRuleContexts<HmlParser::VariableDeclarationContext>();
}

HmlParser::VariableDeclarationContext* HmlParser::ElementBodyContext::variableDeclaration(size_t i) {
  return getRuleContext<HmlParser::VariableDeclarationContext>(i);
}

std::vector<HmlParser::ConditionalStatementContext *> HmlParser::ElementBodyContext::conditionalStatement() {
  return getRuleContexts<HmlParser::ConditionalStatementContext>();
}

HmlParser::ConditionalStatementContext* HmlParser::ElementBodyContext::conditionalStatement(size_t i) {
  return getRuleContext<HmlParser::ConditionalStatementContext>(i);
}

std::vector<HmlParser::SignalDeclarationContext *> HmlParser::ElementBodyContext::signalDeclaration() {
  return getRuleContexts<HmlParser::SignalDeclarationContext>();
}

HmlParser::SignalDeclarationContext* HmlParser::ElementBodyContext::signalDeclaration(size_t i) {
  return getRuleContext<HmlParser::SignalDeclarationContext>(i);
}


size_t HmlParser::ElementBodyContext::getRuleIndex() const {
  return HmlParser::RuleElementBody;
}

void HmlParser::ElementBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementBody(this);
}

void HmlParser::ElementBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementBody(this);
}


std::any HmlParser::ElementBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitElementBody(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ElementBodyContext* HmlParser::elementBody() {
  ElementBodyContext *_localctx = _tracker.createInstance<ElementBodyContext>(_ctx, getState());
  enterRule(_localctx, 4, HmlParser::RuleElementBody);
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
    setState(80); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(80);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
      case 1: {
        setState(73);
        property();
        break;
      }

      case 2: {
        setState(74);
        element();
        break;
      }

      case 3: {
        setState(75);
        includeStatement();
        break;
      }

      case 4: {
        setState(76);
        scriptStatement();
        break;
      }

      case 5: {
        setState(77);
        variableDeclaration();
        break;
      }

      case 6: {
        setState(78);
        conditionalStatement();
        break;
      }

      case 7: {
        setState(79);
        signalDeclaration();
        break;
      }

      default:
        break;
      }
      setState(82); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 537339968) != 0));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IncludeStatementContext ------------------------------------------------------------------

HmlParser::IncludeStatementContext::IncludeStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::IncludeStatementContext::INCLUDE() {
  return getToken(HmlParser::INCLUDE, 0);
}

tree::TerminalNode* HmlParser::IncludeStatementContext::STRING() {
  return getToken(HmlParser::STRING, 0);
}


size_t HmlParser::IncludeStatementContext::getRuleIndex() const {
  return HmlParser::RuleIncludeStatement;
}

void HmlParser::IncludeStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIncludeStatement(this);
}

void HmlParser::IncludeStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIncludeStatement(this);
}


std::any HmlParser::IncludeStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitIncludeStatement(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::IncludeStatementContext* HmlParser::includeStatement() {
  IncludeStatementContext *_localctx = _tracker.createInstance<IncludeStatementContext>(_ctx, getState());
  enterRule(_localctx, 6, HmlParser::RuleIncludeStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(84);
    match(HmlParser::INCLUDE);
    setState(85);
    match(HmlParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ImportStatementContext ------------------------------------------------------------------

HmlParser::ImportStatementContext::ImportStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::ImportStatementContext::IMPORT() {
  return getToken(HmlParser::IMPORT, 0);
}

tree::TerminalNode* HmlParser::ImportStatementContext::STRING() {
  return getToken(HmlParser::STRING, 0);
}


size_t HmlParser::ImportStatementContext::getRuleIndex() const {
  return HmlParser::RuleImportStatement;
}

void HmlParser::ImportStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterImportStatement(this);
}

void HmlParser::ImportStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitImportStatement(this);
}


std::any HmlParser::ImportStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitImportStatement(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ImportStatementContext* HmlParser::importStatement() {
  ImportStatementContext *_localctx = _tracker.createInstance<ImportStatementContext>(_ctx, getState());
  enterRule(_localctx, 8, HmlParser::RuleImportStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(87);
    match(HmlParser::IMPORT);
    setState(88);
    match(HmlParser::STRING);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VariableDeclarationContext ------------------------------------------------------------------

HmlParser::VariableDeclarationContext::VariableDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::VariableDeclarationContext::VAR() {
  return getToken(HmlParser::VAR, 0);
}

tree::TerminalNode* HmlParser::VariableDeclarationContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::VariableDeclarationContext::COLON() {
  return getToken(HmlParser::COLON, 0);
}

HmlParser::TypeAnnotationContext* HmlParser::VariableDeclarationContext::typeAnnotation() {
  return getRuleContext<HmlParser::TypeAnnotationContext>(0);
}

HmlParser::PropertyValueContext* HmlParser::VariableDeclarationContext::propertyValue() {
  return getRuleContext<HmlParser::PropertyValueContext>(0);
}


size_t HmlParser::VariableDeclarationContext::getRuleIndex() const {
  return HmlParser::RuleVariableDeclaration;
}

void HmlParser::VariableDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableDeclaration(this);
}

void HmlParser::VariableDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableDeclaration(this);
}


std::any HmlParser::VariableDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitVariableDeclaration(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::VariableDeclarationContext* HmlParser::variableDeclaration() {
  VariableDeclarationContext *_localctx = _tracker.createInstance<VariableDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 10, HmlParser::RuleVariableDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(101);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(90);
      match(HmlParser::VAR);
      setState(91);
      match(HmlParser::ID);
      setState(92);
      match(HmlParser::COLON);
      setState(93);
      typeAnnotation();
      setState(94);
      match(HmlParser::T__0);
      setState(95);
      propertyValue();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(97);
      match(HmlParser::VAR);
      setState(98);
      match(HmlParser::ID);
      setState(99);
      match(HmlParser::COLON);
      setState(100);
      propertyValue();
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

//----------------- SignalDeclarationContext ------------------------------------------------------------------

HmlParser::SignalDeclarationContext::SignalDeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::SignalDeclarationContext::SIGNAL() {
  return getToken(HmlParser::SIGNAL, 0);
}

tree::TerminalNode* HmlParser::SignalDeclarationContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::SignalDeclarationContext::LPAREN() {
  return getToken(HmlParser::LPAREN, 0);
}

tree::TerminalNode* HmlParser::SignalDeclarationContext::RPAREN() {
  return getToken(HmlParser::RPAREN, 0);
}

HmlParser::ParameterListContext* HmlParser::SignalDeclarationContext::parameterList() {
  return getRuleContext<HmlParser::ParameterListContext>(0);
}


size_t HmlParser::SignalDeclarationContext::getRuleIndex() const {
  return HmlParser::RuleSignalDeclaration;
}

void HmlParser::SignalDeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSignalDeclaration(this);
}

void HmlParser::SignalDeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSignalDeclaration(this);
}


std::any HmlParser::SignalDeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitSignalDeclaration(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::SignalDeclarationContext* HmlParser::signalDeclaration() {
  SignalDeclarationContext *_localctx = _tracker.createInstance<SignalDeclarationContext>(_ctx, getState());
  enterRule(_localctx, 12, HmlParser::RuleSignalDeclaration);
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
    setState(103);
    match(HmlParser::SIGNAL);
    setState(104);
    match(HmlParser::ID);
    setState(105);
    match(HmlParser::LPAREN);
    setState(107);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HmlParser::ID) {
      setState(106);
      parameterList();
    }
    setState(109);
    match(HmlParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TypeAnnotationContext ------------------------------------------------------------------

HmlParser::TypeAnnotationContext::TypeAnnotationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HmlParser::TypeAnnotationContext::getRuleIndex() const {
  return HmlParser::RuleTypeAnnotation;
}

void HmlParser::TypeAnnotationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTypeAnnotation(this);
}

void HmlParser::TypeAnnotationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTypeAnnotation(this);
}


std::any HmlParser::TypeAnnotationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitTypeAnnotation(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::TypeAnnotationContext* HmlParser::typeAnnotation() {
  TypeAnnotationContext *_localctx = _tracker.createInstance<TypeAnnotationContext>(_ctx, getState());
  enterRule(_localctx, 14, HmlParser::RuleTypeAnnotation);
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
    setState(111);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 60) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParameterListContext ------------------------------------------------------------------

HmlParser::ParameterListContext::ParameterListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HmlParser::ParameterContext *> HmlParser::ParameterListContext::parameter() {
  return getRuleContexts<HmlParser::ParameterContext>();
}

HmlParser::ParameterContext* HmlParser::ParameterListContext::parameter(size_t i) {
  return getRuleContext<HmlParser::ParameterContext>(i);
}

std::vector<tree::TerminalNode *> HmlParser::ParameterListContext::COMMA() {
  return getTokens(HmlParser::COMMA);
}

tree::TerminalNode* HmlParser::ParameterListContext::COMMA(size_t i) {
  return getToken(HmlParser::COMMA, i);
}


size_t HmlParser::ParameterListContext::getRuleIndex() const {
  return HmlParser::RuleParameterList;
}

void HmlParser::ParameterListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameterList(this);
}

void HmlParser::ParameterListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameterList(this);
}


std::any HmlParser::ParameterListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitParameterList(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ParameterListContext* HmlParser::parameterList() {
  ParameterListContext *_localctx = _tracker.createInstance<ParameterListContext>(_ctx, getState());
  enterRule(_localctx, 16, HmlParser::RuleParameterList);
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
    setState(113);
    parameter();
    setState(118);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HmlParser::COMMA) {
      setState(114);
      match(HmlParser::COMMA);
      setState(115);
      parameter();
      setState(120);
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

//----------------- ParameterContext ------------------------------------------------------------------

HmlParser::ParameterContext::ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::ParameterContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::ParameterContext::COLON() {
  return getToken(HmlParser::COLON, 0);
}

HmlParser::TypeAnnotationContext* HmlParser::ParameterContext::typeAnnotation() {
  return getRuleContext<HmlParser::TypeAnnotationContext>(0);
}


size_t HmlParser::ParameterContext::getRuleIndex() const {
  return HmlParser::RuleParameter;
}

void HmlParser::ParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParameter(this);
}

void HmlParser::ParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParameter(this);
}


std::any HmlParser::ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitParameter(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ParameterContext* HmlParser::parameter() {
  ParameterContext *_localctx = _tracker.createInstance<ParameterContext>(_ctx, getState());
  enterRule(_localctx, 18, HmlParser::RuleParameter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(121);
    match(HmlParser::ID);
    setState(122);
    match(HmlParser::COLON);
    setState(123);
    typeAnnotation();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalStatementContext ------------------------------------------------------------------

HmlParser::ConditionalStatementContext::ConditionalStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::ConditionalStatementContext::IF() {
  return getToken(HmlParser::IF, 0);
}

tree::TerminalNode* HmlParser::ConditionalStatementContext::LPAREN() {
  return getToken(HmlParser::LPAREN, 0);
}

HmlParser::ConditionalExpressionContext* HmlParser::ConditionalStatementContext::conditionalExpression() {
  return getRuleContext<HmlParser::ConditionalExpressionContext>(0);
}

tree::TerminalNode* HmlParser::ConditionalStatementContext::RPAREN() {
  return getToken(HmlParser::RPAREN, 0);
}

std::vector<tree::TerminalNode *> HmlParser::ConditionalStatementContext::LBRACE() {
  return getTokens(HmlParser::LBRACE);
}

tree::TerminalNode* HmlParser::ConditionalStatementContext::LBRACE(size_t i) {
  return getToken(HmlParser::LBRACE, i);
}

std::vector<HmlParser::ElementBodyContext *> HmlParser::ConditionalStatementContext::elementBody() {
  return getRuleContexts<HmlParser::ElementBodyContext>();
}

HmlParser::ElementBodyContext* HmlParser::ConditionalStatementContext::elementBody(size_t i) {
  return getRuleContext<HmlParser::ElementBodyContext>(i);
}

std::vector<tree::TerminalNode *> HmlParser::ConditionalStatementContext::RBRACE() {
  return getTokens(HmlParser::RBRACE);
}

tree::TerminalNode* HmlParser::ConditionalStatementContext::RBRACE(size_t i) {
  return getToken(HmlParser::RBRACE, i);
}

tree::TerminalNode* HmlParser::ConditionalStatementContext::ELSE() {
  return getToken(HmlParser::ELSE, 0);
}


size_t HmlParser::ConditionalStatementContext::getRuleIndex() const {
  return HmlParser::RuleConditionalStatement;
}

void HmlParser::ConditionalStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterConditionalStatement(this);
}

void HmlParser::ConditionalStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitConditionalStatement(this);
}


std::any HmlParser::ConditionalStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitConditionalStatement(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ConditionalStatementContext* HmlParser::conditionalStatement() {
  ConditionalStatementContext *_localctx = _tracker.createInstance<ConditionalStatementContext>(_ctx, getState());
  enterRule(_localctx, 20, HmlParser::RuleConditionalStatement);
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
    setState(125);
    match(HmlParser::IF);
    setState(126);
    match(HmlParser::LPAREN);
    setState(127);
    conditionalExpression(0);
    setState(128);
    match(HmlParser::RPAREN);
    setState(129);
    match(HmlParser::LBRACE);
    setState(130);
    elementBody();
    setState(131);
    match(HmlParser::RBRACE);
    setState(137);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == HmlParser::ELSE) {
      setState(132);
      match(HmlParser::ELSE);
      setState(133);
      match(HmlParser::LBRACE);
      setState(134);
      elementBody();
      setState(135);
      match(HmlParser::RBRACE);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ConditionalExpressionContext ------------------------------------------------------------------

HmlParser::ConditionalExpressionContext::ConditionalExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HmlParser::ConditionalExpressionContext::getRuleIndex() const {
  return HmlParser::RuleConditionalExpression;
}

void HmlParser::ConditionalExpressionContext::copyFrom(ConditionalExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- EqualityConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::EqualityConditionContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::EqualityConditionContext::EQ() {
  return getToken(HmlParser::EQ, 0);
}

HmlParser::PropertyValueContext* HmlParser::EqualityConditionContext::propertyValue() {
  return getRuleContext<HmlParser::PropertyValueContext>(0);
}

HmlParser::EqualityConditionContext::EqualityConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::EqualityConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEqualityCondition(this);
}
void HmlParser::EqualityConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEqualityCondition(this);
}

std::any HmlParser::EqualityConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitEqualityCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleanConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::BooleanConditionContext::BOOLEAN() {
  return getToken(HmlParser::BOOLEAN, 0);
}

HmlParser::BooleanConditionContext::BooleanConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::BooleanConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanCondition(this);
}
void HmlParser::BooleanConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanCondition(this);
}

std::any HmlParser::BooleanConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitBooleanCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NotConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::NotConditionContext::NOT() {
  return getToken(HmlParser::NOT, 0);
}

HmlParser::ConditionalExpressionContext* HmlParser::NotConditionContext::conditionalExpression() {
  return getRuleContext<HmlParser::ConditionalExpressionContext>(0);
}

HmlParser::NotConditionContext::NotConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::NotConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNotCondition(this);
}
void HmlParser::NotConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNotCondition(this);
}

std::any HmlParser::NotConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitNotCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GreaterThanConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::GreaterThanConditionContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::GreaterThanConditionContext::GT() {
  return getToken(HmlParser::GT, 0);
}

tree::TerminalNode* HmlParser::GreaterThanConditionContext::NUMBER() {
  return getToken(HmlParser::NUMBER, 0);
}

HmlParser::GreaterThanConditionContext::GreaterThanConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::GreaterThanConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGreaterThanCondition(this);
}
void HmlParser::GreaterThanConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGreaterThanCondition(this);
}

std::any HmlParser::GreaterThanConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitGreaterThanCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GreaterEqualConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::GreaterEqualConditionContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::GreaterEqualConditionContext::GE() {
  return getToken(HmlParser::GE, 0);
}

tree::TerminalNode* HmlParser::GreaterEqualConditionContext::NUMBER() {
  return getToken(HmlParser::NUMBER, 0);
}

HmlParser::GreaterEqualConditionContext::GreaterEqualConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::GreaterEqualConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGreaterEqualCondition(this);
}
void HmlParser::GreaterEqualConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGreaterEqualCondition(this);
}

std::any HmlParser::GreaterEqualConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitGreaterEqualCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- VariableConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::VariableConditionContext::ID() {
  return getToken(HmlParser::ID, 0);
}

HmlParser::VariableConditionContext::VariableConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::VariableConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVariableCondition(this);
}
void HmlParser::VariableConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVariableCondition(this);
}

std::any HmlParser::VariableConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitVariableCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::ParenConditionContext::LPAREN() {
  return getToken(HmlParser::LPAREN, 0);
}

HmlParser::ConditionalExpressionContext* HmlParser::ParenConditionContext::conditionalExpression() {
  return getRuleContext<HmlParser::ConditionalExpressionContext>(0);
}

tree::TerminalNode* HmlParser::ParenConditionContext::RPAREN() {
  return getToken(HmlParser::RPAREN, 0);
}

HmlParser::ParenConditionContext::ParenConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::ParenConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenCondition(this);
}
void HmlParser::ParenConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenCondition(this);
}

std::any HmlParser::ParenConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitParenCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LessThanConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::LessThanConditionContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::LessThanConditionContext::LT() {
  return getToken(HmlParser::LT, 0);
}

tree::TerminalNode* HmlParser::LessThanConditionContext::NUMBER() {
  return getToken(HmlParser::NUMBER, 0);
}

HmlParser::LessThanConditionContext::LessThanConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::LessThanConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLessThanCondition(this);
}
void HmlParser::LessThanConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLessThanCondition(this);
}

std::any HmlParser::LessThanConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitLessThanCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LessEqualConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::LessEqualConditionContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::LessEqualConditionContext::LE() {
  return getToken(HmlParser::LE, 0);
}

tree::TerminalNode* HmlParser::LessEqualConditionContext::NUMBER() {
  return getToken(HmlParser::NUMBER, 0);
}

HmlParser::LessEqualConditionContext::LessEqualConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::LessEqualConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLessEqualCondition(this);
}
void HmlParser::LessEqualConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLessEqualCondition(this);
}

std::any HmlParser::LessEqualConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitLessEqualCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- InequalityConditionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::InequalityConditionContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::InequalityConditionContext::NE() {
  return getToken(HmlParser::NE, 0);
}

HmlParser::PropertyValueContext* HmlParser::InequalityConditionContext::propertyValue() {
  return getRuleContext<HmlParser::PropertyValueContext>(0);
}

HmlParser::InequalityConditionContext::InequalityConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::InequalityConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterInequalityCondition(this);
}
void HmlParser::InequalityConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitInequalityCondition(this);
}

std::any HmlParser::InequalityConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitInequalityCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- OrConditionContext ------------------------------------------------------------------

std::vector<HmlParser::ConditionalExpressionContext *> HmlParser::OrConditionContext::conditionalExpression() {
  return getRuleContexts<HmlParser::ConditionalExpressionContext>();
}

HmlParser::ConditionalExpressionContext* HmlParser::OrConditionContext::conditionalExpression(size_t i) {
  return getRuleContext<HmlParser::ConditionalExpressionContext>(i);
}

tree::TerminalNode* HmlParser::OrConditionContext::OR() {
  return getToken(HmlParser::OR, 0);
}

HmlParser::OrConditionContext::OrConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::OrConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOrCondition(this);
}
void HmlParser::OrConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOrCondition(this);
}

std::any HmlParser::OrConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitOrCondition(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AndConditionContext ------------------------------------------------------------------

std::vector<HmlParser::ConditionalExpressionContext *> HmlParser::AndConditionContext::conditionalExpression() {
  return getRuleContexts<HmlParser::ConditionalExpressionContext>();
}

HmlParser::ConditionalExpressionContext* HmlParser::AndConditionContext::conditionalExpression(size_t i) {
  return getRuleContext<HmlParser::ConditionalExpressionContext>(i);
}

tree::TerminalNode* HmlParser::AndConditionContext::AND() {
  return getToken(HmlParser::AND, 0);
}

HmlParser::AndConditionContext::AndConditionContext(ConditionalExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::AndConditionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAndCondition(this);
}
void HmlParser::AndConditionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAndCondition(this);
}

std::any HmlParser::AndConditionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitAndCondition(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ConditionalExpressionContext* HmlParser::conditionalExpression() {
   return conditionalExpression(0);
}

HmlParser::ConditionalExpressionContext* HmlParser::conditionalExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  HmlParser::ConditionalExpressionContext *_localctx = _tracker.createInstance<ConditionalExpressionContext>(_ctx, parentState);
  HmlParser::ConditionalExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, HmlParser::RuleConditionalExpression, precedence);

    

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
    setState(166);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<EqualityConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(140);
      match(HmlParser::ID);
      setState(141);
      match(HmlParser::EQ);
      setState(142);
      propertyValue();
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<InequalityConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(143);
      match(HmlParser::ID);
      setState(144);
      match(HmlParser::NE);
      setState(145);
      propertyValue();
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<GreaterThanConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(146);
      match(HmlParser::ID);
      setState(147);
      match(HmlParser::GT);
      setState(148);
      match(HmlParser::NUMBER);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<LessThanConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(149);
      match(HmlParser::ID);
      setState(150);
      match(HmlParser::LT);
      setState(151);
      match(HmlParser::NUMBER);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<GreaterEqualConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(152);
      match(HmlParser::ID);
      setState(153);
      match(HmlParser::GE);
      setState(154);
      match(HmlParser::NUMBER);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<LessEqualConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(155);
      match(HmlParser::ID);
      setState(156);
      match(HmlParser::LE);
      setState(157);
      match(HmlParser::NUMBER);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<BooleanConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(158);
      match(HmlParser::BOOLEAN);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<VariableConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(159);
      match(HmlParser::ID);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<NotConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(160);
      match(HmlParser::NOT);
      setState(161);
      conditionalExpression(2);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<ParenConditionContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(162);
      match(HmlParser::LPAREN);
      setState(163);
      conditionalExpression(0);
      setState(164);
      match(HmlParser::RPAREN);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(176);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(174);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AndConditionContext>(_tracker.createInstance<ConditionalExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleConditionalExpression);
          setState(168);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(169);
          match(HmlParser::AND);
          setState(170);
          conditionalExpression(5);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<OrConditionContext>(_tracker.createInstance<ConditionalExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleConditionalExpression);
          setState(171);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(172);
          match(HmlParser::OR);
          setState(173);
          conditionalExpression(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(178);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- PropertyContext ------------------------------------------------------------------

HmlParser::PropertyContext::PropertyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

HmlParser::PropertyNameContext* HmlParser::PropertyContext::propertyName() {
  return getRuleContext<HmlParser::PropertyNameContext>(0);
}

tree::TerminalNode* HmlParser::PropertyContext::COLON() {
  return getToken(HmlParser::COLON, 0);
}

HmlParser::PropertyValueContext* HmlParser::PropertyContext::propertyValue() {
  return getRuleContext<HmlParser::PropertyValueContext>(0);
}

HmlParser::EventHandlerContext* HmlParser::PropertyContext::eventHandler() {
  return getRuleContext<HmlParser::EventHandlerContext>(0);
}


size_t HmlParser::PropertyContext::getRuleIndex() const {
  return HmlParser::RuleProperty;
}

void HmlParser::PropertyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProperty(this);
}

void HmlParser::PropertyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProperty(this);
}


std::any HmlParser::PropertyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitProperty(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::PropertyContext* HmlParser::property() {
  PropertyContext *_localctx = _tracker.createInstance<PropertyContext>(_ctx, getState());
  enterRule(_localctx, 24, HmlParser::RuleProperty);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(187);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HmlParser::ID: {
        enterOuterAlt(_localctx, 1);
        setState(179);
        propertyName();
        setState(180);
        match(HmlParser::COLON);
        setState(181);
        propertyValue();
        break;
      }

      case HmlParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(183);
        eventHandler();
        setState(184);
        match(HmlParser::COLON);
        setState(185);
        propertyValue();
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

//----------------- PropertyNameContext ------------------------------------------------------------------

HmlParser::PropertyNameContext::PropertyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::PropertyNameContext::ID() {
  return getToken(HmlParser::ID, 0);
}


size_t HmlParser::PropertyNameContext::getRuleIndex() const {
  return HmlParser::RulePropertyName;
}

void HmlParser::PropertyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterPropertyName(this);
}

void HmlParser::PropertyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitPropertyName(this);
}


std::any HmlParser::PropertyNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitPropertyName(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::PropertyNameContext* HmlParser::propertyName() {
  PropertyNameContext *_localctx = _tracker.createInstance<PropertyNameContext>(_ctx, getState());
  enterRule(_localctx, 26, HmlParser::RulePropertyName);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(189);
    match(HmlParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- EventHandlerContext ------------------------------------------------------------------

HmlParser::EventHandlerContext::EventHandlerContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::EventHandlerContext::ID() {
  return getToken(HmlParser::ID, 0);
}


size_t HmlParser::EventHandlerContext::getRuleIndex() const {
  return HmlParser::RuleEventHandler;
}

void HmlParser::EventHandlerContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterEventHandler(this);
}

void HmlParser::EventHandlerContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitEventHandler(this);
}


std::any HmlParser::EventHandlerContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitEventHandler(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::EventHandlerContext* HmlParser::eventHandler() {
  EventHandlerContext *_localctx = _tracker.createInstance<EventHandlerContext>(_ctx, getState());
  enterRule(_localctx, 28, HmlParser::RuleEventHandler);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(191);
    match(HmlParser::T__5);
    setState(192);
    match(HmlParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- PropertyValueContext ------------------------------------------------------------------

HmlParser::PropertyValueContext::PropertyValueContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HmlParser::PropertyValueContext::getRuleIndex() const {
  return HmlParser::RulePropertyValue;
}

void HmlParser::PropertyValueContext::copyFrom(PropertyValueContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- ScriptValueContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::ScriptValueContext::SCRIPT_CONTENT() {
  return getToken(HmlParser::SCRIPT_CONTENT, 0);
}

HmlParser::ScriptValueContext::ScriptValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::ScriptValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterScriptValue(this);
}
void HmlParser::ScriptValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitScriptValue(this);
}

std::any HmlParser::ScriptValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitScriptValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberValueContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::NumberValueContext::NUMBER() {
  return getToken(HmlParser::NUMBER, 0);
}

HmlParser::NumberValueContext::NumberValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::NumberValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumberValue(this);
}
void HmlParser::NumberValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumberValue(this);
}

std::any HmlParser::NumberValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitNumberValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExpressionValueContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::ExpressionValueContext::EXPRESSION() {
  return getToken(HmlParser::EXPRESSION, 0);
}

HmlParser::ExpressionValueContext::ExpressionValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::ExpressionValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpressionValue(this);
}
void HmlParser::ExpressionValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpressionValue(this);
}

std::any HmlParser::ExpressionValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitExpressionValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ColorValueContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::ColorValueContext::COLOR() {
  return getToken(HmlParser::COLOR, 0);
}

HmlParser::ColorValueContext::ColorValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::ColorValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterColorValue(this);
}
void HmlParser::ColorValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitColorValue(this);
}

std::any HmlParser::ColorValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitColorValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- BooleanValueContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::BooleanValueContext::BOOLEAN() {
  return getToken(HmlParser::BOOLEAN, 0);
}

HmlParser::BooleanValueContext::BooleanValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::BooleanValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBooleanValue(this);
}
void HmlParser::BooleanValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBooleanValue(this);
}

std::any HmlParser::BooleanValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitBooleanValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComplexExpressionValueContext ------------------------------------------------------------------

HmlParser::ComplexExpressionContext* HmlParser::ComplexExpressionValueContext::complexExpression() {
  return getRuleContext<HmlParser::ComplexExpressionContext>(0);
}

HmlParser::ComplexExpressionValueContext::ComplexExpressionValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::ComplexExpressionValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComplexExpressionValue(this);
}
void HmlParser::ComplexExpressionValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComplexExpressionValue(this);
}

std::any HmlParser::ComplexExpressionValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitComplexExpressionValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionValueContext ------------------------------------------------------------------

HmlParser::FunctionCallContext* HmlParser::FunctionValueContext::functionCall() {
  return getRuleContext<HmlParser::FunctionCallContext>(0);
}

HmlParser::FunctionValueContext::FunctionValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::FunctionValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionValue(this);
}
void HmlParser::FunctionValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionValue(this);
}

std::any HmlParser::FunctionValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitFunctionValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierValueContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::IdentifierValueContext::ID() {
  return getToken(HmlParser::ID, 0);
}

HmlParser::IdentifierValueContext::IdentifierValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::IdentifierValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifierValue(this);
}
void HmlParser::IdentifierValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifierValue(this);
}

std::any HmlParser::IdentifierValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitIdentifierValue(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StringValueContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::StringValueContext::STRING() {
  return getToken(HmlParser::STRING, 0);
}

HmlParser::StringValueContext::StringValueContext(PropertyValueContext *ctx) { copyFrom(ctx); }

void HmlParser::StringValueContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringValue(this);
}
void HmlParser::StringValueContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringValue(this);
}

std::any HmlParser::StringValueContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitStringValue(this);
  else
    return visitor->visitChildren(this);
}
HmlParser::PropertyValueContext* HmlParser::propertyValue() {
  PropertyValueContext *_localctx = _tracker.createInstance<PropertyValueContext>(_ctx, getState());
  enterRule(_localctx, 30, HmlParser::RulePropertyValue);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(203);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<HmlParser::StringValueContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(194);
      match(HmlParser::STRING);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<HmlParser::NumberValueContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(195);
      match(HmlParser::NUMBER);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<HmlParser::ColorValueContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(196);
      match(HmlParser::COLOR);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<HmlParser::BooleanValueContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(197);
      match(HmlParser::BOOLEAN);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<HmlParser::ScriptValueContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(198);
      match(HmlParser::SCRIPT_CONTENT);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<HmlParser::FunctionValueContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(199);
      functionCall();
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<HmlParser::IdentifierValueContext>(_localctx);
      enterOuterAlt(_localctx, 7);
      setState(200);
      match(HmlParser::ID);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<HmlParser::ExpressionValueContext>(_localctx);
      enterOuterAlt(_localctx, 8);
      setState(201);
      match(HmlParser::EXPRESSION);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<HmlParser::ComplexExpressionValueContext>(_localctx);
      enterOuterAlt(_localctx, 9);
      setState(202);
      complexExpression(0);
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

//----------------- ComplexExpressionContext ------------------------------------------------------------------

HmlParser::ComplexExpressionContext::ComplexExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HmlParser::ComplexExpressionContext::getRuleIndex() const {
  return HmlParser::RuleComplexExpression;
}

void HmlParser::ComplexExpressionContext::copyFrom(ComplexExpressionContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- SubtractExpressionContext ------------------------------------------------------------------

std::vector<HmlParser::ComplexExpressionContext *> HmlParser::SubtractExpressionContext::complexExpression() {
  return getRuleContexts<HmlParser::ComplexExpressionContext>();
}

HmlParser::ComplexExpressionContext* HmlParser::SubtractExpressionContext::complexExpression(size_t i) {
  return getRuleContext<HmlParser::ComplexExpressionContext>(i);
}

HmlParser::SubtractExpressionContext::SubtractExpressionContext(ComplexExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::SubtractExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSubtractExpression(this);
}
void HmlParser::SubtractExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSubtractExpression(this);
}

std::any HmlParser::SubtractExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitSubtractExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DivideExpressionContext ------------------------------------------------------------------

std::vector<HmlParser::ComplexExpressionContext *> HmlParser::DivideExpressionContext::complexExpression() {
  return getRuleContexts<HmlParser::ComplexExpressionContext>();
}

HmlParser::ComplexExpressionContext* HmlParser::DivideExpressionContext::complexExpression(size_t i) {
  return getRuleContext<HmlParser::ComplexExpressionContext>(i);
}

HmlParser::DivideExpressionContext::DivideExpressionContext(ComplexExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::DivideExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDivideExpression(this);
}
void HmlParser::DivideExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDivideExpression(this);
}

std::any HmlParser::DivideExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitDivideExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AddExpressionContext ------------------------------------------------------------------

std::vector<HmlParser::ComplexExpressionContext *> HmlParser::AddExpressionContext::complexExpression() {
  return getRuleContexts<HmlParser::ComplexExpressionContext>();
}

HmlParser::ComplexExpressionContext* HmlParser::AddExpressionContext::complexExpression(size_t i) {
  return getRuleContext<HmlParser::ComplexExpressionContext>(i);
}

HmlParser::AddExpressionContext::AddExpressionContext(ComplexExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::AddExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddExpression(this);
}
void HmlParser::AddExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddExpression(this);
}

std::any HmlParser::AddExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitAddExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultiplyExpressionContext ------------------------------------------------------------------

std::vector<HmlParser::ComplexExpressionContext *> HmlParser::MultiplyExpressionContext::complexExpression() {
  return getRuleContexts<HmlParser::ComplexExpressionContext>();
}

HmlParser::ComplexExpressionContext* HmlParser::MultiplyExpressionContext::complexExpression(size_t i) {
  return getRuleContext<HmlParser::ComplexExpressionContext>(i);
}

HmlParser::MultiplyExpressionContext::MultiplyExpressionContext(ComplexExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::MultiplyExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplyExpression(this);
}
void HmlParser::MultiplyExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplyExpression(this);
}

std::any HmlParser::MultiplyExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitMultiplyExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ParenExpressionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::ParenExpressionContext::LPAREN() {
  return getToken(HmlParser::LPAREN, 0);
}

HmlParser::ComplexExpressionContext* HmlParser::ParenExpressionContext::complexExpression() {
  return getRuleContext<HmlParser::ComplexExpressionContext>(0);
}

tree::TerminalNode* HmlParser::ParenExpressionContext::RPAREN() {
  return getToken(HmlParser::RPAREN, 0);
}

HmlParser::ParenExpressionContext::ParenExpressionContext(ComplexExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::ParenExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParenExpression(this);
}
void HmlParser::ParenExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParenExpression(this);
}

std::any HmlParser::ParenExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitParenExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberExpressionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::NumberExpressionContext::NUMBER() {
  return getToken(HmlParser::NUMBER, 0);
}

HmlParser::NumberExpressionContext::NumberExpressionContext(ComplexExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::NumberExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumberExpression(this);
}
void HmlParser::NumberExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumberExpression(this);
}

std::any HmlParser::NumberExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitNumberExpression(this);
  else
    return visitor->visitChildren(this);
}
//----------------- SimpleExpressionContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::SimpleExpressionContext::EXPRESSION() {
  return getToken(HmlParser::EXPRESSION, 0);
}

HmlParser::SimpleExpressionContext::SimpleExpressionContext(ComplexExpressionContext *ctx) { copyFrom(ctx); }

void HmlParser::SimpleExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimpleExpression(this);
}
void HmlParser::SimpleExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimpleExpression(this);
}

std::any HmlParser::SimpleExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitSimpleExpression(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ComplexExpressionContext* HmlParser::complexExpression() {
   return complexExpression(0);
}

HmlParser::ComplexExpressionContext* HmlParser::complexExpression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  HmlParser::ComplexExpressionContext *_localctx = _tracker.createInstance<ComplexExpressionContext>(_ctx, parentState);
  HmlParser::ComplexExpressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 32;
  enterRecursionRule(_localctx, 32, HmlParser::RuleComplexExpression, precedence);

    

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
    setState(212);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case HmlParser::EXPRESSION: {
        _localctx = _tracker.createInstance<SimpleExpressionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(206);
        match(HmlParser::EXPRESSION);
        break;
      }

      case HmlParser::LPAREN: {
        _localctx = _tracker.createInstance<ParenExpressionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(207);
        match(HmlParser::LPAREN);
        setState(208);
        complexExpression(0);
        setState(209);
        match(HmlParser::RPAREN);
        break;
      }

      case HmlParser::NUMBER: {
        _localctx = _tracker.createInstance<NumberExpressionContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(211);
        match(HmlParser::NUMBER);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(228);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(226);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<AddExpressionContext>(_tracker.createInstance<ComplexExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleComplexExpression);
          setState(214);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(215);
          match(HmlParser::T__6);
          setState(216);
          complexExpression(7);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<SubtractExpressionContext>(_tracker.createInstance<ComplexExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleComplexExpression);
          setState(217);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(218);
          match(HmlParser::T__7);
          setState(219);
          complexExpression(6);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<MultiplyExpressionContext>(_tracker.createInstance<ComplexExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleComplexExpression);
          setState(220);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(221);
          match(HmlParser::T__8);
          setState(222);
          complexExpression(5);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<DivideExpressionContext>(_tracker.createInstance<ComplexExpressionContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleComplexExpression);
          setState(223);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(224);
          match(HmlParser::T__9);
          setState(225);
          complexExpression(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(230);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ScriptStatementContext ------------------------------------------------------------------

HmlParser::ScriptStatementContext::ScriptStatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t HmlParser::ScriptStatementContext::getRuleIndex() const {
  return HmlParser::RuleScriptStatement;
}

void HmlParser::ScriptStatementContext::copyFrom(ScriptStatementContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- AsyncScriptStatementContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::AsyncScriptStatementContext::SCRIPT() {
  return getToken(HmlParser::SCRIPT, 0);
}

tree::TerminalNode* HmlParser::AsyncScriptStatementContext::ASYNC() {
  return getToken(HmlParser::ASYNC, 0);
}

tree::TerminalNode* HmlParser::AsyncScriptStatementContext::STRING() {
  return getToken(HmlParser::STRING, 0);
}

HmlParser::AsyncScriptStatementContext::AsyncScriptStatementContext(ScriptStatementContext *ctx) { copyFrom(ctx); }

void HmlParser::AsyncScriptStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAsyncScriptStatement(this);
}
void HmlParser::AsyncScriptStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAsyncScriptStatement(this);
}

std::any HmlParser::AsyncScriptStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitAsyncScriptStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeferInlineScriptStatementContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::DeferInlineScriptStatementContext::SCRIPT() {
  return getToken(HmlParser::SCRIPT, 0);
}

tree::TerminalNode* HmlParser::DeferInlineScriptStatementContext::DEFER() {
  return getToken(HmlParser::DEFER, 0);
}

tree::TerminalNode* HmlParser::DeferInlineScriptStatementContext::SCRIPT_CONTENT() {
  return getToken(HmlParser::SCRIPT_CONTENT, 0);
}

HmlParser::DeferInlineScriptStatementContext::DeferInlineScriptStatementContext(ScriptStatementContext *ctx) { copyFrom(ctx); }

void HmlParser::DeferInlineScriptStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeferInlineScriptStatement(this);
}
void HmlParser::DeferInlineScriptStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeferInlineScriptStatement(this);
}

std::any HmlParser::DeferInlineScriptStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitDeferInlineScriptStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AsyncInlineScriptStatementContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::AsyncInlineScriptStatementContext::SCRIPT() {
  return getToken(HmlParser::SCRIPT, 0);
}

tree::TerminalNode* HmlParser::AsyncInlineScriptStatementContext::ASYNC() {
  return getToken(HmlParser::ASYNC, 0);
}

tree::TerminalNode* HmlParser::AsyncInlineScriptStatementContext::SCRIPT_CONTENT() {
  return getToken(HmlParser::SCRIPT_CONTENT, 0);
}

HmlParser::AsyncInlineScriptStatementContext::AsyncInlineScriptStatementContext(ScriptStatementContext *ctx) { copyFrom(ctx); }

void HmlParser::AsyncInlineScriptStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAsyncInlineScriptStatement(this);
}
void HmlParser::AsyncInlineScriptStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAsyncInlineScriptStatement(this);
}

std::any HmlParser::AsyncInlineScriptStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitAsyncInlineScriptStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefaultScriptStatementContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::DefaultScriptStatementContext::SCRIPT() {
  return getToken(HmlParser::SCRIPT, 0);
}

tree::TerminalNode* HmlParser::DefaultScriptStatementContext::STRING() {
  return getToken(HmlParser::STRING, 0);
}

HmlParser::DefaultScriptStatementContext::DefaultScriptStatementContext(ScriptStatementContext *ctx) { copyFrom(ctx); }

void HmlParser::DefaultScriptStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefaultScriptStatement(this);
}
void HmlParser::DefaultScriptStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefaultScriptStatement(this);
}

std::any HmlParser::DefaultScriptStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitDefaultScriptStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DeferScriptStatementContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::DeferScriptStatementContext::SCRIPT() {
  return getToken(HmlParser::SCRIPT, 0);
}

tree::TerminalNode* HmlParser::DeferScriptStatementContext::DEFER() {
  return getToken(HmlParser::DEFER, 0);
}

tree::TerminalNode* HmlParser::DeferScriptStatementContext::STRING() {
  return getToken(HmlParser::STRING, 0);
}

HmlParser::DeferScriptStatementContext::DeferScriptStatementContext(ScriptStatementContext *ctx) { copyFrom(ctx); }

void HmlParser::DeferScriptStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeferScriptStatement(this);
}
void HmlParser::DeferScriptStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeferScriptStatement(this);
}

std::any HmlParser::DeferScriptStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitDeferScriptStatement(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DefaultInlineScriptStatementContext ------------------------------------------------------------------

tree::TerminalNode* HmlParser::DefaultInlineScriptStatementContext::SCRIPT() {
  return getToken(HmlParser::SCRIPT, 0);
}

tree::TerminalNode* HmlParser::DefaultInlineScriptStatementContext::SCRIPT_CONTENT() {
  return getToken(HmlParser::SCRIPT_CONTENT, 0);
}

HmlParser::DefaultInlineScriptStatementContext::DefaultInlineScriptStatementContext(ScriptStatementContext *ctx) { copyFrom(ctx); }

void HmlParser::DefaultInlineScriptStatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDefaultInlineScriptStatement(this);
}
void HmlParser::DefaultInlineScriptStatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDefaultInlineScriptStatement(this);
}

std::any HmlParser::DefaultInlineScriptStatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitDefaultInlineScriptStatement(this);
  else
    return visitor->visitChildren(this);
}
HmlParser::ScriptStatementContext* HmlParser::scriptStatement() {
  ScriptStatementContext *_localctx = _tracker.createInstance<ScriptStatementContext>(_ctx, getState());
  enterRule(_localctx, 34, HmlParser::RuleScriptStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(247);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<HmlParser::DefaultScriptStatementContext>(_localctx);
      enterOuterAlt(_localctx, 1);
      setState(231);
      match(HmlParser::SCRIPT);
      setState(232);
      match(HmlParser::STRING);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<HmlParser::DeferScriptStatementContext>(_localctx);
      enterOuterAlt(_localctx, 2);
      setState(233);
      match(HmlParser::SCRIPT);
      setState(234);
      match(HmlParser::DEFER);
      setState(235);
      match(HmlParser::STRING);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<HmlParser::AsyncScriptStatementContext>(_localctx);
      enterOuterAlt(_localctx, 3);
      setState(236);
      match(HmlParser::SCRIPT);
      setState(237);
      match(HmlParser::ASYNC);
      setState(238);
      match(HmlParser::STRING);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<HmlParser::DefaultInlineScriptStatementContext>(_localctx);
      enterOuterAlt(_localctx, 4);
      setState(239);
      match(HmlParser::SCRIPT);
      setState(240);
      match(HmlParser::SCRIPT_CONTENT);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<HmlParser::DeferInlineScriptStatementContext>(_localctx);
      enterOuterAlt(_localctx, 5);
      setState(241);
      match(HmlParser::SCRIPT);
      setState(242);
      match(HmlParser::DEFER);
      setState(243);
      match(HmlParser::SCRIPT_CONTENT);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<HmlParser::AsyncInlineScriptStatementContext>(_localctx);
      enterOuterAlt(_localctx, 6);
      setState(244);
      match(HmlParser::SCRIPT);
      setState(245);
      match(HmlParser::ASYNC);
      setState(246);
      match(HmlParser::SCRIPT_CONTENT);
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

//----------------- FunctionCallContext ------------------------------------------------------------------

HmlParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::FunctionCallContext::ID() {
  return getToken(HmlParser::ID, 0);
}

tree::TerminalNode* HmlParser::FunctionCallContext::LPAREN() {
  return getToken(HmlParser::LPAREN, 0);
}

tree::TerminalNode* HmlParser::FunctionCallContext::RPAREN() {
  return getToken(HmlParser::RPAREN, 0);
}

HmlParser::ArgumentListContext* HmlParser::FunctionCallContext::argumentList() {
  return getRuleContext<HmlParser::ArgumentListContext>(0);
}


size_t HmlParser::FunctionCallContext::getRuleIndex() const {
  return HmlParser::RuleFunctionCall;
}

void HmlParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void HmlParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}


std::any HmlParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::FunctionCallContext* HmlParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 36, HmlParser::RuleFunctionCall);
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
    setState(249);
    match(HmlParser::ID);
    setState(250);
    match(HmlParser::LPAREN);
    setState(252);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 2267205861376) != 0)) {
      setState(251);
      argumentList();
    }
    setState(254);
    match(HmlParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgumentListContext ------------------------------------------------------------------

HmlParser::ArgumentListContext::ArgumentListContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<HmlParser::PropertyValueContext *> HmlParser::ArgumentListContext::propertyValue() {
  return getRuleContexts<HmlParser::PropertyValueContext>();
}

HmlParser::PropertyValueContext* HmlParser::ArgumentListContext::propertyValue(size_t i) {
  return getRuleContext<HmlParser::PropertyValueContext>(i);
}

std::vector<tree::TerminalNode *> HmlParser::ArgumentListContext::COMMA() {
  return getTokens(HmlParser::COMMA);
}

tree::TerminalNode* HmlParser::ArgumentListContext::COMMA(size_t i) {
  return getToken(HmlParser::COMMA, i);
}


size_t HmlParser::ArgumentListContext::getRuleIndex() const {
  return HmlParser::RuleArgumentList;
}

void HmlParser::ArgumentListContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgumentList(this);
}

void HmlParser::ArgumentListContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgumentList(this);
}


std::any HmlParser::ArgumentListContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitArgumentList(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ArgumentListContext* HmlParser::argumentList() {
  ArgumentListContext *_localctx = _tracker.createInstance<ArgumentListContext>(_ctx, getState());
  enterRule(_localctx, 38, HmlParser::RuleArgumentList);
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
    setState(256);
    propertyValue();
    setState(261);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == HmlParser::COMMA) {
      setState(257);
      match(HmlParser::COMMA);
      setState(258);
      propertyValue();
      setState(263);
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

//----------------- ElementTypeContext ------------------------------------------------------------------

HmlParser::ElementTypeContext::ElementTypeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* HmlParser::ElementTypeContext::ID() {
  return getToken(HmlParser::ID, 0);
}


size_t HmlParser::ElementTypeContext::getRuleIndex() const {
  return HmlParser::RuleElementType;
}

void HmlParser::ElementTypeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterElementType(this);
}

void HmlParser::ElementTypeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<HmlListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitElementType(this);
}


std::any HmlParser::ElementTypeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<HmlVisitor*>(visitor))
    return parserVisitor->visitElementType(this);
  else
    return visitor->visitChildren(this);
}

HmlParser::ElementTypeContext* HmlParser::elementType() {
  ElementTypeContext *_localctx = _tracker.createInstance<ElementTypeContext>(_ctx, getState());
  enterRule(_localctx, 40, HmlParser::RuleElementType);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(264);
    match(HmlParser::ID);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool HmlParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 11: return conditionalExpressionSempred(antlrcpp::downCast<ConditionalExpressionContext *>(context), predicateIndex);
    case 16: return complexExpressionSempred(antlrcpp::downCast<ComplexExpressionContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool HmlParser::conditionalExpressionSempred(ConditionalExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 4);
    case 1: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

bool HmlParser::complexExpressionSempred(ComplexExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return precpred(_ctx, 6);
    case 3: return precpred(_ctx, 5);
    case 4: return precpred(_ctx, 4);
    case 5: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void HmlParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  hmlParserInitialize();
#else
  ::antlr4::internal::call_once(hmlParserOnceFlag, hmlParserInitialize);
#endif
}
