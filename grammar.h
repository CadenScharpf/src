#pragma once
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <iostream>
#include <iterator>
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
void deleteRule(rule_t * r);

//GRAMMAR
typedef struct grammar
{
    std::vector<rule_t*> * rules;
    std::vector<std::string> * symbols;
} grammar_t;
grammar_t * new_grammar();
std::set<int> getNonTerminals(grammar_t * g);
std::set<int> getTermsAndNonTerms(grammar_t * g);
std::set<int> getTerminals(grammar_t * g);
void printSetWithStr(std::set<int> s, grammar_t * g);
void printSetWithStrAndComma(std::set<int> s, grammar_t * g);
std::vector<std::set<int>> calcFirstSets(grammar_t * g);
std::vector<std::set<int>> calcFollowSets(grammar_t * g);
void printFirstSets(std::vector<std::set<int>> s, grammar_t * g);
void printFullFirstSets(std::vector<std::set<int>> s, grammar_t * g);//!< for submission
void deleteGrammar(grammar_t * g);

//Functions for the 'symbols' list
void pushSymbol(std::string symbol, std::vector<std::string> & symbols);
int idxOf(std::string sym, std::vector<std::string> & symbols);
void print_grammar(grammar_t * grammar);
void print_symbols(std::vector<std::string> * symbls);
void printTermsAndNonTerms(grammar_t * grammar);//!< print funtion for task 1

//FIRST/FOLLOW SETS
typedef std::set<int> set_t;
typedef std::vector<std::set<int>> setlist_t;
typedef std::vector<rule_t*> rulelist_t;
typedef std::vector<std::string> symbollist_t;