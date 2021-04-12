/*
 * Copyright (C) Mohsen Zohrevandi, 2017
 *               Rida Bazzi 2019
 * Do not share this file with anyone
 */
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lexer.h"
#include "grammar.h"
#include "sets.h"
#include "parser.h"

using namespace std;
LexicalAnalyzer lexer;std::set<int> getNonTerminals(grammar_t * g);
std::set<int> getTermsAndNonTerms(grammar_t * g);
std::set<int> getNonTerminals(grammar_t * g);
void printSetWithStr(std::set<int>, grammar_t * g);
void deleteGrammar(grammar_t * g);

grammar_t * grammar;
std::vector<std::set<int>> first;
std::vector<std::set<int>> follow;
// read grammar
void ReadGrammar()
{
    cout << "Reading Grammar\n";
    grammar = parseGrammar(lexer);
}

// Task 1
void printTerminalsAndNoneTerminals()
{
    cout << "Printing terminals and non terminals\n";
    printTermsAndNonTerms(grammar);
}

// Task 2
void RemoveUselessSymbols()
{
    cout << "Removing useless symbols\n";
}

// Task 3
void CalculateFirstSets()
{
    cout << "Calculating the first sets\n";
    first = calcFirstSets(grammar);
    printFirstSets(first, grammar);
}

// Task 4
void CalculateFollowSets()
{
    cout << "Calculating the follow sets\n";
    //calcFollowSets(grammar);
}

// Task 5
void CheckIfGrammarHasPredictiveParser()
{
    cout << "Cheching if grammar has a predictive parser\n";
}
    
int main (int argc, char* argv[])
{
    int task;
    if (argc < 2)
    {
        cout << "Error: missing argument\n";
        return 1;
    }

    /*
       Note that by convention argv[0] is the name of your executable,
       and the first argument to your program is stored in argv[1]
     */

    task = atoi(argv[1]);
    
    ReadGrammar();  // Reads the input grammar from standard input
                    // and represent it internally in data structures
                    // ad described in project 2 presentation file
    print_grammar(grammar);
    switch (task)
    {
        case 1: printTerminalsAndNoneTerminals();
            break;

        case 2: RemoveUselessSymbols();
            break;

        case 3: CalculateFirstSets();
            break;

        case 4: CalculateFollowSets();
            break;

        case 5: CheckIfGrammarHasPredictiveParser();
            break;

        default:
            cout << "Error:  unrecognized task number " << task << "\n";
            break;

    }
    deleteGrammar(grammar);
    return 0;
}

