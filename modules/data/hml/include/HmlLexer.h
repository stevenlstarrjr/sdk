
// Generated from Hml.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  HmlLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, INCLUDE = 11, IMPORT = 12, SCRIPT = 13, 
    DEFER = 14, ASYNC = 15, VAR = 16, SIGNAL = 17, IF = 18, ELSE = 19, EQ = 20, 
    NE = 21, GT = 22, LT = 23, GE = 24, LE = 25, AND = 26, OR = 27, NOT = 28, 
    ID = 29, STRING = 30, SCRIPT_CONTENT = 31, EXPRESSION = 32, NUMBER = 33, 
    COLOR = 34, BOOLEAN = 35, WS = 36, LINE_COMMENT = 37, BLOCK_COMMENT = 38, 
    LBRACE = 39, RBRACE = 40, LPAREN = 41, RPAREN = 42, COLON = 43, COMMA = 44, 
    SEMICOLON = 45
  };

  explicit HmlLexer(antlr4::CharStream *input);

  ~HmlLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

