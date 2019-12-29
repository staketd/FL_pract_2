#ifndef PRACT_2_EARLEY_H
#define PRACT_2_EARLEY_H

#include <Grammar.h>
#include <unordered_map>

class Earley {
    Grammar G_;
    std::vector<int> word_;

    struct Event {
        int rule_, rulePos_;
        int begin_;
        Event();
        Event(int rule, int rulePos, int length);

        unsigned long long getHash() const;
    };

    std::vector<std::vector<Event>> D_;
    std::vector<std::unordered_map<unsigned long long, bool>> EventExistsInD_;

    void addToD_(const Event &event, int classInd);

    void scan(const Event &e, int classInd);

    void complete(const Event &e, int classInd);

    void predict(const Event &e, int classInd);

    void initD_();

public:
    Earley();
    explicit Earley(Grammar G);

    void setWord(const string &word);

    void setWord(const std::vector<int>& word);

    bool checkWord();

};


#endif //PRACT_2_EARLEY_H
