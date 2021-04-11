#include "grammar.h"

grammar_t * new_grammar()
{
    grammar_t * g = (grammar_t *) malloc(sizeof(grammar_t));
    g->rules = new std::vector<rule_t*>;
    g->symbols = new std::vector<std::string>;
    g->symbols->push_back("#");
    g->symbols->push_back("$");
    return g;
}
rule_t * new_rule(int left, std::vector<int> right)
{
    rule_t * rule = (rule_t *) malloc(sizeof(rule_t));
    rule->rhs = new std::vector<int>;
    *(rule->rhs)->insert((rule->rhs)->end(), right.begin(), right.end());
    rule->lhs = left;
    return rule;
}
void pushSymbol(std::string symbol, std::vector<std::string> & symbols)
{
    std::vector<std::string>::iterator it;
    it = std::find(symbols.begin(), symbols.end(), symbol);
    if(it == symbols.end()){symbols.push_back(symbol);}
}
int idxOf(std::string sym, std::vector<std::string> & symbols)
{
    int i = 0;
    while((symbols[i] != sym) && (i<symbols.size()) ){i++;};
    return (symbols[i] == sym) ? i : -1;
}

void print_grammar(grammar_t * grammar)
{
    std::cout << grammar->symbols->size() << std::endl;
    std::vector<std::string> * symbls = grammar->symbols;
    std::vector<rule_t*> * rls = grammar->rules;
    std::cout << YELLOW << "Symbols: " << RESET << std::endl;
    for(int i = 0; i < symbls->size(); i++)
    {
        std::cout << "[" << symbls->at(i) << " : " << i << "]    ";
    }
    std::cout << std::endl;
    std::cout << YELLOW << "Rules: " << RESET << std::endl;
    
}