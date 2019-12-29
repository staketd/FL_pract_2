#include "gtest/gtest.h"
#include <Earley.h>
#include <vector>

TEST(CorrectBracketSequence, Test1) {
    std::vector<std::pair<char, std::string>> rules = {
            {'S', "(S)S"},
            {'S', "_"}
    };
    Grammar G(rules, 'S');
    Earley earley(G);
    earley.setWord("()");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("(()()()(()()))");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("(())())(");
    EXPECT_FALSE(earley.checkWord());
    earley.setWord("())())");
    EXPECT_FALSE(earley.checkWord());
}

TEST(Palindromes, Test2) {
    std::vector<std::pair<char, std::string>> rules;
    for (int i = 0; i < 26; ++i) {
        string rule;
        rule.resize(3);
        rule[0] = char('a' + i);
        rule[2] = char('a' + i);
        rule[1] = 'S';
        rules.emplace_back('S', string() + char('a' + i));
        rules.emplace_back('S', rule);
    }
    rules.emplace_back('S', "_");
    Grammar G(rules, 'S');
    Earley earley(G);
    earley.setWord("abba");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("bacab");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("bazxzxzab");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("bazazxzab");
    EXPECT_FALSE(earley.checkWord());
    earley.setWord("abc");
    EXPECT_FALSE(earley.checkWord());
}

TEST(ArithmeticExpression, Test3) {
    std::vector<std::pair<char, std::string>> rules = {
            {'S', "T+S"},
            {'S', "T"},
            {'T', "T*S"},
            {'T', "F"},
            {'F', "(S)"},
            {'F', "a"}
    };
    Grammar G(rules, 'S');
    Earley earley(G);
    earley.setWord("(a+a)");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("(a+a)*a");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("a");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("(a*a+a)");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("(a+a)*(a+a)");
    EXPECT_TRUE(earley.checkWord());
    earley.setWord("a+(a+a)+");
    EXPECT_FALSE(earley.checkWord());
    earley.setWord("a+a+a)");
    EXPECT_FALSE(earley.checkWord());
    earley.setWord("a*+(a+a)");
    EXPECT_FALSE(earley.checkWord());
    earley.setWord("*a*(a+a)+");
    EXPECT_FALSE(earley.checkWord());
    earley.setWord("(*a)*b");
    EXPECT_FALSE(earley.checkWord());
}

int main(int argc, char *argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}