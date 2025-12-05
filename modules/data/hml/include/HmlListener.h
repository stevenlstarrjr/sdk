
// Generated from Hml.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "HmlParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by HmlParser.
 */
class  HmlListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterHml(HmlParser::HmlContext *ctx) = 0;
  virtual void exitHml(HmlParser::HmlContext *ctx) = 0;

  virtual void enterElement(HmlParser::ElementContext *ctx) = 0;
  virtual void exitElement(HmlParser::ElementContext *ctx) = 0;

  virtual void enterElementBody(HmlParser::ElementBodyContext *ctx) = 0;
  virtual void exitElementBody(HmlParser::ElementBodyContext *ctx) = 0;

  virtual void enterIncludeStatement(HmlParser::IncludeStatementContext *ctx) = 0;
  virtual void exitIncludeStatement(HmlParser::IncludeStatementContext *ctx) = 0;

  virtual void enterImportStatement(HmlParser::ImportStatementContext *ctx) = 0;
  virtual void exitImportStatement(HmlParser::ImportStatementContext *ctx) = 0;

  virtual void enterVariableDeclaration(HmlParser::VariableDeclarationContext *ctx) = 0;
  virtual void exitVariableDeclaration(HmlParser::VariableDeclarationContext *ctx) = 0;

  virtual void enterSignalDeclaration(HmlParser::SignalDeclarationContext *ctx) = 0;
  virtual void exitSignalDeclaration(HmlParser::SignalDeclarationContext *ctx) = 0;

  virtual void enterTypeAnnotation(HmlParser::TypeAnnotationContext *ctx) = 0;
  virtual void exitTypeAnnotation(HmlParser::TypeAnnotationContext *ctx) = 0;

  virtual void enterParameterList(HmlParser::ParameterListContext *ctx) = 0;
  virtual void exitParameterList(HmlParser::ParameterListContext *ctx) = 0;

  virtual void enterParameter(HmlParser::ParameterContext *ctx) = 0;
  virtual void exitParameter(HmlParser::ParameterContext *ctx) = 0;

  virtual void enterConditionalStatement(HmlParser::ConditionalStatementContext *ctx) = 0;
  virtual void exitConditionalStatement(HmlParser::ConditionalStatementContext *ctx) = 0;

  virtual void enterEqualityCondition(HmlParser::EqualityConditionContext *ctx) = 0;
  virtual void exitEqualityCondition(HmlParser::EqualityConditionContext *ctx) = 0;

  virtual void enterBooleanCondition(HmlParser::BooleanConditionContext *ctx) = 0;
  virtual void exitBooleanCondition(HmlParser::BooleanConditionContext *ctx) = 0;

  virtual void enterNotCondition(HmlParser::NotConditionContext *ctx) = 0;
  virtual void exitNotCondition(HmlParser::NotConditionContext *ctx) = 0;

  virtual void enterGreaterThanCondition(HmlParser::GreaterThanConditionContext *ctx) = 0;
  virtual void exitGreaterThanCondition(HmlParser::GreaterThanConditionContext *ctx) = 0;

  virtual void enterGreaterEqualCondition(HmlParser::GreaterEqualConditionContext *ctx) = 0;
  virtual void exitGreaterEqualCondition(HmlParser::GreaterEqualConditionContext *ctx) = 0;

  virtual void enterVariableCondition(HmlParser::VariableConditionContext *ctx) = 0;
  virtual void exitVariableCondition(HmlParser::VariableConditionContext *ctx) = 0;

  virtual void enterParenCondition(HmlParser::ParenConditionContext *ctx) = 0;
  virtual void exitParenCondition(HmlParser::ParenConditionContext *ctx) = 0;

  virtual void enterLessThanCondition(HmlParser::LessThanConditionContext *ctx) = 0;
  virtual void exitLessThanCondition(HmlParser::LessThanConditionContext *ctx) = 0;

  virtual void enterLessEqualCondition(HmlParser::LessEqualConditionContext *ctx) = 0;
  virtual void exitLessEqualCondition(HmlParser::LessEqualConditionContext *ctx) = 0;

  virtual void enterInequalityCondition(HmlParser::InequalityConditionContext *ctx) = 0;
  virtual void exitInequalityCondition(HmlParser::InequalityConditionContext *ctx) = 0;

  virtual void enterOrCondition(HmlParser::OrConditionContext *ctx) = 0;
  virtual void exitOrCondition(HmlParser::OrConditionContext *ctx) = 0;

  virtual void enterAndCondition(HmlParser::AndConditionContext *ctx) = 0;
  virtual void exitAndCondition(HmlParser::AndConditionContext *ctx) = 0;

  virtual void enterProperty(HmlParser::PropertyContext *ctx) = 0;
  virtual void exitProperty(HmlParser::PropertyContext *ctx) = 0;

  virtual void enterPropertyName(HmlParser::PropertyNameContext *ctx) = 0;
  virtual void exitPropertyName(HmlParser::PropertyNameContext *ctx) = 0;

  virtual void enterEventHandler(HmlParser::EventHandlerContext *ctx) = 0;
  virtual void exitEventHandler(HmlParser::EventHandlerContext *ctx) = 0;

  virtual void enterStringValue(HmlParser::StringValueContext *ctx) = 0;
  virtual void exitStringValue(HmlParser::StringValueContext *ctx) = 0;

  virtual void enterNumberValue(HmlParser::NumberValueContext *ctx) = 0;
  virtual void exitNumberValue(HmlParser::NumberValueContext *ctx) = 0;

  virtual void enterColorValue(HmlParser::ColorValueContext *ctx) = 0;
  virtual void exitColorValue(HmlParser::ColorValueContext *ctx) = 0;

  virtual void enterBooleanValue(HmlParser::BooleanValueContext *ctx) = 0;
  virtual void exitBooleanValue(HmlParser::BooleanValueContext *ctx) = 0;

  virtual void enterScriptValue(HmlParser::ScriptValueContext *ctx) = 0;
  virtual void exitScriptValue(HmlParser::ScriptValueContext *ctx) = 0;

  virtual void enterFunctionValue(HmlParser::FunctionValueContext *ctx) = 0;
  virtual void exitFunctionValue(HmlParser::FunctionValueContext *ctx) = 0;

  virtual void enterIdentifierValue(HmlParser::IdentifierValueContext *ctx) = 0;
  virtual void exitIdentifierValue(HmlParser::IdentifierValueContext *ctx) = 0;

  virtual void enterExpressionValue(HmlParser::ExpressionValueContext *ctx) = 0;
  virtual void exitExpressionValue(HmlParser::ExpressionValueContext *ctx) = 0;

  virtual void enterComplexExpressionValue(HmlParser::ComplexExpressionValueContext *ctx) = 0;
  virtual void exitComplexExpressionValue(HmlParser::ComplexExpressionValueContext *ctx) = 0;

  virtual void enterSubtractExpression(HmlParser::SubtractExpressionContext *ctx) = 0;
  virtual void exitSubtractExpression(HmlParser::SubtractExpressionContext *ctx) = 0;

  virtual void enterDivideExpression(HmlParser::DivideExpressionContext *ctx) = 0;
  virtual void exitDivideExpression(HmlParser::DivideExpressionContext *ctx) = 0;

  virtual void enterAddExpression(HmlParser::AddExpressionContext *ctx) = 0;
  virtual void exitAddExpression(HmlParser::AddExpressionContext *ctx) = 0;

  virtual void enterMultiplyExpression(HmlParser::MultiplyExpressionContext *ctx) = 0;
  virtual void exitMultiplyExpression(HmlParser::MultiplyExpressionContext *ctx) = 0;

  virtual void enterParenExpression(HmlParser::ParenExpressionContext *ctx) = 0;
  virtual void exitParenExpression(HmlParser::ParenExpressionContext *ctx) = 0;

  virtual void enterNumberExpression(HmlParser::NumberExpressionContext *ctx) = 0;
  virtual void exitNumberExpression(HmlParser::NumberExpressionContext *ctx) = 0;

  virtual void enterSimpleExpression(HmlParser::SimpleExpressionContext *ctx) = 0;
  virtual void exitSimpleExpression(HmlParser::SimpleExpressionContext *ctx) = 0;

  virtual void enterDefaultScriptStatement(HmlParser::DefaultScriptStatementContext *ctx) = 0;
  virtual void exitDefaultScriptStatement(HmlParser::DefaultScriptStatementContext *ctx) = 0;

  virtual void enterDeferScriptStatement(HmlParser::DeferScriptStatementContext *ctx) = 0;
  virtual void exitDeferScriptStatement(HmlParser::DeferScriptStatementContext *ctx) = 0;

  virtual void enterAsyncScriptStatement(HmlParser::AsyncScriptStatementContext *ctx) = 0;
  virtual void exitAsyncScriptStatement(HmlParser::AsyncScriptStatementContext *ctx) = 0;

  virtual void enterDefaultInlineScriptStatement(HmlParser::DefaultInlineScriptStatementContext *ctx) = 0;
  virtual void exitDefaultInlineScriptStatement(HmlParser::DefaultInlineScriptStatementContext *ctx) = 0;

  virtual void enterDeferInlineScriptStatement(HmlParser::DeferInlineScriptStatementContext *ctx) = 0;
  virtual void exitDeferInlineScriptStatement(HmlParser::DeferInlineScriptStatementContext *ctx) = 0;

  virtual void enterAsyncInlineScriptStatement(HmlParser::AsyncInlineScriptStatementContext *ctx) = 0;
  virtual void exitAsyncInlineScriptStatement(HmlParser::AsyncInlineScriptStatementContext *ctx) = 0;

  virtual void enterFunctionCall(HmlParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(HmlParser::FunctionCallContext *ctx) = 0;

  virtual void enterArgumentList(HmlParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(HmlParser::ArgumentListContext *ctx) = 0;

  virtual void enterElementType(HmlParser::ElementTypeContext *ctx) = 0;
  virtual void exitElementType(HmlParser::ElementTypeContext *ctx) = 0;


};

