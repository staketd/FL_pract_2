#ifndef PRACT_2_GRAMMAR_H
#define PRACT_2_GRAMMAR_H

#include <vector>
#include <string>
#include <unordered_map>

using std::string;
using std::pair;

class Grammar {
    struct Rule {
        int leftSide_;
        std::vector<int> rightSide_;

        Rule();

        Rule(const int&, std::vector<int>);
        Rule(const char&, const string&);
    };

    int rulesNum_;
public:

    std::unordered_map<int, std::vector<int>> NotTerminalToRule;
    std::vector<Rule> rules_;
    int startSymbol_;
    static constexpr int epsilon = -1;
    Grammar() : rules_(0), startSymbol_('\0'), rulesNum_(0) {}

    static bool isTerminal(int);

    static int convertFromCharToInt(const char &c);

    Grammar(const std::vector<pair<char, string>> &rules, char startSymbol);

    void addRule(const char&, const string &rightSide);

    void addRule(const int& , const std::vector<int>&);

};

#endif //PRACT_2_GRAMMAR_H
