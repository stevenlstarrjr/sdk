/*
 * Copyright 2024 HML Project Contributors
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

grammar Hml;

// Top level rule - entry point for parsing HML
hml         : importStatement* variableDeclaration* (includeStatement | element)+ EOF ;

// Element rule - matches widget definitions like "HButton { ... }"
element     : elementType '{' elementBody '}' 
            | elementType '{' '}'
            ;

// Element body contains properties, child elements, includes, script statements, variables, conditionals, and signals (at least one item)
elementBody : (property | element | includeStatement | scriptStatement | variableDeclaration | conditionalStatement | signalDeclaration)+ ;

// Include statement rule - matches "include "filename.hml""
includeStatement : INCLUDE STRING ;

// Import statement rule - matches "import "filename.hml""
importStatement : IMPORT STRING ;

// Variable declaration rule - matches "var name: type = value" or "var name: value"
variableDeclaration : VAR ID ':' typeAnnotation '=' propertyValue
                    | VAR ID ':' propertyValue
                    ;

// Signal declaration rule - matches "signal eventName(param: type, ...)"
signalDeclaration : SIGNAL ID '(' parameterList? ')' ;

// Type annotations for variables and parameters
typeAnnotation : 'int' | 'string' | 'bool' | 'any' ;

// Parameter list for signals
parameterList : parameter (',' parameter)* ;
parameter : ID ':' typeAnnotation ;

// Conditional statement rule - matches "if (condition) { ... } else { ... }"
conditionalStatement : IF '(' conditionalExpression ')' '{' elementBody '}' (ELSE '{' elementBody '}')? ;

// Conditional expressions for boolean evaluation
conditionalExpression
    : ID '==' propertyValue              # EqualityCondition
    | ID '!=' propertyValue              # InequalityCondition  
    | ID '>' NUMBER                      # GreaterThanCondition
    | ID '<' NUMBER                      # LessThanCondition
    | ID '>=' NUMBER                     # GreaterEqualCondition
    | ID '<=' NUMBER                     # LessEqualCondition
    | BOOLEAN                            # BooleanCondition
    | ID                                 # VariableCondition
    | conditionalExpression '&&' conditionalExpression  # AndCondition
    | conditionalExpression '||' conditionalExpression  # OrCondition
    | '!' conditionalExpression          # NotCondition
    | '(' conditionalExpression ')'      # ParenCondition
    ;

// Property rule - matches "propertyName: value" or "onEventName: handler"
property    : propertyName ':' propertyValue 
            | eventHandler ':' propertyValue
            ;

// Property name is just an identifier
propertyName : ID ;

// Event handler name - matches "onEventName"
eventHandler : 'on' ID ;

// Property values can be different types
propertyValue 
    : STRING                    # StringValue
    | NUMBER                    # NumberValue  
    | COLOR                     # ColorValue
    | BOOLEAN                   # BooleanValue
    | SCRIPT_CONTENT            # ScriptValue
    | functionCall              # FunctionValue
    | ID                        # IdentifierValue
    | EXPRESSION                # ExpressionValue
    | complexExpression         # ComplexExpressionValue
    ;

// Complex expressions for property binding - supports math operations
complexExpression
    : EXPRESSION                                    # SimpleExpression
    | complexExpression '+' complexExpression       # AddExpression
    | complexExpression '-' complexExpression       # SubtractExpression  
    | complexExpression '*' complexExpression       # MultiplyExpression
    | complexExpression '/' complexExpression       # DivideExpression
    | '(' complexExpression ')'                     # ParenExpression
    | NUMBER                                        # NumberExpression
    ;

// Script statements for external files and inline code with timing control
scriptStatement 
    : SCRIPT STRING                     # DefaultScriptStatement
    | SCRIPT DEFER STRING               # DeferScriptStatement  
    | SCRIPT ASYNC STRING               # AsyncScriptStatement
    | SCRIPT SCRIPT_CONTENT             # DefaultInlineScriptStatement
    | SCRIPT DEFER SCRIPT_CONTENT       # DeferInlineScriptStatement
    | SCRIPT ASYNC SCRIPT_CONTENT       # AsyncInlineScriptStatement
    ;

// Function calls like "onClick()" or "setVolume(value)"
functionCall : ID '(' argumentList? ')' ;

// Function arguments
argumentList : propertyValue (',' propertyValue)* ;

// Element type is the widget name
elementType : ID ;

// LEXER RULES (Token definitions)

// Include and import keywords - must come before ID
INCLUDE     : 'include' ;
IMPORT      : 'import' ;

// Script timing keywords
SCRIPT      : 'script' ;
DEFER       : 'defer' ;
ASYNC       : 'async' ;

// Variable keyword
VAR         : 'var' ;

// Signal keyword
SIGNAL      : 'signal' ;

// Conditional keywords
IF          : 'if' ;
ELSE        : 'else' ;

// Comparison operators
EQ          : '==' ;
NE          : '!=' ;
GT          : '>' ;
LT          : '<' ;
GE          : '>=' ;
LE          : '<=' ;
AND         : '&&' ;
OR          : '||' ;
NOT         : '!' ;

// Identifiers - widget names, property names, function names
ID          : [a-zA-Z][a-zA-Z0-9_]* ;

// String literals in quotes
STRING      : '"' (~["\\\r\n] | EscapeSequence)* '"' ;

// Script content in backticks (like JavaScript template literals)
SCRIPT_CONTENT : '`' (~[`\\] | EscapeSequence)* '`' ;

// Expression substitution like ${varName}
EXPRESSION  : '${' [a-zA-Z][a-zA-Z0-9_]* '}' ;

// Numbers - integers and decimals, positive and negative
NUMBER      : '-'? [0-9]+ ('.' [0-9]+)? ;

// Hex colors like #ff0000 or #3b82f6
COLOR       : '#' [0-9a-fA-F]+ ;

// Boolean values
BOOLEAN     : 'true' | 'false' ;

// String escape sequences
fragment
EscapeSequence
    : '\\' [btnfr"'\\]
    | '\\' ([0-3]? [0-7])? [0-7]
    | '\\' 'u'+ HexDigit HexDigit HexDigit HexDigit
    ;

fragment
HexDigit : [0-9a-fA-F] ;

// Skip whitespace and comments
WS          : [ \t\r\n]+ -> skip ;

// Single line comments
LINE_COMMENT : '//' ~[\r\n]* -> skip ;

// Multi-line comments  
BLOCK_COMMENT : '/*' .*? '*/' -> skip ;

// Punctuation tokens
LBRACE      : '{' ;
RBRACE      : '}' ;
LPAREN      : '(' ;
RPAREN      : ')' ;
COLON       : ':' ;
COMMA       : ',' ;
SEMICOLON   : ';' ;
