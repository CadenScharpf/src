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


void syntaxErr()
{
    std::cout << RED << "Syntax Error !!!" << RESET << std::endl;
    exit(0);
}

void expect(TokenType expected, Token nxt)
{
    if(nxt.token_type == expected){return;}
    else{syntaxErr();};
}

grammar_t * parseGrammar(LexicalAnalyzer &lexer)
{
    std::cout << "pg" << std::endl;
    grammar_t * grammar = new_grammar();
    parseRuleList(lexer, grammar);
    expect(HASH, lexer.peek(1));
    return grammar;
};

void parseRuleList(LexicalAnalyzer &lexer, grammar_t * grammar)
{
    std::cout << "prl" << std::endl;
    parseRule(lexer, grammar);
    if(lexer.peek(1).token_type == HASH){return;}
    else if(lexer.peek(1).token_type == ID){parseRuleList(lexer, grammar);}
    else{syntaxErr();};
};

void parseRule(LexicalAnalyzer &lexer, grammar_t * grammar)
{
    std::cout << "pr" << std::endl;
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

std::vector<int> parseRHS(LexicalAnalyzer &lexer, grammar_t * grammar)
{
    std::cout << "prhs" << std::endl;
    std::vector<int> right;
    if(lexer.peek(1).token_type == STAR){lexer.GetToken(); return right;}
    else if(lexer.peek(1).token_type == ID){parseIDList(lexer, grammar, right);}
    expect(STAR, lexer.peek(1));
    lexer.GetToken();
    return right;
}

void parseIDList(LexicalAnalyzer &lexer, grammar_t * grammar, std::vector<int> &idlist)
{
    std::cout << "pidl" << std::endl;
    expect(ID, lexer.peek(1));
    Token t = lexer.GetToken();
    pushSymbol(t.lexeme, *(grammar->symbols));
    idlist.push_back(idxOf(t.lexeme, *(grammar->symbols)));

    if(lexer.peek(1).token_type == ID){parseIDList(lexer, grammar, idlist);}
    else if(lexer.peek(1).token_type == STAR){return;}
    else{syntaxErr();}
}
