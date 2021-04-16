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

std::vector<bool> calculateReachableSymbols(grammar_t * g)
{
    std::vector<bool> reachable(g->symbols->size(), false);
    std::vector<std::string> symbls = *(g->symbols);
    set_t terms = getTerminals(g);
    std::vector<rule_t*> &rls = *(g->rules);

    reachable.at(2) = true;
    bool changed = true;
    while(changed)
    {
        changed = false;

        for(int i = 0; i < rls.size(); i++)
        {
            rule_t * rule = rls.at(i);
            int l = rule->lhs;
            std::vector<int> r = *(rule->rhs);
            if(reachable.at(l) == true)
            {
                for(auto x : r)
                {
                    if(reachable.at(x) == false){changed = true;}
                    reachable.at(x) = true;
                }
            }
        }
    }
    return reachable;
}

std::vector<bool> calculateGeneratingSymbols(grammar_t * g)
{
    std::vector<std::string> symbls = *(g->symbols);
    set_t terms = getTerminals(g);
    std::vector<rule_t*> &rls = *(g->rules);
    std::vector<bool> gsymb(symbls.size(), false);

    //initialization
    std::set<int> t = getTerminals(g);
    gsymb.at(idxOf("#",*(g->symbols))) = 1;
    for(auto &i : t)
    {
        gsymb.at(i) = true; //!< terminals are generating
    }
    //LOOP
    bool changed = true;
    while(changed)
    {
        changed = false;
        for(auto &rl : rls)
        {
            int lhs = rl->lhs;
            std::vector<int> &rhs = *(rl->rhs);

            auto rhsterm = rhs.begin();
            while(rhsterm != rhs.end() && gsymb.at(*rhsterm) == 1)
            {rhsterm++;}

            if(rhsterm == rhs.end())
            { 
               if(gsymb.at(lhs) == false){changed = true;}
               gsymb.at(lhs) = 1; 
            }
        }
    }
    return gsymb;
}

void removeRlsWNonGenSyms(grammar_t * g, std::vector<bool> gensym)
{   
    rulelist_t * keep = new rulelist_t;
    for(int i = 0; i < g->rules->size(); i++ )
    {
        rule_t * rulee = g->rules->at(i);//<! pointer to current rule
        int lhs = rulee->lhs; //copy of lhs
        std::vector<int> rhs = *(rulee->rhs); //copy or rhs

        std::vector<int>::iterator term = rhs.begin(); // iterate over current rules rhs

        while((term != rhs.end()) && (gensym.at(*term)==1) )// inc term while it points to a generating sym
        {
            term++;
        }
        if(term == rhs.end())//delete rule if it has a non generating symbol
        {
            keep->push_back(new_rule(lhs,rhs));
        }
    }
    deleteRuleList(g);
    g->rules = keep;

}

void removeRlsWNonReachableSyms(grammar_t * g, std::vector<bool> rsyms)
{
    rulelist_t * keep = new rulelist_t;
    for(int i = 0; i < g->rules->size(); i++)
    {
        rule_t* rule =  g->rules->at(i);
        bool toKeep = 1;
        if(!rsyms.at(rule->lhs))// THIS LINE IS A MAYBE AND COULD BE A CAUSE FOR FAILED TEST CASES
        {toKeep = 0;}
        for(int i : *(rule->rhs))
        {
            if(!rsyms.at(i))
            {toKeep = 0;}
        }
        if(toKeep)
        {keep->push_back(new_rule(rule->lhs, *(rule->rhs)));}
    }
    deleteRuleList(g);
    g->rules = keep;
}

void print_rule(rule_t * rule, grammar_t * g)
{
    std::cout << g->symbols->at(rule->lhs) << " -> ";
    print_rhs(rule->rhs, g);
    std::cout << std::endl;
}

void print_rhs(std::vector<int> * rhs, grammar_t * g)
{
    for(unsigned int i = 0; i < rhs->size(); i++)
    {
        std::cout << g->symbols->at(rhs->at(i)) << " ";
    }
}

void print_rules(rulelist_t * rules, grammar_t * g)
{
    for(unsigned int i = 0; i < rules->size(); i++)
    {
        print_rule(rules->at(i), g);
    }
}

void print_grammar(grammar_t * grammar)
{
    std::cout << "Symbols: " << std::endl;
    print_symbols(grammar->symbols);
    std::cout << "Rules: " << std::endl;
    print_rules(grammar->rules, grammar);
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
    for (auto it = s.begin(); it != s.end(); ++it)
    {
        std::cout << g->symbols->at(*it) << ' ';
    }
    //std::cout << RESET;
}
void printSetWithStrAndComma(std::set<int> s, grammar_t * g)
{
    //std::cout << YELLOW;
    std::set<int>::iterator it = s.begin();
    std::set<int>::iterator last = it;
    std::advance(last, s.size()-1);
    for (; it != last; ++it)
    {
        std::cout << g->symbols->at(*it) << ", ";
    }
    std::cout << g->symbols->at(*it) << " ";
    //std::cout << RESET;
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
    //print_grammar(g);

    set_t temp;
    for(unsigned int i = 0; i < g->symbols->size(); i++)
    {follow.push_back(temp);} //!< populate return vector

    //INITIALIZATION
    std::set<int>::iterator x = nt.begin();
    follow.at(*x).insert(idxOf("$", *(g->symbols)));//!< rule 1

    //APPLY RULES IV/V
    for(unsigned int i = 0; i < rls.size(); i++)//!< for each rule
    {
        rule_t & rule = *(rls.at(i));
        int l = rule.lhs;
        std::vector<int>::iterator it = (rule.rhs)->begin();
        for(int j = 0; j < rls.size(); j++)//against each rhs
        {
            std::vector<int> r = *(rls.at(j)->rhs);
            for(int k = 0; k < r.size()-1; k++)//against each rhs token
            {
                if(r.at(k) == l)
                {
                    int nxidx = r.at(k+1);
                    std::set<int> noep = removeEpsilon(first.at(nxidx), g);
                    follow.at(l).insert(noep.begin(), noep.end()); //rule 1
                    int kk = k+1;
                    while((kk < r.size()-1) && contains(first.at(r.at(kk)), idxOf("#", *(g->symbols))))//!< loop for rule 2(sketchy)
                    {
                        nxidx = r.at(kk+1);
                        noep = removeEpsilon(first.at(nxidx), g);
                        follow.at(l).insert(noep.begin(), noep.end());
                        kk++;
                    }
                }
            }
        }
    }

    //LOOP RULES II/III
    bool changed = true;
    while(changed)
    {
        changed = false;
        //LOOP FOR RULE II
        for(int i = 0; i < rls.size();i++)//for each rule
        {
            rule_t & rule = *(rls.at(i));
            int l = rule.lhs;

            for(int j = 0; j < rls.size(); j++)//against every other rhs
            {
                std::vector<int> r = *(rls.at(j)->rhs);
                int rend = (r.at(r.size()-1));
                int rendl = rls.at(j)->lhs;
                if(rend == l)
                {
                    std::set<int> old = follow.at(l);
                    follow.at(l).insert(follow.at(rendl).begin(), follow.at(rendl).end());//apply rule II
                    if(follow.at(l)!= old){changed = true;}
                }
            }
        }
        //LOOP FOR RULE III
        for(int i = 0; i < rls.size(); i++)
        {
            int l = rls.at(i)->lhs;
            for(int j = 0; j < rls.size(); j++)
            {
                std::vector<int> r = *(rls.at(j)->rhs);
                int ll = rls.at(j)->lhs;
                for(int k = 0; k < r.size(); k++)
                {
                    if((r.at(k) == l) && (k < r.size()-1)) 
                    {
                        int kk = k+1;
                        while((kk<r.size()) && contains(first.at(r.at(kk)), idxOf("#", *(g->symbols))))
                        {
                            kk++;
                        }
                        if(kk >= r.size())
                        {
                            std::set<int> old = first.at(l);
                            std::set<int> ins = first.at(ll);
                            first.at(l).insert(ins.begin(), ins.end());
                            if(first.at(l) != old){changed = true;}
                        }
                    }
                }
            }
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
void deleteRuleList(grammar_t * g)
{
    for(unsigned int i = 0; i < g->rules->size(); i++)
    {
        deleteRule(g->rules->at(i));
        free((g->rules)->at(i));
    }
    delete g->rules;
}
void deleteRule(rule_t * r)
{
    delete r->rhs;
}