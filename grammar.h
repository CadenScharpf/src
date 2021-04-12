#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <iostream>
#include "colors.h"
#include "sets.h"
//RULE
typedef struct rule
{
    int lhs;
    std::vector<int> * rhs;
} rule_t;
rule_t * new_rule(int left, std::vector<int> right);
void print_rule(rule_t * rule);
void print_rhs(std::vector<int> * rhs);
void print_rules(std::vector<rule_t*> rules);

//GRAMMAR
typedef struct grammar
{
    std::vector<rule_t*> * rules;
    std::vector<std::string> * symbols;
} grammar_t;
grammar_t * new_grammar();
//Functions for the 'symbols' list
void pushSymbol(std::string symbol, std::vector<std::string> & symbols);
int idxOf(std::string sym, std::vector<std::string> & symbols);
void print_grammar(grammar_t * grammar);
void print_symbols(std::vector<std::string> * symbls);
void printTermsAndNonTerms(grammar_t * grammar);//!< print funtion for task 1
std::set<int> getNonTerminals(grammar_t * g);
std::set<int> getTermsAndNonTerms(grammar_t * g);
void printSetWithStr(std::set<int>, grammar_t * g);