
// Generated from Hml.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "HmlListener.h"


/**
 * This class provides an empty implementation of HmlListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  HmlBaseListener : public HmlListener {
public:

  virtual void enterHml(HmlParser::HmlContext * /*ctx*/) override { }
  virtual void exitHml(HmlParser::HmlContext * /*ctx*/) override { }

  virtual void enterElement(HmlParser::ElementContext * /*ctx*/) override { }
  virtual void exitElement(HmlParser::ElementContext * /*ctx*/) override { }

  virtual void enterElementBody(HmlParser::ElementBodyContext * /*ctx*/) override { }
  virtual void exitElementBody(HmlParser::ElementBodyContext * /*ctx*/) override { }

  virtual void enterIncludeStatement(HmlParser::IncludeStatementContext * /*ctx*/) override { }
  virtual void exitIncludeStatement(HmlParser::IncludeStatementContext * /*ctx*/) override { }

  virtual void enterImportStatement(HmlParser::ImportStatementContext * /*ctx*/) override { }
  virtual void exitImportStatement(HmlParser::ImportStatementContext * /*ctx*/) override { }

  virtual void enterVariableDeclaration(HmlParser::VariableDeclarationContext * /*ctx*/) override { }
  virtual void exitVariableDeclaration(HmlParser::VariableDeclarationContext * /*ctx*/) override { }

  virtual void enterSignalDeclaration(HmlParser::SignalDeclarationContext * /*ctx*/) override { }
  virtual void exitSignalDeclaration(HmlParser::SignalDeclarationContext * /*ctx*/) override { }

  virtual void enterTypeAnnotation(HmlParser::TypeAnnotationContext * /*ctx*/) override { }
  virtual void exitTypeAnnotation(HmlParser::TypeAnnotationContext * /*ctx*/) override { }

  virtual void enterParameterList(HmlParser::ParameterListContext * /*ctx*/) override { }
  virtual void exitParameterList(HmlParser::ParameterListContext * /*ctx*/) override { }

  virtual void enterParameter(HmlParser::ParameterContext * /*ctx*/) override { }
  virtual void exitParameter(HmlParser::ParameterContext * /*ctx*/) override { }

  virtual void enterConditionalStatement(HmlParser::ConditionalStatementContext * /*ctx*/) override { }
  virtual void exitConditionalStatement(HmlParser::ConditionalStatementContext * /*ctx*/) override { }

  virtual void enterEqualityCondition(HmlParser::EqualityConditionContext * /*ctx*/) override { }
  virtual void exitEqualityCondition(HmlParser::EqualityConditionContext * /*ctx*/) override { }

  virtual void enterBooleanCondition(HmlParser::BooleanConditionContext * /*ctx*/) override { }
  virtual void exitBooleanCondition(HmlParser::BooleanConditionContext * /*ctx*/) override { }

  virtual void enterNotCondition(HmlParser::NotConditionContext * /*ctx*/) override { }
  virtual void exitNotCondition(HmlParser::NotConditionContext * /*ctx*/) override { }

  virtual void enterGreaterThanCondition(HmlParser::GreaterThanConditionContext * /*ctx*/) override { }
  virtual void exitGreaterThanCondition(HmlParser::GreaterThanConditionContext * /*ctx*/) override { }

  virtual void enterGreaterEqualCondition(HmlParser::GreaterEqualConditionContext * /*ctx*/) override { }
  virtual void exitGreaterEqualCondition(HmlParser::GreaterEqualConditionContext * /*ctx*/) override { }

  virtual void enterVariableCondition(HmlParser::VariableConditionContext * /*ctx*/) override { }
  virtual void exitVariableCondition(HmlParser::VariableConditionContext * /*ctx*/) override { }

  virtual void enterParenCondition(HmlParser::ParenConditionContext * /*ctx*/) override { }
  virtual void exitParenCondition(HmlParser::ParenConditionContext * /*ctx*/) override { }

  virtual void enterLessThanCondition(HmlParser::LessThanConditionContext * /*ctx*/) override { }
  virtual void exitLessThanCondition(HmlParser::LessThanConditionContext * /*ctx*/) override { }

  virtual void enterLessEqualCondition(HmlParser::LessEqualConditionContext * /*ctx*/) override { }
  virtual void exitLessEqualCondition(HmlParser::LessEqualConditionContext * /*ctx*/) override { }

  virtual void enterInequalityCondition(HmlParser::InequalityConditionContext * /*ctx*/) override { }
  virtual void exitInequalityCondition(HmlParser::InequalityConditionContext * /*ctx*/) override { }

  virtual void enterOrCondition(HmlParser::OrConditionContext * /*ctx*/) override { }
  virtual void exitOrCondition(HmlParser::OrConditionContext * /*ctx*/) override { }

  virtual void enterAndCondition(HmlParser::AndConditionContext * /*ctx*/) override { }
  virtual void exitAndCondition(HmlParser::AndConditionContext * /*ctx*/) override { }

  virtual void enterProperty(HmlParser::PropertyContext * /*ctx*/) override { }
  virtual void exitProperty(HmlParser::PropertyContext * /*ctx*/) override { }

  virtual void enterPropertyName(HmlParser::PropertyNameContext * /*ctx*/) override { }
  virtual void exitPropertyName(HmlParser::PropertyNameContext * /*ctx*/) override { }

  virtual void enterEventHandler(HmlParser::EventHandlerContext * /*ctx*/) override { }
  virtual void exitEventHandler(HmlParser::EventHandlerContext * /*ctx*/) override { }

  virtual void enterStringValue(HmlParser::StringValueContext * /*ctx*/) override { }
  virtual void exitStringValue(HmlParser::StringValueContext * /*ctx*/) override { }

  virtual void enterNumberValue(HmlParser::NumberValueContext * /*ctx*/) override { }
  virtual void exitNumberValue(HmlParser::NumberValueContext * /*ctx*/) override { }

  virtual void enterColorValue(HmlParser::ColorValueContext * /*ctx*/) override { }
  virtual void exitColorValue(HmlParser::ColorValueContext * /*ctx*/) override { }

  virtual void enterBooleanValue(HmlParser::BooleanValueContext * /*ctx*/) override { }
  virtual void exitBooleanValue(HmlParser::BooleanValueContext * /*ctx*/) override { }

  virtual void enterScriptValue(HmlParser::ScriptValueContext * /*ctx*/) override { }
  virtual void exitScriptValue(HmlParser::ScriptValueContext * /*ctx*/) override { }

  virtual void enterFunctionValue(HmlParser::FunctionValueContext * /*ctx*/) override { }
  virtual void exitFunctionValue(HmlParser::FunctionValueContext * /*ctx*/) override { }

  virtual void enterIdentifierValue(HmlParser::IdentifierValueContext * /*ctx*/) override { }
  virtual void exitIdentifierValue(HmlParser::IdentifierValueContext * /*ctx*/) override { }

  virtual void enterExpressionValue(HmlParser::ExpressionValueContext * /*ctx*/) override { }
  virtual void exitExpressionValue(HmlParser::ExpressionValueContext * /*ctx*/) override { }

  virtual void enterComplexExpressionValue(HmlParser::ComplexExpressionValueContext * /*ctx*/) override { }
  virtual void exitComplexExpressionValue(HmlParser::ComplexExpressionValueContext * /*ctx*/) override { }

  virtual void enterSubtractExpression(HmlParser::SubtractExpressionContext * /*ctx*/) override { }
  virtual void exitSubtractExpression(HmlParser::SubtractExpressionContext * /*ctx*/) override { }

  virtual void enterDivideExpression(HmlParser::DivideExpressionContext * /*ctx*/) override { }
  virtual void exitDivideExpression(HmlParser::DivideExpressionContext * /*ctx*/) override { }

  virtual void enterAddExpression(HmlParser::AddExpressionContext * /*ctx*/) override { }
  virtual void exitAddExpression(HmlParser::AddExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplyExpression(HmlParser::MultiplyExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplyExpression(HmlParser::MultiplyExpressionContext * /*ctx*/) override { }

  virtual void enterParenExpression(HmlParser::ParenExpressionContext * /*ctx*/) override { }
  virtual void exitParenExpression(HmlParser::ParenExpressionContext * /*ctx*/) override { }

  virtual void enterNumberExpression(HmlParser::NumberExpressionContext * /*ctx*/) override { }
  virtual void exitNumberExpression(HmlParser::NumberExpressionContext * /*ctx*/) override { }

  virtual void enterSimpleExpression(HmlParser::SimpleExpressionContext * /*ctx*/) override { }
  virtual void exitSimpleExpression(HmlParser::SimpleExpressionContext * /*ctx*/) override { }

  virtual void enterDefaultScriptStatement(HmlParser::DefaultScriptStatementContext * /*ctx*/) override { }
  virtual void exitDefaultScriptStatement(HmlParser::DefaultScriptStatementContext * /*ctx*/) override { }

  virtual void enterDeferScriptStatement(HmlParser::DeferScriptStatementContext * /*ctx*/) override { }
  virtual void exitDeferScriptStatement(HmlParser::DeferScriptStatementContext * /*ctx*/) override { }

  virtual void enterAsyncScriptStatement(HmlParser::AsyncScriptStatementContext * /*ctx*/) override { }
  virtual void exitAsyncScriptStatement(HmlParser::AsyncScriptStatementContext * /*ctx*/) override { }

  virtual void enterDefaultInlineScriptStatement(HmlParser::DefaultInlineScriptStatementContext * /*ctx*/) override { }
  virtual void exitDefaultInlineScriptStatement(HmlParser::DefaultInlineScriptStatementContext * /*ctx*/) override { }

  virtual void enterDeferInlineScriptStatement(HmlParser::DeferInlineScriptStatementContext * /*ctx*/) override { }
  virtual void exitDeferInlineScriptStatement(HmlParser::DeferInlineScriptStatementContext * /*ctx*/) override { }

  virtual void enterAsyncInlineScriptStatement(HmlParser::AsyncInlineScriptStatementContext * /*ctx*/) override { }
  virtual void exitAsyncInlineScriptStatement(HmlParser::AsyncInlineScriptStatementContext * /*ctx*/) override { }

  virtual void enterFunctionCall(HmlParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(HmlParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterArgumentList(HmlParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(HmlParser::ArgumentListContext * /*ctx*/) override { }

  virtual void enterElementType(HmlParser::ElementTypeContext * /*ctx*/) override { }
  virtual void exitElementType(HmlParser::ElementTypeContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

