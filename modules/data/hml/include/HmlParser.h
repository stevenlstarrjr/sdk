
// Generated from Hml.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  HmlParser : public antlr4::Parser {
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

  enum {
    RuleHml = 0, RuleElement = 1, RuleElementBody = 2, RuleIncludeStatement = 3, 
    RuleImportStatement = 4, RuleVariableDeclaration = 5, RuleSignalDeclaration = 6, 
    RuleTypeAnnotation = 7, RuleParameterList = 8, RuleParameter = 9, RuleConditionalStatement = 10, 
    RuleConditionalExpression = 11, RuleProperty = 12, RulePropertyName = 13, 
    RuleEventHandler = 14, RulePropertyValue = 15, RuleComplexExpression = 16, 
    RuleScriptStatement = 17, RuleFunctionCall = 18, RuleArgumentList = 19, 
    RuleElementType = 20
  };

  explicit HmlParser(antlr4::TokenStream *input);

  HmlParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~HmlParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class HmlContext;
  class ElementContext;
  class ElementBodyContext;
  class IncludeStatementContext;
  class ImportStatementContext;
  class VariableDeclarationContext;
  class SignalDeclarationContext;
  class TypeAnnotationContext;
  class ParameterListContext;
  class ParameterContext;
  class ConditionalStatementContext;
  class ConditionalExpressionContext;
  class PropertyContext;
  class PropertyNameContext;
  class EventHandlerContext;
  class PropertyValueContext;
  class ComplexExpressionContext;
  class ScriptStatementContext;
  class FunctionCallContext;
  class ArgumentListContext;
  class ElementTypeContext; 

  class  HmlContext : public antlr4::ParserRuleContext {
  public:
    HmlContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EOF();
    std::vector<ImportStatementContext *> importStatement();
    ImportStatementContext* importStatement(size_t i);
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);
    std::vector<IncludeStatementContext *> includeStatement();
    IncludeStatementContext* includeStatement(size_t i);
    std::vector<ElementContext *> element();
    ElementContext* element(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  HmlContext* hml();

  class  ElementContext : public antlr4::ParserRuleContext {
  public:
    ElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ElementTypeContext *elementType();
    antlr4::tree::TerminalNode *LBRACE();
    ElementBodyContext *elementBody();
    antlr4::tree::TerminalNode *RBRACE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementContext* element();

  class  ElementBodyContext : public antlr4::ParserRuleContext {
  public:
    ElementBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PropertyContext *> property();
    PropertyContext* property(size_t i);
    std::vector<ElementContext *> element();
    ElementContext* element(size_t i);
    std::vector<IncludeStatementContext *> includeStatement();
    IncludeStatementContext* includeStatement(size_t i);
    std::vector<ScriptStatementContext *> scriptStatement();
    ScriptStatementContext* scriptStatement(size_t i);
    std::vector<VariableDeclarationContext *> variableDeclaration();
    VariableDeclarationContext* variableDeclaration(size_t i);
    std::vector<ConditionalStatementContext *> conditionalStatement();
    ConditionalStatementContext* conditionalStatement(size_t i);
    std::vector<SignalDeclarationContext *> signalDeclaration();
    SignalDeclarationContext* signalDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementBodyContext* elementBody();

  class  IncludeStatementContext : public antlr4::ParserRuleContext {
  public:
    IncludeStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INCLUDE();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IncludeStatementContext* includeStatement();

  class  ImportStatementContext : public antlr4::ParserRuleContext {
  public:
    ImportStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportStatementContext* importStatement();

  class  VariableDeclarationContext : public antlr4::ParserRuleContext {
  public:
    VariableDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VAR();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeAnnotationContext *typeAnnotation();
    PropertyValueContext *propertyValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  VariableDeclarationContext* variableDeclaration();

  class  SignalDeclarationContext : public antlr4::ParserRuleContext {
  public:
    SignalDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SIGNAL();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ParameterListContext *parameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SignalDeclarationContext* signalDeclaration();

  class  TypeAnnotationContext : public antlr4::ParserRuleContext {
  public:
    TypeAnnotationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeAnnotationContext* typeAnnotation();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeAnnotationContext *typeAnnotation();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterContext* parameter();

  class  ConditionalStatementContext : public antlr4::ParserRuleContext {
  public:
    ConditionalStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IF();
    antlr4::tree::TerminalNode *LPAREN();
    ConditionalExpressionContext *conditionalExpression();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<antlr4::tree::TerminalNode *> LBRACE();
    antlr4::tree::TerminalNode* LBRACE(size_t i);
    std::vector<ElementBodyContext *> elementBody();
    ElementBodyContext* elementBody(size_t i);
    std::vector<antlr4::tree::TerminalNode *> RBRACE();
    antlr4::tree::TerminalNode* RBRACE(size_t i);
    antlr4::tree::TerminalNode *ELSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConditionalStatementContext* conditionalStatement();

  class  ConditionalExpressionContext : public antlr4::ParserRuleContext {
  public:
    ConditionalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ConditionalExpressionContext() = default;
    void copyFrom(ConditionalExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  EqualityConditionContext : public ConditionalExpressionContext {
  public:
    EqualityConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EQ();
    PropertyValueContext *propertyValue();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BooleanConditionContext : public ConditionalExpressionContext {
  public:
    BooleanConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *BOOLEAN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NotConditionContext : public ConditionalExpressionContext {
  public:
    NotConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *NOT();
    ConditionalExpressionContext *conditionalExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GreaterThanConditionContext : public ConditionalExpressionContext {
  public:
    GreaterThanConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *NUMBER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  GreaterEqualConditionContext : public ConditionalExpressionContext {
  public:
    GreaterEqualConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *GE();
    antlr4::tree::TerminalNode *NUMBER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  VariableConditionContext : public ConditionalExpressionContext {
  public:
    VariableConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenConditionContext : public ConditionalExpressionContext {
  public:
    ParenConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ConditionalExpressionContext *conditionalExpression();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LessThanConditionContext : public ConditionalExpressionContext {
  public:
    LessThanConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *NUMBER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  LessEqualConditionContext : public ConditionalExpressionContext {
  public:
    LessEqualConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *NUMBER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  InequalityConditionContext : public ConditionalExpressionContext {
  public:
    InequalityConditionContext(ConditionalExpressionContext *ctx);

    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *NE();
    PropertyValueContext *propertyValue();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  OrConditionContext : public ConditionalExpressionContext {
  public:
    OrConditionContext(ConditionalExpressionContext *ctx);

    std::vector<ConditionalExpressionContext *> conditionalExpression();
    ConditionalExpressionContext* conditionalExpression(size_t i);
    antlr4::tree::TerminalNode *OR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AndConditionContext : public ConditionalExpressionContext {
  public:
    AndConditionContext(ConditionalExpressionContext *ctx);

    std::vector<ConditionalExpressionContext *> conditionalExpression();
    ConditionalExpressionContext* conditionalExpression(size_t i);
    antlr4::tree::TerminalNode *AND();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ConditionalExpressionContext* conditionalExpression();
  ConditionalExpressionContext* conditionalExpression(int precedence);
  class  PropertyContext : public antlr4::ParserRuleContext {
  public:
    PropertyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PropertyNameContext *propertyName();
    antlr4::tree::TerminalNode *COLON();
    PropertyValueContext *propertyValue();
    EventHandlerContext *eventHandler();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyContext* property();

  class  PropertyNameContext : public antlr4::ParserRuleContext {
  public:
    PropertyNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PropertyNameContext* propertyName();

  class  EventHandlerContext : public antlr4::ParserRuleContext {
  public:
    EventHandlerContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EventHandlerContext* eventHandler();

  class  PropertyValueContext : public antlr4::ParserRuleContext {
  public:
    PropertyValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    PropertyValueContext() = default;
    void copyFrom(PropertyValueContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ScriptValueContext : public PropertyValueContext {
  public:
    ScriptValueContext(PropertyValueContext *ctx);

    antlr4::tree::TerminalNode *SCRIPT_CONTENT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NumberValueContext : public PropertyValueContext {
  public:
    NumberValueContext(PropertyValueContext *ctx);

    antlr4::tree::TerminalNode *NUMBER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExpressionValueContext : public PropertyValueContext {
  public:
    ExpressionValueContext(PropertyValueContext *ctx);

    antlr4::tree::TerminalNode *EXPRESSION();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ColorValueContext : public PropertyValueContext {
  public:
    ColorValueContext(PropertyValueContext *ctx);

    antlr4::tree::TerminalNode *COLOR();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  BooleanValueContext : public PropertyValueContext {
  public:
    BooleanValueContext(PropertyValueContext *ctx);

    antlr4::tree::TerminalNode *BOOLEAN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ComplexExpressionValueContext : public PropertyValueContext {
  public:
    ComplexExpressionValueContext(PropertyValueContext *ctx);

    ComplexExpressionContext *complexExpression();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FunctionValueContext : public PropertyValueContext {
  public:
    FunctionValueContext(PropertyValueContext *ctx);

    FunctionCallContext *functionCall();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  IdentifierValueContext : public PropertyValueContext {
  public:
    IdentifierValueContext(PropertyValueContext *ctx);

    antlr4::tree::TerminalNode *ID();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  StringValueContext : public PropertyValueContext {
  public:
    StringValueContext(PropertyValueContext *ctx);

    antlr4::tree::TerminalNode *STRING();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  PropertyValueContext* propertyValue();

  class  ComplexExpressionContext : public antlr4::ParserRuleContext {
  public:
    ComplexExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ComplexExpressionContext() = default;
    void copyFrom(ComplexExpressionContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  SubtractExpressionContext : public ComplexExpressionContext {
  public:
    SubtractExpressionContext(ComplexExpressionContext *ctx);

    std::vector<ComplexExpressionContext *> complexExpression();
    ComplexExpressionContext* complexExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DivideExpressionContext : public ComplexExpressionContext {
  public:
    DivideExpressionContext(ComplexExpressionContext *ctx);

    std::vector<ComplexExpressionContext *> complexExpression();
    ComplexExpressionContext* complexExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AddExpressionContext : public ComplexExpressionContext {
  public:
    AddExpressionContext(ComplexExpressionContext *ctx);

    std::vector<ComplexExpressionContext *> complexExpression();
    ComplexExpressionContext* complexExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  MultiplyExpressionContext : public ComplexExpressionContext {
  public:
    MultiplyExpressionContext(ComplexExpressionContext *ctx);

    std::vector<ComplexExpressionContext *> complexExpression();
    ComplexExpressionContext* complexExpression(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ParenExpressionContext : public ComplexExpressionContext {
  public:
    ParenExpressionContext(ComplexExpressionContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ComplexExpressionContext *complexExpression();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  NumberExpressionContext : public ComplexExpressionContext {
  public:
    NumberExpressionContext(ComplexExpressionContext *ctx);

    antlr4::tree::TerminalNode *NUMBER();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  SimpleExpressionContext : public ComplexExpressionContext {
  public:
    SimpleExpressionContext(ComplexExpressionContext *ctx);

    antlr4::tree::TerminalNode *EXPRESSION();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ComplexExpressionContext* complexExpression();
  ComplexExpressionContext* complexExpression(int precedence);
  class  ScriptStatementContext : public antlr4::ParserRuleContext {
  public:
    ScriptStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ScriptStatementContext() = default;
    void copyFrom(ScriptStatementContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  AsyncScriptStatementContext : public ScriptStatementContext {
  public:
    AsyncScriptStatementContext(ScriptStatementContext *ctx);

    antlr4::tree::TerminalNode *SCRIPT();
    antlr4::tree::TerminalNode *ASYNC();
    antlr4::tree::TerminalNode *STRING();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DeferInlineScriptStatementContext : public ScriptStatementContext {
  public:
    DeferInlineScriptStatementContext(ScriptStatementContext *ctx);

    antlr4::tree::TerminalNode *SCRIPT();
    antlr4::tree::TerminalNode *DEFER();
    antlr4::tree::TerminalNode *SCRIPT_CONTENT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  AsyncInlineScriptStatementContext : public ScriptStatementContext {
  public:
    AsyncInlineScriptStatementContext(ScriptStatementContext *ctx);

    antlr4::tree::TerminalNode *SCRIPT();
    antlr4::tree::TerminalNode *ASYNC();
    antlr4::tree::TerminalNode *SCRIPT_CONTENT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DefaultScriptStatementContext : public ScriptStatementContext {
  public:
    DefaultScriptStatementContext(ScriptStatementContext *ctx);

    antlr4::tree::TerminalNode *SCRIPT();
    antlr4::tree::TerminalNode *STRING();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DeferScriptStatementContext : public ScriptStatementContext {
  public:
    DeferScriptStatementContext(ScriptStatementContext *ctx);

    antlr4::tree::TerminalNode *SCRIPT();
    antlr4::tree::TerminalNode *DEFER();
    antlr4::tree::TerminalNode *STRING();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  DefaultInlineScriptStatementContext : public ScriptStatementContext {
  public:
    DefaultInlineScriptStatementContext(ScriptStatementContext *ctx);

    antlr4::tree::TerminalNode *SCRIPT();
    antlr4::tree::TerminalNode *SCRIPT_CONTENT();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ScriptStatementContext* scriptStatement();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentListContext *argumentList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionCallContext* functionCall();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PropertyValueContext *> propertyValue();
    PropertyValueContext* propertyValue(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListContext* argumentList();

  class  ElementTypeContext : public antlr4::ParserRuleContext {
  public:
    ElementTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ElementTypeContext* elementType();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool conditionalExpressionSempred(ConditionalExpressionContext *_localctx, size_t predicateIndex);
  bool complexExpressionSempred(ComplexExpressionContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

