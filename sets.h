#pragma once

#include <set>
#include <iostream>
#include <vector>
#include <algorithm>

std::set<int> conjunction(std::set<int> a, std::set<int> b);//!< Set intersection
std::set<int> disjunction(std::set<int> a, std::set<int> b);//!< Set union
std::set<int> diff(std::set<int> a, std::set<int> b);//!< Set difference
void printSet(std::set<int> myset);
bool contains(std::set<int> s, int x);