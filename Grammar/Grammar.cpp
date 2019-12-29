#include "Grammar.h"

Grammar::Rule::Rule() : leftSide_(), rightSide_() {}

Grammar::Rule::Rule(const int &leftSide, std::vector<int> rightSide) : leftSide_(leftSide),
                                                                       rightSide_(std::move(rightSide)) {}

int Grammar::convertFromCharToInt(const char &c)  {
    return (c == '_' ? Grammar::epsilon : (int)c);
}

Grammar::Rule::Rule(const char &c, const string& rightSide_s) {
    leftSide_ = convertFromCharToInt(c);
    int sz = 0;
    for (char rightSide_char : rightSide_s) {
        if (rightSide_char != '_') {
            ++sz;
        }
    }
    rightSide_.resize(sz);
    int cnt = 0;
    for (char rightSide_char : rightSide_s) {
        if (rightSide_char != '_') {
            rightSide_[cnt++] = convertFromCharToInt(rightSide_char);
        }
    }
}

Grammar::Grammar(const std::vector<pair<char, string>> &rules, const char startSymbol)  : startSymbol_(startSymbol),
                                                                                            rulesNum_(rules.size()) {
    rules_.resize(rulesNum_);
    for (int i = 0; i < rulesNum_; ++i) {
        rules_[i] = Rule(rules[i].first, rules[i].second);
        NotTerminalToRule[rules_[i].leftSide_].push_back(i);
    }
    startSymbol_ = convertFromCharToInt(startSymbol);
}

void Grammar::addRule(const char &leftSide, const string &rightSide) {
    rulesNum_++;
    rules_.emplace_back(leftSide, rightSide);
    NotTerminalToRule[rules_.back().leftSide_].push_back(rules_.size() - 1);
}


bool Grammar::isTerminal(int symb) {
    return !(convertFromCharToInt('A') <= symb && symb <= convertFromCharToInt('Z'));
}

void Grammar::addRule(const int& leftSide, const std::vector<int>& rightSide) {
    rulesNum_++;
    rules_.emplace_back(leftSide, rightSide);
    NotTerminalToRule[rules_.back().leftSide_].push_back(rules_.size() - 1);
}
