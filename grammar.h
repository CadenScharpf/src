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

typedef std::set<int> set_t;
typedef std::vector<std::set<int>> setlist_t;
typedef std::vector<rule_t*> rulelist_t;
typedef std::vector<std::string> symbollist_t;
rule_t * new_rule(int left, std::vector<int> right);
void deleteRule(rule_t * r);

//GRAMMAR
typedef struct grammar
{
    rulelist_t * rules;
    symbollist_t * symbols;
} grammar_t;

grammar_t * new_grammar();
set_t getNonTerminals(grammar_t * g);
set_t getTermsAndNonTerms(grammar_t * g);
set_t getTerminals(grammar_t * g);

//Functions for set_t/fs setlist_t
void printSetWithStr(set_t s, grammar_t * g);
void printSetWithStrAndComma(std::set<int> s, grammar_t * g);
void printFirstSets(setlist_t s, grammar_t * g);//!< for submission
void printFollowSets(setlist_t s, grammar_t * g);//!< for submission
void printFullFirstSets(setlist_t s, grammar_t * g);
void printFullFollowSets(setlist_t s, grammar_t * g);
void deleteGrammar(grammar_t * g);
void deleteRuleList(grammar_t * g);
setlist_t calcFirstSets(grammar_t * g);
setlist_t calcFollowSets(grammar_t * g, setlist_t first);
set_t removeEpsilon(set_t s, grammar_t * g);

void print_rule(rule_t * rule, grammar_t * g);
void print_rhs(std::vector<int> * rhs, grammar_t * g);

//Functions for symbollist_t
void pushSymbol(std::string symbol, symbollist_t & symbols);
int idxOf(std::string sym, symbollist_t & symbols);
void print_grammar(grammar_t * grammar);
void print_symbols(symbollist_t * symbls);
void printTermsAndNonTerms(grammar_t * grammar);//!< print funtion for task 1

//Functions for calculating/removing generating symbols
std::vector<bool> calculateGeneratingSymbols(grammar_t * g);

void removeRlsWNonGenSyms(grammar_t * g, std::vector<bool> gensym);

//Functions for calculating/removing reachable symbols
std::vector<bool> calculateReachableSymbols(grammar_t * g);
void removeRlsWNonReachableSyms(grammar_t * g, std::vector<bool> rsyms);

//Print
void print_rules(rulelist_t * rules, grammar_t * g);

//