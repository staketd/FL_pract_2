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
            addToD_(Event(e.rule_, e.rulePos_ + 1, e.begin_), classInd + 1);
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
        addToD_(Event(rule, 0, classInd), classInd);
    }
}

void Earley::complete(const Earley::Event &e, int classInd) {
    auto event_rule = G_.rules_[e.rule_];
    if (e.rulePos_ != event_rule.rightSide_.size() || e.rule_ + 1 == G_.rules_.size()) {
        return;
    }
    for (auto event: D_[e.begin_]) {
        auto rule = G_.rules_[event.rule_];
        if (event.rulePos_ < rule.rightSide_.size() && event_rule.leftSide_ == rule.rightSide_[event.rulePos_]) {
            addToD_(Event(event.rule_, event.rulePos_ + 1, event.begin_), classInd);
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
    for (int j = 0; j <= word_.size(); ++j) {
        lastPos = 0;
        for (int i = 0; j > 0 && i < D_[j - 1].size(); ++i) {
            scan(D_[j - 1][i], j - 1);
        }
        int prevSize = D_[j].size();
        do {
            prevSize = D_[j].size();
            for (int i = lastPos; i < prevSize; ++i) {
                complete(D_[j][i], j);
            }
            for (int i = lastPos; i < prevSize; ++i) {
                predict(D_[j][i], j);
            }
            lastPos = prevSize;
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
    D_.clear();
    EventExistsInD_.clear();
    D_.resize(word_.size() + 1, {});
    EventExistsInD_.resize(word_.size() + 1, {});
    addToD_(Event((int)G_.rules_.size() - 1, 0, 0), 0);
}

void Earley::addToD_(const Earley::Event &event, int classInd) {
    if (EventExistsInD_[classInd][event.getHash()]) {
        return;
    }
    EventExistsInD_[classInd][event.getHash()] = true;
    D_[classInd].push_back(event);
}

Earley::Event::Event(): rule_(0), rulePos_(0), begin_(0) {}

Earley::Event::Event(int rule, int rulePos, int length): rule_(rule), rulePos_(rulePos), begin_(length) {}

unsigned long long Earley::Event::getHash() const {
    return ((unsigned long long)rule_ << 40) | ((unsigned long long) rulePos_ << 20) | begin_;
}
