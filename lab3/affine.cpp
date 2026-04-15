#include "Header.h"

string alphabet = "אבגדהוזחטיךכלםמןנסעףפץצקרשüû‎‏ÿ";
const int m = 31 * 31;

int bigramToNum(const string& bg) {
    int x1 = alphabet.find(bg[0]);
    int x2 = alphabet.find(bg[1]);
    return x1 * 31 + x2;
}

string numToBigram(int x) {
    string res = "  ";
    res[0] = alphabet[x / 31];
    res[1] = alphabet[x % 31];
    return res;
}

string decrypt(const string& text, int a, int b) {
    string result;

    int a_inv = modInverse(a, m);
    if (a_inv == -1) {
        return "";
    }

    for (size_t i = 0; i + 1 < text.size(); i += 2) {
        string bg = text.substr(i, 2);
        int y = bigramToNum(bg);

        int x = (a_inv * (y - b + m)) % m;
        result += numToBigram(x);
    }

    return result;
}


bool isRusText(const string& text) {
    int count_o = 0;
    int count_a = 0;
    int count_e = 0;
    int count_bad = 0;

    for (char c : text) {
        if (c == 'מ') count_o++;
        if (c == 'א') count_a++;
        if (c == 'ו') count_e++;

        if (c == 'פ' || c == 'ש')
            count_bad++;
    }

    double n = text.size();

    if (n == 0) { 
        return false; 
    }

    if (!(count_o / n > 0.07 && count_a / n > 0.05 && count_e / n > 0.05 && count_bad / n < 0.02))
        return false;

    vector<string> common = { "סע","םמ","עמ","םא","ום","םט","מג","נא" };
    int good = 0;
    for (auto& bg : common) {
        if (text.find(bg) != string::npos)
            good++;
    }

    return good >= 4;
}

int my_gcd(int a, int b)
{
    int x, y;
    return extendedgcd(a, b, x, y);
}

void findKeyAndDecrypt(const string& text, ofstream& out) {
    auto freq = BigramFreqN(text);
    vector<pair<string, int>> vec(freq.begin(), freq.end());

    sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
        return a.second > b.second;
    });

    vector<string> cipherBigrams;

    out << "Top 5 bigrams:\n";

    for (int i = 0; i < 5; i++) {
        out << vec[i].first << " : " << vec[i].second << "\n";
        cipherBigrams.push_back(vec[i].first);
    }

    vector<string> lang = { "סע","םמ","עמ","םא","ום" };
    bool found = false;

    for (auto X1 : lang)
        for (auto X2 : lang)
            for (auto Y1 : cipherBigrams)
                for (auto Y2 : cipherBigrams)
                {
                    if (X1 == X2 || Y1 == Y2) { 
                        continue; 
                    }

                    int x1 = bigramToNum(X1);
                    int x2 = bigramToNum(X2);
                    int y1 = bigramToNum(Y1);
                    int y2 = bigramToNum(Y2);

                    int dx = (x1 - x2 + m) % m;
                    int dy = (y1 - y2 + m) % m;

                    vector<int> a_vals = LinCongr(dx, dy, m);

                    for (int a : a_vals) {

                        if (my_gcd(a, m) != 1) { 
                            continue; 
                        }

                        int b = (y1 - a * x1) % m;

                        if (b < 0) {
                            b += m;
                        }

                        string dec = decrypt(text, a, b);

                        if (!dec.empty() && isRusText(dec)) {
                            found = true;
                            out << "\nKEY FOUND:\n";
                            out << "a = " << a << " b = " << b << "\n";

                            out << "Used bigrams:\n";
                            out << X1 << " -> " << Y1 << "\n";
                            out << X2 << " -> " << Y2 << "\n";

                            out << "\nDECRYPTED TEXT:\n";
                            out << dec << "\n";

                            continue;
                        }
                    }
                }

    if (!found) { 
        out << "\nKey not found\n"; 
    }
}