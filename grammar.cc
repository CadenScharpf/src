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
    unsigned int i = 0;
    while((symbols[i] != sym) && (i<symbols.size()) ){i++;};
    return (symbols[i] == sym) ? i : -1;
}

void print_symbols(std::vector<std::string> * symbls)
{
    for(unsigned int i = 0; i < symbls->size(); i++)
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
    for(unsigned int i = 0; i < rhs->size(); i++)
    {
        std::cout << rhs->at(i) << " ";
    }
}

void print_rules(std::vector<rule_t*> * rules)
{
    for(unsigned int i = 0; i < rules->size(); i++)
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
    for(unsigned int i = 2; i < symbls->size(); i++){tnt.insert(i);}
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
    for(unsigned int i = 0; i < rules.size(); i++)
    {
        nt.insert((rules.at(i))->lhs);
    }
    return nt;
}
std::set<int> getTermsAndNonTerms(grammar_t * g)
{
    std::set<int> tnt;
    std::vector<std::string> symbls = *(g->symbols);
    for(unsigned int i = 2; i < symbls.size(); i++)
    {
        tnt.insert(i);
    }
    return tnt;
}
std::set<int> getTerminals(grammar_t * g)
{
    std::set<int> nt = getNonTerminals(g);
    std::set<int> tnt = getTermsAndNonTerms(g);
    std::set<int> d = diff(tnt,nt);
    return d;
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
void printSetWithStrAndComma(std::set<int> s, grammar_t * g)
{
    std::cout << YELLOW;
    std::set<int>::iterator it = s.begin();
    std::set<int>::iterator last = it;
    std::advance(last, s.size()-1);
    for (; it != last; ++it)
    {
        std::cout << g->symbols->at(*it) << ", ";
    }
    std::cout << g->symbols->at(*it) << " ";
    std::cout << RESET;
}

setlist_t calcFirstSets(grammar_t * g)
{   
    setlist_t first;//!< first set obj
    rulelist_t & rls = *(g->rules);//ref to g->rules
    symbollist_t & symbls = *(g->symbols);
    set_t terminals = getTerminals(g);

    set_t temp;
    for(unsigned int i = 0; i < g->symbols->size(); i++)
    {first.push_back(temp);} //!< populate return vector

    //INITIALIZATION
    first.at(idxOf("#",symbls)).insert(idxOf("#",symbls));//!< rule 1: add # to first(#)

     for (auto it = terminals.begin(); it != terminals.end(); ++it)//!< for each terminal
     {
        first.at(*it).insert(*it);
     }

     //LOOP STEPS III - V
     bool changed = true;
     while(changed)//!< repeat steps III - V
     {
         changed = false;
         for(unsigned int i = 0;i < rls.size(); i++)//!< for every grammar rule
         {
            rule_t & r = *(rls.at(i));
             set_t before = first.at(r.lhs);
             if(r.rhs->size() > 0)//!< rule 3
             {
                set_t e = first.at(r.rhs->at(0));
                e = removeEpsilon(e,g);
                first.at(r.lhs).insert(e.begin(), e.end());
             }
             auto it = r.rhs->begin();
             while
             (
                (it != r.rhs->end())
                &&
                (std::find(first.at(*it).begin(), first.at(*it).end(), idxOf("#", *(g->symbols))) 
                    != first.at(*it).end())
             )
             {it++;};
             if(it != r.rhs->end())//!< rule 4
             {
                 set_t e = first.at(*it);
                 set_t epsilon;
                 epsilon.insert(idxOf("#",symbls));
                 e = diff(e, epsilon);

                 first.at(r.lhs).insert(e.begin(), e.end());
             } else {
                 first.at(r.lhs).insert(idxOf("#",symbls));//!< rule 5
             }
             if((first.at(r.lhs)) != before){changed = true;};//!< check for change
         }
     }
    return first;
}
void printFirstSets(std::vector<std::set<int>> s, grammar_t * g)
{
    std::set<int> nt = getNonTerminals(g);
     for (auto it = nt.begin(); it != nt.end(); ++it)
    {   
        std::cout << "FIRST(" << (g->symbols)->at(*it) << ") = { ";
        printSetWithStrAndComma(s.at(*it), g);
        std::cout << "}" << std::endl;
    }
}
void printFollowSets(std::vector<std::set<int>> s, grammar_t * g)
{
    std::set<int> nt = getNonTerminals(g);
     for (auto it = nt.begin(); it != nt.end(); ++it)
    {   
        std::cout << "FOLLOW(" << (g->symbols)->at(*it) << ") = { ";
        printSetWithStrAndComma(s.at(*it), g);
        std::cout << "}" << std::endl;
    }
}
void printFullFirstSets(std::vector<std::set<int>> s, grammar_t * g)
{
     for(unsigned int i = 0; i < s.size(); i++)
    {   
        std::cout << "FIRST(" << (g->symbols)->at(i) << ") = { ";
        printSetWithStr(s.at(i), g);
        std::cout << "}" << std::endl;
    }
}
void printFullFollowSets(std::vector<std::set<int>> s, grammar_t * g)//!< for submission
{
    for(unsigned int i = 0; i < s.size(); i++)
    {   
        std::cout << "FOLLOW(" << (g->symbols)->at(i) << ") = { ";
        printSetWithStr(s.at(i), g);
        std::cout << "}" << std::endl;
    }
}
std::vector<std::set<int>> calcFollowSets(grammar_t * g, setlist_t first)
{
    //bool changed = true;
    setlist_t follow;//!< first set obj
    rulelist_t & rls = *(g->rules);//ref to g->rules
    //symbollist_t & symbls = *(g->symbols);
    set_t terminals = getTerminals(g);
    set_t nt = getNonTerminals(g);

    set_t temp;
    for(unsigned int i = 0; i < g->symbols->size(); i++)
    {follow.push_back(temp);} //!< populate return vector

    //INITIALIZATION
    std::set<int>::iterator x = nt.begin();
    follow.at(*x).insert(idxOf("$", *(g->symbols)));//!< rule 1

    //LOOP
    for(unsigned int i = 0; i < rls.size(); i++)//!< for each rule
    {
        rule_t & rule = *(rls.at(i));//!< refence to current rule
        std::vector<int>::iterator it = (rule.rhs)->begin();
        while(it != (rule.rhs)->end())
        {
            
        }

    }
    return follow;
}

set_t removeEpsilon(set_t s, grammar_t * g)
{
    set_t epsilon;
    epsilon.insert(idxOf("#",*(g->symbols)));
    return diff(s, epsilon);
}


void deleteGrammar(grammar_t * g)
{
    std::vector<rule_t*> rules = *(g->rules);
    for(unsigned int i = 0; i < rules.size(); i++)
    {
        deleteRule(rules.at(i));
        free((g->rules)->at(i));
    }
    delete g->rules;
    delete g->symbols;
    free(g);
}
void deleteRule(rule_t * r)
{
    delete r->rhs;
}