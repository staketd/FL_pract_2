#ifndef PRACT_2_EARLEY_H
#define PRACT_2_EARLEY_H

#include <Grammar.h>

class Earley {
    Grammar G_;
    std::vector<int> word_;

    struct Event {
        int rule_, rulePos_;
        int begin_;
        Event();
        Event(int rule, int rulePos, int length);
    };

    std::vector<std::vector<Event>> D_;

    void scan(const Event &e, int classInd);

    void complete(const Event &e, int classInd);

    void predict(const Event &e, int classInd);

    void initD_();

public:
    Earley();
    Earley(Grammar G);

    void setWord(const string &word);

    void setWord(const std::vector<int>& word);

    bool checkWord();

};


#endif //PRACT_2_EARLEY_H
