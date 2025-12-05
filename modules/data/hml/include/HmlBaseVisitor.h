
// Generated from Hml.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "HmlVisitor.h"


/**
 * This class provides an empty implementation of HmlVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  HmlBaseVisitor : public HmlVisitor {
public:

  virtual std::any visitHml(HmlParser::HmlContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElement(HmlParser::ElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementBody(HmlParser::ElementBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIncludeStatement(HmlParser::IncludeStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportStatement(HmlParser::ImportStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableDeclaration(HmlParser::VariableDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSignalDeclaration(HmlParser::SignalDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeAnnotation(HmlParser::TypeAnnotationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(HmlParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(HmlParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConditionalStatement(HmlParser::ConditionalStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityCondition(HmlParser::EqualityConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBooleanCondition(HmlParser::BooleanConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNotCondition(HmlParser::NotConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGreaterThanCondition(HmlParser::GreaterThanConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGreaterEqualCondition(HmlParser::GreaterEqualConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitVariableCondition(HmlParser::VariableConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenCondition(HmlParser::ParenConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLessThanCondition(HmlParser::LessThanConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLessEqualCondition(HmlParser::LessEqualConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInequalityCondition(HmlParser::InequalityConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrCondition(HmlParser::OrConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndCondition(HmlParser::AndConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProperty(HmlParser::PropertyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPropertyName(HmlParser::PropertyNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEventHandler(HmlParser::EventHandlerContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringValue(HmlParser::StringValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberValue(HmlParser::NumberValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitColorValue(HmlParser::ColorValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBooleanValue(HmlParser::BooleanValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScriptValue(HmlParser::ScriptValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionValue(HmlParser::FunctionValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierValue(HmlParser::IdentifierValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionValue(HmlParser::ExpressionValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComplexExpressionValue(HmlParser::ComplexExpressionValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSubtractExpression(HmlParser::SubtractExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDivideExpression(HmlParser::DivideExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAddExpression(HmlParser::AddExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplyExpression(HmlParser::MultiplyExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenExpression(HmlParser::ParenExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumberExpression(HmlParser::NumberExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleExpression(HmlParser::SimpleExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefaultScriptStatement(HmlParser::DefaultScriptStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeferScriptStatement(HmlParser::DeferScriptStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAsyncScriptStatement(HmlParser::AsyncScriptStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDefaultInlineScriptStatement(HmlParser::DefaultInlineScriptStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeferInlineScriptStatement(HmlParser::DeferInlineScriptStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAsyncInlineScriptStatement(HmlParser::AsyncInlineScriptStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(HmlParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(HmlParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitElementType(HmlParser::ElementTypeContext *ctx) override {
    return visitChildren(ctx);
  }


};

