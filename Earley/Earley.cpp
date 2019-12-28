#include "Earley.h"

Earley::Earley(Grammar G): G_(std::move(G)), D_(0) {
    G_.addRule(Grammar::epsilon - 1, std::vector<int>{G.startSymbol_});
    G_.startSymbol_ = Grammar::epsilon - 1;
}

Earley::Earley(): G_(), word_(), D_(0) {}

void Earley::scan(const Earley::Event &e, int classInd) {
    auto event_rule = G_.rules_[e.rule_];
    if (e.rulePos_ >= event_rule.rightSide_.size()) {
        return;
    }
    if (!Grammar::isTerminal(event_rule.rightSide_[e.rulePos_])) {
        return;
    }
    if (G_.rules_[e.rule_].rightSide_[e.rulePos_] == word_[classInd]) {
        if (classInd + 1 < D_.size()) {
            D_[classInd].push_back(Event(e.rule_, e.rulePos_ + 1, e.begin_));
        }
    }
}

void Earley::predict(const Earley::Event &e, int classInd) {
    auto event_rule = G_.rules_[e.rule_];
    if (e.rulePos_ >= event_rule.rightSide_.size()) {
        return;
    }
    if (Grammar::isTerminal(event_rule.rightSide_[e.rulePos_])) {
        return;
    }
    for (auto rule: G_.NotTerminalToRule[event_rule.rightSide_[e.rulePos_]]) {
        D_[classInd].emplace_back(rule, 0, classInd);
    }
}

void Earley::complete(const Earley::Event &e, int classInd) {
    auto event_rule = G_.rules_[e.rule_];
    if (e.rulePos_ + 1 != event_rule.rightSide_.size()) {
        return;
    }
    for (auto event: D_[e.begin_]) {
        auto rule = G_.rules_[event.rule_];
        if (event_rule.leftSide_ == rule.rightSide_[event.rulePos_]) {
            D_[classInd].emplace_back(event.rule_, event.rulePos_ + 1, event.begin_);
        }
    }
}

void Earley::setWord(const string &word) {
    word_.resize(word.size());
    for (int i = 0; i < word.size(); ++i) {
        word_[i] = Grammar::convertFromCharToInt(word[i]);
    }
}

void Earley::setWord(const std::vector<int>& word) {
    word_ = word;
}

bool Earley::checkWord() {
    initD_();
    int lastPos = 0;
    for (int j = 0; j < word_.size(); ++j) {
        for (int i = lastPos; i < D_[j].size(); ++i) {
            scan(D_[j][i], j);
        }
        int prevSize = D_[j].size();
        do {
            prevSize = D_[j].size();
            for (int i = lastPos; i < D_[j].size(); ++i) {
                complete(D_[j][i], j);
                predict(D_[j][i], j);
            }
        } while (prevSize != D_[j].size());
    }
    for (auto event: D_.back()) {
        if (event.rule_ == G_.rules_.size() - 1 && event.rulePos_ == 1 && event.begin_ == 0) {
            return true;
        }
    }
    return false;
}

void Earley::initD_() {
    D_.resize(word_.size(), {});
    D_[0].emplace_back(G_.rules_.size() - 1, 0, 0);
}

Earley::Event::Event(): rule_(0), rulePos_(0), begin_(0) {}

Earley::Event::Event(int rule, int rulePos, int length): rule_(rule), rulePos_(rulePos), begin_(length) {}
