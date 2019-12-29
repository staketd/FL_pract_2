#include <iostream>
#include <Grammar.h>
#include <Earley.h>

using namespace std;

int main()
{
    int n;
    char c;
    cin >> n >> c;
    vector<pair<char, string>> data(n);
    for (int i = 0; i < n; ++i) {
        cin >> data[i].first >> data[i].second;
    }
    Grammar g(data, c);
    Earley e(g);
    string word;
    cin >> word;
    e.setWord(word);
    cout << (e.checkWord() ? "YES" : "NO");
}
