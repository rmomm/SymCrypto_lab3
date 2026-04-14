#include "Header.h"

int main() {

    string text = cleanText(readFile("12.txt"));
    ofstream out("output.txt");

    if (!out.is_open()) {
        cout << "Помилка відкриття\n";
        return 1;
    }

    auto freq = BigramFreqN(text);

    vector<pair<string, int>> vec(freq.begin(), freq.end());
    sort(vec.begin(), vec.end(),
        [](auto& a, auto& b) { r
        eturn a.second > b.second; 
        });

    vector<string> cipherBigrams;

    out << "ТОП-5 біграм:\n";
    for (int i = 0; i < 5; i++) {
        out << vec[i].first << " : " << vec[i].second << "\n";
        cipherBigrams.push_back(vec[i].first);
    }

    vector<string> lang = { "ст","но","то","на","ен" };

    int m = 31 * 31;

    for (auto X1 : lang)
        for (auto X2 : lang)
            for (auto Y1 : cipherBigrams)
                for (auto Y2 : cipherBigrams)
                {
                    if (X1 == X2 || Y1 == Y2) continue;

                    int x1 = bigramToNum(X1);
                    int x2 = bigramToNum(X2);
                    int y1 = bigramToNum(Y1);
                    int y2 = bigramToNum(Y2);

                    int dx = (x1 - x2 + m) % m;
                    int dy = (y1 - y2 + m) % m;

                    vector<int> a_vals = LinCongr(dx, dy, m);

                    for (int a : a_vals) {
                        int b = (y1 - a * x1) % m;
                        if (b < 0) b += m;

                        string dec = decrypt(text, a, b);

                        if (!dec.empty() && isRusText(dec)) {
                            out << "\nKEY FOUND:\n";
                            out << "a=" << a << " b=" << b << "\n";
                            out << dec << "\n";
                            return 0;
                        }
                    }
                }

}