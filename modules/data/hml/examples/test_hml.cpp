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

// HML Parser Demo - Demonstrates the HML language features
#include <iostream>
#include <string>
#include <any>
#include <fstream>
#include <filesystem>
#include <set>
#include <map>
#include "antlr4-runtime.h"
#include "HmlLexer.h"
#include "HmlParser.h"
#include "HmlBaseVisitor.h"

using namespace antlr4;

// Simple visitor that just prints what it finds
class SimpleHmlVisitor : public HmlBaseVisitor {
public:
    int indentLevel;
    std::set<std::string> includedFiles;  // Track included files to prevent infinite recursion
    std::string basePath;
    std::map<std::string, std::string> importedComponents;  // Registry of imported components (name -> file content)
    std::set<std::string> expandingComponents;  // Track components currently being expanded to prevent infinite recursion
    std::map<std::string, std::string> variables;  // Registry of declared variables (name -> value)
    std::map<std::string, std::string> variableTypes;  // Registry of variable types (name -> type)
    std::map<std::string, std::vector<std::string>> signals;  // Registry of signals (name -> parameter list)
    std::map<std::string, std::vector<std::string>> eventHandlers;  // Registry of event handlers (event -> handler code)
    std::map<std::string, std::set<std::string>> dependencies;  // Dependency tracking (variable -> dependents)
    int maxExpansionDepth;
    
    SimpleHmlVisitor() : indentLevel(0), basePath(""), maxExpansionDepth(5) {}
    
private:
    
    std::string getIndent() const {
        return std::string(indentLevel * 2, ' ');
    }
    
    std::string resolveFilePath(const std::string& filename) const {
        std::filesystem::path file(filename);
        if (file.is_absolute()) {
            return filename;
        }
        
        // Resolve relative to base path
        std::filesystem::path baseDirPath(basePath);
        if (!basePath.empty() && baseDirPath.has_parent_path()) {
            return (baseDirPath.parent_path() / file).string();
        }
        
        return filename;
    }
    
    bool parseIncludedFile(const std::string& filename) {
        std::string resolvedPath = resolveFilePath(filename);
        
        // Check for infinite recursion
        if (includedFiles.find(resolvedPath) != includedFiles.end()) {
            std::cout << getIndent() << "❌ Error: Circular include detected: " << filename << std::endl;
            return false;
        }
        
        // Check if file exists
        if (!std::filesystem::exists(resolvedPath)) {
            std::cout << getIndent() << "❌ Error: Include file not found: " << resolvedPath << std::endl;
            return false;
        }
        
        // Read the file
        std::ifstream file(resolvedPath);
        if (!file.is_open()) {
            std::cout << getIndent() << "❌ Error: Cannot read file: " << resolvedPath << std::endl;
            return false;
        }
        
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();
        
        // Track this file to prevent recursion
        includedFiles.insert(resolvedPath);
        
        try {
            // Create input stream
            antlr4::ANTLRInputStream input(content);
            
            // Create lexer
            HmlLexer lexer(&input);
            
            // Create token stream
            antlr4::CommonTokenStream tokens(&lexer);
            
            // Create parser
            HmlParser parser(&tokens);
            
            // Parse starting from 'hml' rule
            antlr4::tree::ParseTree* tree = parser.hml();
            
            // Create a new visitor with increased indent and same state
            SimpleHmlVisitor includeVisitor;
            includeVisitor.indentLevel = indentLevel + 1;
            includeVisitor.includedFiles = includedFiles;  // Copy current state
            includeVisitor.basePath = resolvedPath;
            includeVisitor.importedComponents = importedComponents;  // Share component registry
            includeVisitor.expandingComponents = expandingComponents;  // Share expansion tracking
            includeVisitor.variables = variables;  // Share variable registry
            includeVisitor.variableTypes = variableTypes;  // Share type registry
            includeVisitor.signals = signals;  // Share signal registry
            includeVisitor.eventHandlers = eventHandlers;  // Share event handlers
            includeVisitor.dependencies = dependencies;  // Share dependencies
            includeVisitor.maxExpansionDepth = maxExpansionDepth;
            
            std::cout << getIndent() << "📁 Processing included file: " << filename << std::endl;
            includeVisitor.visit(tree);
            
            // Update our state with any new includes from the nested file
            includedFiles = includeVisitor.includedFiles;
            importedComponents = includeVisitor.importedComponents;  // Update component registry
            expandingComponents = includeVisitor.expandingComponents;  // Update expansion tracking
            variables = includeVisitor.variables;  // Update variable registry
            variableTypes = includeVisitor.variableTypes;  // Update type registry
            signals = includeVisitor.signals;  // Update signal registry
            eventHandlers = includeVisitor.eventHandlers;  // Update event handlers
            dependencies = includeVisitor.dependencies;  // Update dependencies
            
        } catch (const std::exception& e) {
            std::cout << getIndent() << "❌ Error parsing included file " << filename << ": " << e.what() << std::endl;
            return false;
        }
        
        return true;
    }
    
    bool parseImportedComponent(const std::string& filename) {
        std::string resolvedPath = resolveFilePath(filename);
        
        // Check for infinite recursion
        if (includedFiles.find(resolvedPath) != includedFiles.end()) {
            std::cout << getIndent() << "❌ Error: Circular import detected: " << filename << std::endl;
            return false;
        }
        
        // Check if file exists
        if (!std::filesystem::exists(resolvedPath)) {
            std::cout << getIndent() << "❌ Error: Import file not found: " << resolvedPath << std::endl;
            return false;
        }
        
        // Read the file
        std::ifstream file(resolvedPath);
        if (!file.is_open()) {
            std::cout << getIndent() << "❌ Error: Cannot read file: " << resolvedPath << std::endl;
            return false;
        }
        
        std::string content((std::istreambuf_iterator<char>(file)),
                           std::istreambuf_iterator<char>());
        file.close();
        
        try {
            // Create input stream
            antlr4::ANTLRInputStream input(content);
            
            // Create lexer
            HmlLexer lexer(&input);
            
            // Create token stream
            antlr4::CommonTokenStream tokens(&lexer);
            
            // Create parser
            HmlParser parser(&tokens);
            
            // Parse starting from 'hml' rule
            antlr4::tree::ParseTree* tree = parser.hml();
            
            // Find the root element in the imported file
            // Assume the first element is the component we want to register
            if (auto hmlCtx = dynamic_cast<HmlParser::HmlContext*>(tree)) {
                for (size_t i = 0; i < hmlCtx->children.size(); i++) {
                    if (auto elementCtx = dynamic_cast<HmlParser::ElementContext*>(hmlCtx->children[i])) {
                        std::string componentName = elementCtx->elementType()->ID()->getText();
                        
                        // Register the component with its content
                        importedComponents[componentName] = content;
                        
                        std::cout << getIndent() << "🔧 Registered component: " << componentName << std::endl;
                        return true;
                    }
                }
            }
            
        } catch (const std::exception& e) {
            std::cout << getIndent() << "❌ Error parsing import file " << filename << ": " << e.what() << std::endl;
            return false;
        }
        
        return false;
    }
    
    antlrcpp::Any visitElement(HmlParser::ElementContext *ctx) override {
        std::string elementType = ctx->elementType()->ID()->getText();
        
        // Check if this is an imported component
        auto componentIt = importedComponents.find(elementType);
        if (componentIt != importedComponents.end()) {
            std::cout << getIndent() << "Found imported component: " << elementType << " 🧩" << std::endl;
            
            // Check for recursion
            if (expandingComponents.find(elementType) != expandingComponents.end()) {
                std::cout << getIndent() << "⚠️  Circular reference detected - " << elementType << " already expanding" << std::endl;
                return nullptr;
            }
            
            // Check expansion depth
            if (indentLevel > maxExpansionDepth) {
                std::cout << getIndent() << "⚠️  Maximum expansion depth reached for " << elementType << std::endl;
                return nullptr;
            }
            
            // Process the current element's properties first (overrides)
            indentLevel++;
            
            // Visit properties of the current element (which can override imported component defaults)
            if (ctx->elementBody()) {
                for (auto child : ctx->elementBody()->children) {
                    if (auto propertyCtx = dynamic_cast<HmlParser::PropertyContext*>(child)) {
                        visit(propertyCtx);
                    }
                }
            }
            
            // Then expand the imported component definition
            std::cout << getIndent() << "📋 Expanding imported component definition:" << std::endl;
            indentLevel++;
            
            // Mark this component as being expanded (temporarily)
            expandingComponents.insert(elementType);
            
            try {
                // Parse the imported component content to get just the root element content
                std::string componentContent = componentIt->second;
                antlr4::ANTLRInputStream input(componentContent);
                HmlLexer lexer(&input);
                antlr4::CommonTokenStream tokens(&lexer);
                HmlParser parser(&tokens);
                
                // Parse the component
                antlr4::tree::ParseTree* componentTree = parser.hml();
                
                // Find the root element and visit its children directly (not the element itself)
                if (auto hmlCtx = dynamic_cast<HmlParser::HmlContext*>(componentTree)) {
                    for (size_t i = 0; i < hmlCtx->children.size(); i++) {
                        if (auto elementCtx = dynamic_cast<HmlParser::ElementContext*>(hmlCtx->children[i])) {
                            // Visit the element's body content directly (properties and children)
                            if (elementCtx->elementBody()) {
                                for (auto child : elementCtx->elementBody()->children) {
                                    visit(child);  // This will visit properties, elements, and includes
                                }
                            }
                            break; // Only process the first element
                        }
                    }
                }
                
            } catch (const std::exception& e) {
                std::cout << getIndent() << "❌ Error expanding component " << elementType << ": " << e.what() << std::endl;
            }
            
            // Remove from expansion tracking
            expandingComponents.erase(elementType);
            
            indentLevel--;
            indentLevel--;
            
        } else {
            std::cout << getIndent() << "Found element: " << elementType << std::endl;
            
            // Increase indent for children
            indentLevel++;
            antlrcpp::Any result = visitChildren(ctx);
            indentLevel--;
            
            return result;
        }
        
        return nullptr;
    }
    
    antlrcpp::Any visitIncludeStatement(HmlParser::IncludeStatementContext *ctx) override {
        std::string filename = ctx->STRING()->getText();
        // Remove quotes from filename
        filename = filename.substr(1, filename.length() - 2);
        
        std::cout << getIndent() << "📂 Include: " << filename << std::endl;
        
        // Parse the included file
        parseIncludedFile(filename);
        
        return nullptr;
    }
    
    antlrcpp::Any visitImportStatement(HmlParser::ImportStatementContext *ctx) override {
        std::string filename = ctx->STRING()->getText();
        // Remove quotes from filename
        filename = filename.substr(1, filename.length() - 2);
        
        std::cout << getIndent() << "📦 Import: " << filename << std::endl;
        
        // Load and register the component
        if (parseImportedComponent(filename)) {
            std::cout << getIndent() << "✅ Component registered successfully" << std::endl;
        }
        
        return nullptr;
    }
    
    antlrcpp::Any visitVariableDeclaration(HmlParser::VariableDeclarationContext *ctx) override {
        std::string varName = ctx->ID()->getText();
        std::string varType = "any";  // Default type
        
        // Check if type annotation exists
        if (ctx->typeAnnotation()) {
            varType = ctx->typeAnnotation()->getText();
        }
        
        antlrcpp::Any result = visit(ctx->propertyValue());
        std::string varValue = std::any_cast<std::string>(result);
        
        // Store the variable and its type in registries
        variables[varName] = varValue;
        variableTypes[varName] = varType;
        
        std::cout << getIndent() << "🔧 Variable: " << varName << ": " << varType << " = " << varValue << std::endl;
        
        return nullptr;
    }
    
    antlrcpp::Any visitSignalDeclaration(HmlParser::SignalDeclarationContext *ctx) override {
        std::string signalName = ctx->ID()->getText();
        std::vector<std::string> parameters;
        
        // Collect parameters if they exist
        if (ctx->parameterList()) {
            for (auto paramCtx : ctx->parameterList()->parameter()) {
                std::string paramName = paramCtx->ID()->getText();
                std::string paramType = paramCtx->typeAnnotation()->getText();
                parameters.push_back(paramName + ":" + paramType);
            }
        }
        
        // Store the signal in the registry
        signals[signalName] = parameters;
        
        std::cout << getIndent() << "📡 Signal: " << signalName << "(";
        for (size_t i = 0; i < parameters.size(); i++) {
            std::cout << parameters[i];
            if (i < parameters.size() - 1) std::cout << ", ";
        }
        std::cout << ")" << std::endl;
        
        return nullptr;
    }
    
    bool evaluateCondition(HmlParser::ConditionalExpressionContext *ctx) {
        if (auto boolCtx = dynamic_cast<HmlParser::BooleanConditionContext*>(ctx)) {
            return boolCtx->BOOLEAN()->getText() == "true";
        }
        
        if (auto varCtx = dynamic_cast<HmlParser::VariableConditionContext*>(ctx)) {
            std::string varName = varCtx->ID()->getText();
            auto varIt = variables.find(varName);
            if (varIt != variables.end()) {
                return varIt->second == "true" || varIt->second != "0" && varIt->second != "false";
            }
            return false;
        }
        
        if (auto eqCtx = dynamic_cast<HmlParser::EqualityConditionContext*>(ctx)) {
            std::string varName = eqCtx->ID()->getText();
            auto varIt = variables.find(varName);
            if (varIt != variables.end()) {
                antlrcpp::Any result = visit(eqCtx->propertyValue());
                std::string compareValue = std::any_cast<std::string>(result);
                return varIt->second == compareValue;
            }
            return false;
        }
        
        if (auto neCtx = dynamic_cast<HmlParser::InequalityConditionContext*>(ctx)) {
            std::string varName = neCtx->ID()->getText();
            auto varIt = variables.find(varName);
            if (varIt != variables.end()) {
                antlrcpp::Any result = visit(neCtx->propertyValue());
                std::string compareValue = std::any_cast<std::string>(result);
                return varIt->second != compareValue;
            }
            return true;
        }
        
        if (auto gtCtx = dynamic_cast<HmlParser::GreaterThanConditionContext*>(ctx)) {
            std::string varName = gtCtx->ID()->getText();
            auto varIt = variables.find(varName);
            if (varIt != variables.end()) {
                try {
                    int varValue = std::stoi(varIt->second);
                    int compareValue = std::stoi(gtCtx->NUMBER()->getText());
                    return varValue > compareValue;
                } catch (...) {
                    return false;
                }
            }
            return false;
        }
        
        if (auto andCtx = dynamic_cast<HmlParser::AndConditionContext*>(ctx)) {
            auto leftChild = andCtx->conditionalExpression(0);
            auto rightChild = andCtx->conditionalExpression(1);
            return evaluateCondition(leftChild) && evaluateCondition(rightChild);
        }
        
        if (auto orCtx = dynamic_cast<HmlParser::OrConditionContext*>(ctx)) {
            auto leftChild = orCtx->conditionalExpression(0);
            auto rightChild = orCtx->conditionalExpression(1);
            return evaluateCondition(leftChild) || evaluateCondition(rightChild);
        }
        
        if (auto notCtx = dynamic_cast<HmlParser::NotConditionContext*>(ctx)) {
            return !evaluateCondition(notCtx->conditionalExpression());
        }
        
        if (auto parenCtx = dynamic_cast<HmlParser::ParenConditionContext*>(ctx)) {
            return evaluateCondition(parenCtx->conditionalExpression());
        }
        
        return false;
    }
    
    antlrcpp::Any visitConditionalStatement(HmlParser::ConditionalStatementContext *ctx) override {
        bool condition = evaluateCondition(ctx->conditionalExpression());
        
        std::cout << getIndent() << "🔀 Conditional: " << (condition ? "TRUE" : "FALSE") << std::endl;
        
        indentLevel++;
        
        if (condition) {
            // Execute the if block
            std::cout << getIndent() << "✅ Executing IF block:" << std::endl;
            indentLevel++;
            for (auto child : ctx->elementBody(0)->children) {
                visit(child);
            }
            indentLevel--;
        } else if (ctx->elementBody().size() > 1) {
            // Execute the else block if it exists
            std::cout << getIndent() << "🔄 Executing ELSE block:" << std::endl;
            indentLevel++;
            for (auto child : ctx->elementBody(1)->children) {
                visit(child);
            }
            indentLevel--;
        }
        
        indentLevel--;
        return nullptr;
    }
    
    antlrcpp::Any visitProperty(HmlParser::PropertyContext *ctx) override {
        if (ctx->propertyName()) {
            // Regular property
            std::string propName = ctx->propertyName()->ID()->getText();
            antlrcpp::Any result = visit(ctx->propertyValue());
            std::string propValue = std::any_cast<std::string>(result);
            
            std::cout << getIndent() << "Property: " << propName << " = " << propValue << std::endl;
        } else if (ctx->eventHandler()) {
            // Event handler property
            std::string eventName = ctx->eventHandler()->ID()->getText();
            antlrcpp::Any result = visit(ctx->propertyValue());
            std::string handlerCode = std::any_cast<std::string>(result);
            
            // Store event handler
            eventHandlers[eventName].push_back(handlerCode);
            
            std::cout << getIndent() << "🎯 Event Handler: on" << eventName << " = " << handlerCode << std::endl;
        }
        
        return nullptr;
    }
    
    antlrcpp::Any visitStringValue(HmlParser::StringValueContext *ctx) override {
        std::string value = ctx->STRING()->getText();
        return value;
    }
    
    antlrcpp::Any visitScriptValue(HmlParser::ScriptValueContext *ctx) override {
        std::string scriptContent = ctx->SCRIPT_CONTENT()->getText();
        // Remove backticks and show as script
        std::string cleanScript = scriptContent.substr(1, scriptContent.length() - 2);
        return "📜 Inline Script: " + cleanScript;
    }
    
    
    antlrcpp::Any visitDefaultScriptStatement(HmlParser::DefaultScriptStatementContext *ctx) override {
        std::string filename = ctx->STRING()->getText();
        // Remove quotes
        filename = filename.substr(1, filename.length() - 2);
        std::cout << getIndent() << "📜 Script (blocking): " << filename << std::endl;
        return nullptr;
    }
    
    antlrcpp::Any visitDeferScriptStatement(HmlParser::DeferScriptStatementContext *ctx) override {
        std::string filename = ctx->STRING()->getText();
        // Remove quotes
        filename = filename.substr(1, filename.length() - 2);
        std::cout << getIndent() << "⏳ Script (defer): " << filename << std::endl;
        return nullptr;
    }
    
    antlrcpp::Any visitAsyncScriptStatement(HmlParser::AsyncScriptStatementContext *ctx) override {
        std::string filename = ctx->STRING()->getText();
        // Remove quotes
        filename = filename.substr(1, filename.length() - 2);
        std::cout << getIndent() << "🚀 Script (async): " << filename << std::endl;
        return nullptr;
    }
    
    antlrcpp::Any visitDefaultInlineScriptStatement(HmlParser::DefaultInlineScriptStatementContext *ctx) override {
        std::string scriptCode = ctx->SCRIPT_CONTENT()->getText();
        // Remove backticks from inline script
        std::string cleanScript = scriptCode.substr(1, scriptCode.length() - 2);
        std::cout << getIndent() << "📜 Inline Script (blocking): " << cleanScript << std::endl;
        return nullptr;
    }
    
    antlrcpp::Any visitDeferInlineScriptStatement(HmlParser::DeferInlineScriptStatementContext *ctx) override {
        std::string scriptCode = ctx->SCRIPT_CONTENT()->getText();
        // Remove backticks from inline script
        std::string cleanScript = scriptCode.substr(1, scriptCode.length() - 2);
        std::cout << getIndent() << "⏳ Inline Script (defer): " << cleanScript << std::endl;
        return nullptr;
    }
    
    antlrcpp::Any visitAsyncInlineScriptStatement(HmlParser::AsyncInlineScriptStatementContext *ctx) override {
        std::string scriptCode = ctx->SCRIPT_CONTENT()->getText();
        // Remove backticks from inline script  
        std::string cleanScript = scriptCode.substr(1, scriptCode.length() - 2);
        std::cout << getIndent() << "🚀 Inline Script (async): " << cleanScript << std::endl;
        return nullptr;
    }
    
    antlrcpp::Any visitNumberValue(HmlParser::NumberValueContext *ctx) override {
        return ctx->NUMBER()->getText();
    }
    
    antlrcpp::Any visitColorValue(HmlParser::ColorValueContext *ctx) override {
        return ctx->COLOR()->getText();
    }
    
    antlrcpp::Any visitBooleanValue(HmlParser::BooleanValueContext *ctx) override {
        return ctx->BOOLEAN()->getText();
    }
    
    antlrcpp::Any visitIdentifierValue(HmlParser::IdentifierValueContext *ctx) override {
        return ctx->ID()->getText();
    }
    
    antlrcpp::Any visitFunctionValue(HmlParser::FunctionValueContext *ctx) override {
        std::string funcName = ctx->functionCall()->ID()->getText();
        return funcName + "()";
    }
    
    antlrcpp::Any visitExpressionValue(HmlParser::ExpressionValueContext *ctx) override {
        std::string expression = ctx->EXPRESSION()->getText();
        // Extract variable name from ${varName} - remove ${ and }
        std::string varName = expression.substr(2, expression.length() - 3);
        
        // Look up the variable value
        auto varIt = variables.find(varName);
        if (varIt != variables.end()) {
            return "📋 Expression: " + expression + " → " + varIt->second;
        } else {
            return "❌ Undefined variable: " + varName;
        }
    }
    
    antlrcpp::Any visitComplexExpressionValue(HmlParser::ComplexExpressionValueContext *ctx) override {
        antlrcpp::Any result = visit(ctx->complexExpression());
        std::string value = std::any_cast<std::string>(result);
        return "🧮 Complex Expression: " + value;
    }
    
    antlrcpp::Any visitAddExpression(HmlParser::AddExpressionContext *ctx) override {
        antlrcpp::Any left = visit(ctx->complexExpression(0));
        antlrcpp::Any right = visit(ctx->complexExpression(1));
        
        std::string leftStr = std::any_cast<std::string>(left);
        std::string rightStr = std::any_cast<std::string>(right);
        
        // Try to evaluate as numbers if possible
        try {
            double leftNum = std::stod(leftStr);
            double rightNum = std::stod(rightStr);
            double result = leftNum + rightNum;
            return std::to_string(result);
        } catch (...) {
            return leftStr + " + " + rightStr;
        }
    }
    
    antlrcpp::Any visitSubtractExpression(HmlParser::SubtractExpressionContext *ctx) override {
        antlrcpp::Any left = visit(ctx->complexExpression(0));
        antlrcpp::Any right = visit(ctx->complexExpression(1));
        
        std::string leftStr = std::any_cast<std::string>(left);
        std::string rightStr = std::any_cast<std::string>(right);
        
        try {
            double leftNum = std::stod(leftStr);
            double rightNum = std::stod(rightStr);
            double result = leftNum - rightNum;
            return std::to_string(result);
        } catch (...) {
            return leftStr + " - " + rightStr;
        }
    }
    
    antlrcpp::Any visitMultiplyExpression(HmlParser::MultiplyExpressionContext *ctx) override {
        antlrcpp::Any left = visit(ctx->complexExpression(0));
        antlrcpp::Any right = visit(ctx->complexExpression(1));
        
        std::string leftStr = std::any_cast<std::string>(left);
        std::string rightStr = std::any_cast<std::string>(right);
        
        try {
            double leftNum = std::stod(leftStr);
            double rightNum = std::stod(rightStr);
            double result = leftNum * rightNum;
            return std::to_string(result);
        } catch (...) {
            return leftStr + " * " + rightStr;
        }
    }
    
    antlrcpp::Any visitDivideExpression(HmlParser::DivideExpressionContext *ctx) override {
        antlrcpp::Any left = visit(ctx->complexExpression(0));
        antlrcpp::Any right = visit(ctx->complexExpression(1));
        
        std::string leftStr = std::any_cast<std::string>(left);
        std::string rightStr = std::any_cast<std::string>(right);
        
        try {
            double leftNum = std::stod(leftStr);
            double rightNum = std::stod(rightStr);
            if (rightNum != 0) {
                double result = leftNum / rightNum;
                return std::to_string(result);
            } else {
                return "Division by zero";
            }
        } catch (...) {
            return leftStr + " / " + rightStr;
        }
    }
    
    antlrcpp::Any visitSimpleExpression(HmlParser::SimpleExpressionContext *ctx) override {
        std::string expression = ctx->EXPRESSION()->getText();
        // Extract variable name from ${varName} - remove ${ and }
        std::string varName = expression.substr(2, expression.length() - 3);
        
        // Look up the variable value
        auto varIt = variables.find(varName);
        if (varIt != variables.end()) {
            return varIt->second;
        } else {
            return "0";  // Default for undefined variables in expressions
        }
    }
    
    antlrcpp::Any visitNumberExpression(HmlParser::NumberExpressionContext *ctx) override {
        return ctx->NUMBER()->getText();
    }
    
    antlrcpp::Any visitParenExpression(HmlParser::ParenExpressionContext *ctx) override {
        return visit(ctx->complexExpression());
    }
};

int main() {
    // First create some test include files
    std::cout << "🚀 Creating test include files..." << std::endl;
    
    // Create a toolbar.hml include file
    std::string toolbarHml = R"(HToolbar {
    height: 40
    background: "#1a202c"
    
    HButton {
        text: "Save"
        width: 80
        height: 30
        icon: "save.png"
    }
    
    HButton {
        text: "Load"
        width: 80
        height: 30
        icon: "load.png"
    }
})";
    
    std::ofstream toolbarFile("toolbar.hml");
    toolbarFile << toolbarHml;
    toolbarFile.close();
    
    // Create a status.hml include file  
    std::string statusHml = R"(HStatusBar {
    height: 25
    background: "#2d3748"
    
    HLabel {
        text: "Ready"
        color: "#e2e8f0"
    }
})";
    
    std::ofstream statusFile("status.hml");
    statusFile << statusHml;
    statusFile.close();
    
    // Main HML test code with imports, includes, comments, scripts and variables  
    std::string hmlCode = R"(
        // Import custom components
        import "MyButton.hml"
        import "HeaderBar.hml"
        
        // Variable declarations with types
        var appTitle: string = "Enhanced HML Primitives Demo"
        var primaryColor: string = "#3182ce"
        var buttonWidth: int = 150
        var spacing: int = 10
        var showAdvanced: bool = true
        var userLevel: int = 5
        var aspectRatio: any = 0.75
        
        /* 
         * Main application window
         * Demonstrates enhanced primitives: signals, events, types
         */
        Window {
            // Signal declarations for the window
            signal windowResized(newWidth: int, newHeight: int)
            signal themeChanged(themeName: string)
            
            // Properties with variable substitution
            title: ${appTitle}
            width: 800
            height: 600
            background: "#2d3748"
            
            // Event handlers
            onWindowResized: `console.log("Window resized");`
            onThemeChanged: `this.applyTheme();`
            
            // App initialization script (inline) - updated to standalone syntax
            script `
                function initializeApp() {
                    console.log('App starting...');
                    this.loadTheme();
                    this.setupEventHandlers();
                }
                
                function loadTheme() {
                    // Theme loading logic
                    document.body.className = 'dark-theme';
                }
            `
            
            // Standalone script statements (files and inline!)
            script defer "init.lua"        // Deferred initialization from file
            script async "telemetry.lua"  // Async telemetry from file
            
            // Inline script examples using backticks
            script `
                console.log('Immediate initialization');
                window.appReady = true;
            `
            
            script defer `
                // Deferred inline script
                setTimeout(() => {
                    console.log('Deferred setup complete');
                    this.finishLoading();
                }, 100);
            `
            
            script async `
                // Async inline script  
                fetch('/api/stats').then(data => {
                    this.updateStats(data);
                });
            `
            
            // Enhanced HMouseArea primitive with signals and events
            HMouseArea {
                signal customClick(x: int, y: int)
                
                width: 800
                height: 50
                
                onCustomClick: `console.log("Custom click");`
                onClick: `this.handleRegularClick();`
            }
            
            // Enhanced HShape primitive
            HShape {
                signal shapeChanged(newWidth: int, newHeight: int)
                
                width: ${buttonWidth}
                height: 85
                background: ${primaryColor}
                borderRadius: 5
                
                onShapeChanged: `console.log("Shape changed");`
            }
            
            // Enhanced HText primitive with signals
            HText {
                signal textUpdated(newText: string)
                
                text: "Enhanced HText Demo"
                fontSize: 18
                color: "#ffffff"
                
                onTextUpdated: `console.log("Text updated");`
            }
            
            // Enhanced HImage primitive
            HImage {
                signal imageLoaded()
                
                source: "demo.jpg"
                width: ${buttonWidth}
                height: 100
                
                onImageLoaded: `console.log("Image loaded");`
            }
            
            // Custom header with navigation (keeping existing)
            HeaderBar {
                text: "Enhanced Header"
                background: ${primaryColor}
            }
            
            // Include toolbar inline
            include "toolbar.hml"
            
            // Enhanced HLayout primitive with signals
            HLayout {
                signal layoutChanged()
                
                direction: "column"
                spacing: ${spacing}
                width: 800
                height: 450
                
                onLayoutChanged: `console.log("Layout changed");`
                
                // Enhanced HCanvas primitive with signals
                HCanvas {
                    signal canvasPainted()
                    
                    width: 200
                    height: 150
                    contextType: "2d"
                    
                    onCanvasPainted: `console.log("Canvas painted");`
                }
                
                // Custom button component with enhanced properties
                MyButton {
                    signal buttonPressed()
                    
                    text: "Enhanced Button"
                    width: ${buttonWidth}
                    height: 50
                    
                    onButtonPressed: `console.log("Button pressed");`
                }
                
                // Regular button with event handlers
                HButton {
                    text: "Multi-Event Button"
                    width: 120
                    height: 40
                    background: ${primaryColor}
                    
                    onClick: buttonClicked()
                    onDoubleClick: `this.handleDoubleClick();`
                }
                
                // Conditional UI based on user preferences
                if (showAdvanced == true) {
                    // Advanced controls only shown when enabled
                    HLabel {
                        text: "Advanced Settings"
                        fontSize: 16
                        color: "#ffffff"
                    }
                    
                    HSlider {
                        min: 0
                        max: 100
                        value: 75
                        label: "Quality"
                    }
                    
                    HCheckbox {
                        text: "Enable Debug Mode"
                        checked: false
                    }
                } else {
                    // Simple controls for basic users
                    HLabel {
                        text: "Basic Settings"
                        color: "#cccccc"
                    }
                }
                
                // Conditional user level features
                if (userLevel > 3) {
                    HButton {
                        text: "Expert Mode"
                        background: "#dc2626"
                        width: 120
                    }
                    
                    if (userLevel >= 5) {
                        HButton {
                            text: "Developer Tools"
                            background: "#7c3aed"
                            width: 140
                        }
                    }
                }
                
                // Basic slider always visible
                HSlider {
                    min: 0
                    max: 100
                    value: 50
                }
            }
            
            // Include status bar inline
            include "status.hml"
        }
    )";
    
    std::cout << "🚀 Testing HML Parser with Imports and Includes..." << std::endl;
    std::cout << "HML Code to parse:" << std::endl;
    std::cout << hmlCode << std::endl;
    std::cout << "------------------------" << std::endl;
    
    try {
        // Create input stream
        ANTLRInputStream input(hmlCode);
        
        // Create lexer
        HmlLexer lexer(&input);
        
        // Create token stream
        CommonTokenStream tokens(&lexer);
        
        // Create parser
        HmlParser parser(&tokens);
        
        // Parse starting from 'hml' rule
        tree::ParseTree* tree = parser.hml();
        
        // Create visitor and visit the tree
        SimpleHmlVisitor visitor;
        visitor.basePath = std::filesystem::current_path().string() + "/main.hml";  // Set base path for relative includes
        visitor.visit(tree);
        
        std::cout << "------------------------" << std::endl;
        std::cout << "✅ HML parsing successful!" << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << std::endl;
        return 1;
    }
    
    return 0;
}