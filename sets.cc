#include "sets.h"

/** conjunction: std::set<int>
 * @brief calculates the intersection of two std::set<int>
 * 
 * @param a 
 * @param b 
 * @return std::set<int> 
 */
std::set<int> conjunction(std::set<int> a, std::set<int> b)
{
    std::set<int> intersect;
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(intersect, intersect.begin()));
    return intersect;
};
/** disjunction: std::set<int>
 * @brief calculates the union of two std::set<int>
 * 
 * @param a 
 * @param b 
 * @return std::set<int> 
 */
std::set<int> disjunction(std::set<int> a, std::set<int> b)
{
    std::set<int> uni;
    set_union(a.begin(), a.end(), b.begin(), b.end(), std::inserter(uni, uni.begin()));
    return uni;
};

/**
 * @brief 
 * 
 * @param a 
 * @param b 
 * @return std::set<int> 
 */
std::set<int> diff(std::set<int> a, std::set<int> b)
{
    std::set<int> dif;
    set_difference(a.begin(), a.end(), b.begin(), b.end(), std::inserter(dif, dif.begin()));
    return dif;
}
/** printSet: void
 * @brief Outputs the contents of a std::set<int> to std output
 * 
 * @param myset 
 */
void printSet(std::set<int> myset)
{
        for (auto it = myset.begin(); it != myset.end(); ++it)
        {
            std::cout << *it << ' ';
        }
        std::cout << std::endl;
}