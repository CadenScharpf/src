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

void print_symbols(std::vector<std::string> * symbls)
{
    for(int i = 0; i < symbls->size(); i++)
    {
        std::cout << "[" << symbls->at(i) << " : " << i << "]    ";
    }
    std::cout << std::endl;
}

void print_rule(rule_t * rule)
{
    std::cout << rule->lhs << ": ";
    print_rhs(rule->rhs);
    std::cout << std::endl;
}

void print_rhs(std::vector<int> * rhs)
{
    for(int i = 0; i < rhs->size(); i++)
    {
        std::cout << rhs->at(i) << " ";
    }
}

void print_rules(std::vector<rule_t*> * rules)
{
    for(int i = 0; i < rules->size(); i++)
    {
        print_rule(rules->at(i));
    }
}

void print_grammar(grammar_t * grammar)
{
    std::cout << YELLOW << "Symbols: " << RESET << std::endl;
    print_symbols(grammar->symbols);
    std::cout << YELLOW << "Rules: " << RESET << std::endl;
    print_rules(grammar->rules);
}

/**
 * @brief print function for task one
 * 
 * @param grammar 
 */
void printTermsAndNonTerms(grammar_t * grammar)
{
    std::vector<std::string> * symbls = grammar->symbols;
    std::set<int> tnt;
    for(int i = 2; i < symbls->size(); i++){tnt.insert(i);}
    std::set<int> nt = getNonTerminals(grammar);
    std::set<int> t = diff(tnt, nt);
    printSetWithStr(t,grammar);
    printSetWithStr(nt,grammar);
    std::cout << std::endl;
}

std::set<int> getNonTerminals(grammar_t * g)
{
    std::set<int> nt;
    std::vector<rule_t*> rules = *(g->rules);
    for(int i = 0; i < rules.size(); i++)
    {
        nt.insert((rules.at(i))->lhs);
    }
    return nt;
}
std::set<int> getTermsAndNonTerms(grammar_t * g)
{
    std::set<int> tnt;
    std::vector<std::string> symbls = *(g->symbols);
    for(int i = 2; i < symbls.size(); i++)
    {
        tnt.insert(i);
    }
}
void printSetWithStr(std::set<int> s, grammar_t * g)
{
    std::cout << YELLOW;
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << g->symbols->at(*it) << ' ';
    }
    std::cout << RESET;
}