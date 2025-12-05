
// Generated from Hml.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "HmlParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by HmlParser.
 */
class  HmlVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by HmlParser.
   */
    virtual std::any visitHml(HmlParser::HmlContext *context) = 0;

    virtual std::any visitElement(HmlParser::ElementContext *context) = 0;

    virtual std::any visitElementBody(HmlParser::ElementBodyContext *context) = 0;

    virtual std::any visitIncludeStatement(HmlParser::IncludeStatementContext *context) = 0;

    virtual std::any visitImportStatement(HmlParser::ImportStatementContext *context) = 0;

    virtual std::any visitVariableDeclaration(HmlParser::VariableDeclarationContext *context) = 0;

    virtual std::any visitSignalDeclaration(HmlParser::SignalDeclarationContext *context) = 0;

    virtual std::any visitTypeAnnotation(HmlParser::TypeAnnotationContext *context) = 0;

    virtual std::any visitParameterList(HmlParser::ParameterListContext *context) = 0;

    virtual std::any visitParameter(HmlParser::ParameterContext *context) = 0;

    virtual std::any visitConditionalStatement(HmlParser::ConditionalStatementContext *context) = 0;

    virtual std::any visitEqualityCondition(HmlParser::EqualityConditionContext *context) = 0;

    virtual std::any visitBooleanCondition(HmlParser::BooleanConditionContext *context) = 0;

    virtual std::any visitNotCondition(HmlParser::NotConditionContext *context) = 0;

    virtual std::any visitGreaterThanCondition(HmlParser::GreaterThanConditionContext *context) = 0;

    virtual std::any visitGreaterEqualCondition(HmlParser::GreaterEqualConditionContext *context) = 0;

    virtual std::any visitVariableCondition(HmlParser::VariableConditionContext *context) = 0;

    virtual std::any visitParenCondition(HmlParser::ParenConditionContext *context) = 0;

    virtual std::any visitLessThanCondition(HmlParser::LessThanConditionContext *context) = 0;

    virtual std::any visitLessEqualCondition(HmlParser::LessEqualConditionContext *context) = 0;

    virtual std::any visitInequalityCondition(HmlParser::InequalityConditionContext *context) = 0;

    virtual std::any visitOrCondition(HmlParser::OrConditionContext *context) = 0;

    virtual std::any visitAndCondition(HmlParser::AndConditionContext *context) = 0;

    virtual std::any visitProperty(HmlParser::PropertyContext *context) = 0;

    virtual std::any visitPropertyName(HmlParser::PropertyNameContext *context) = 0;

    virtual std::any visitEventHandler(HmlParser::EventHandlerContext *context) = 0;

    virtual std::any visitStringValue(HmlParser::StringValueContext *context) = 0;

    virtual std::any visitNumberValue(HmlParser::NumberValueContext *context) = 0;

    virtual std::any visitColorValue(HmlParser::ColorValueContext *context) = 0;

    virtual std::any visitBooleanValue(HmlParser::BooleanValueContext *context) = 0;

    virtual std::any visitScriptValue(HmlParser::ScriptValueContext *context) = 0;

    virtual std::any visitFunctionValue(HmlParser::FunctionValueContext *context) = 0;

    virtual std::any visitIdentifierValue(HmlParser::IdentifierValueContext *context) = 0;

    virtual std::any visitExpressionValue(HmlParser::ExpressionValueContext *context) = 0;

    virtual std::any visitComplexExpressionValue(HmlParser::ComplexExpressionValueContext *context) = 0;

    virtual std::any visitSubtractExpression(HmlParser::SubtractExpressionContext *context) = 0;

    virtual std::any visitDivideExpression(HmlParser::DivideExpressionContext *context) = 0;

    virtual std::any visitAddExpression(HmlParser::AddExpressionContext *context) = 0;

    virtual std::any visitMultiplyExpression(HmlParser::MultiplyExpressionContext *context) = 0;

    virtual std::any visitParenExpression(HmlParser::ParenExpressionContext *context) = 0;

    virtual std::any visitNumberExpression(HmlParser::NumberExpressionContext *context) = 0;

    virtual std::any visitSimpleExpression(HmlParser::SimpleExpressionContext *context) = 0;

    virtual std::any visitDefaultScriptStatement(HmlParser::DefaultScriptStatementContext *context) = 0;

    virtual std::any visitDeferScriptStatement(HmlParser::DeferScriptStatementContext *context) = 0;

    virtual std::any visitAsyncScriptStatement(HmlParser::AsyncScriptStatementContext *context) = 0;

    virtual std::any visitDefaultInlineScriptStatement(HmlParser::DefaultInlineScriptStatementContext *context) = 0;

    virtual std::any visitDeferInlineScriptStatement(HmlParser::DeferInlineScriptStatementContext *context) = 0;

    virtual std::any visitAsyncInlineScriptStatement(HmlParser::AsyncInlineScriptStatementContext *context) = 0;

    virtual std::any visitFunctionCall(HmlParser::FunctionCallContext *context) = 0;

    virtual std::any visitArgumentList(HmlParser::ArgumentListContext *context) = 0;

    virtual std::any visitElementType(HmlParser::ElementTypeContext *context) = 0;


};

