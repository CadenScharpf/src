#pragma once

#include <iostream>
#include "grammar.h"
#include "lexer.h"
#include "colors.h"

void parseIDList(LexicalAnalyzer &lexer, grammar_t * grammar, std::vector<int> &idlist);
std::vector<int> parseRHS(LexicalAnalyzer &lexer, grammar_t * grammar);
void parseRule(LexicalAnalyzer &lexer, grammar_t * grammar);
void parseRuleList(LexicalAnalyzer &lexer, grammar_t * grammar);
grammar_t * parseGrammar(LexicalAnalyzer &lexer);

/**
 * @brief outputs the syntax err msg to std out and exits program
 * 
 */
void syntaxErr()
{
    std::cout << "SYNTAX ERROR !!!" << std::endl;
    exit(0);
}

/**
 * @brief Throws a syntax error if nxt is not of type expected
 * 
 * @param expected 
 * @param nxt 
 */
void expect(TokenType expected, Token nxt)
{
    if(nxt.token_type == expected){return;}
    else{syntaxErr();};
}

/**
 * @brief 
 * 
 * @param lexer 
 * @return grammar_t* 
 */
grammar_t * parseGrammar(LexicalAnalyzer &lexer)
{
    grammar_t * grammar = new_grammar();
    parseRuleList(lexer, grammar);
    expect(HASH, lexer.peek(1));
    return grammar;
};
/**
 * @brief 
 * 
 * @param lexer 
 * @param grammar 
 */
void parseRuleList(LexicalAnalyzer &lexer, grammar_t * grammar)
{
    parseRule(lexer, grammar);
    if(lexer.peek(1).token_type == HASH){return;}
    else if(lexer.peek(1).token_type == ID){parseRuleList(lexer, grammar);}
    else{syntaxErr();};
};

/**
 * @brief 
 * 
 * @param lexer 
 * @param grammar 
 */
void parseRule(LexicalAnalyzer &lexer, grammar_t * grammar)
{
    expect(ID, lexer.peek(1));
    Token nt = lexer.GetToken();
    pushSymbol(nt.lexeme, *(grammar->symbols));
    expect(ARROW, lexer.GetToken());
    std::vector<int> rightSide = parseRHS(lexer, grammar);
    (grammar->rules)->push_back( new_rule(idxOf(nt.lexeme, *(grammar->symbols)), rightSide));

    if(lexer.peek(1).token_type == HASH){return;}
    else if(lexer.peek(1).token_type == ID){parseRule(lexer, grammar);}
    else{syntaxErr();};
}

/**
 * @brief 
 * 
 * @param lexer 
 * @param grammar 
 * @return std::vector<int> 
 */
std::vector<int> parseRHS(LexicalAnalyzer &lexer, grammar_t * grammar)
{
    std::vector<int> right;
    if(lexer.peek(1).token_type == STAR){lexer.GetToken();right.push_back(0); return right;}
    else if(lexer.peek(1).token_type == ID){parseIDList(lexer, grammar, right);}
    expect(STAR, lexer.peek(1));
    lexer.GetToken();
    return right;
}

/**
 * @brief 
 * 
 * @param lexer 
 * @param grammar 
 * @param idlist 
 */
void parseIDList(LexicalAnalyzer &lexer, grammar_t * grammar, std::vector<int> &idlist)
{
    expect(ID, lexer.peek(1));
    Token t = lexer.GetToken();
    pushSymbol(t.lexeme, *(grammar->symbols));
    idlist.push_back(idxOf(t.lexeme, *(grammar->symbols)));

    if(lexer.peek(1).token_type == ID){parseIDList(lexer, grammar, idlist);}
    else if(lexer.peek(1).token_type == STAR){return;}
    else{syntaxErr();}
}
