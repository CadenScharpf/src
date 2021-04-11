#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include "colors.h"
#include <iostream>

typedef struct rule
{
    int lhs;
    std::vector<int> * rhs;
} rule_t;

typedef struct grammar
{
    std::vector<rule_t*> * rules;
    std::vector<std::string> * symbols;
} grammar_t;



//RULE
rule_t * new_rule(int left, std::vector<int> right);

//GRAMMAR
grammar_t * new_grammar();
//Functions for the 'symbols' list
void pushSymbol(std::string symbol, std::vector<std::string> & symbols);
int idxOf(std::string sym, std::vector<std::string> & symbols);
void print_grammar(grammar_t * grammar);