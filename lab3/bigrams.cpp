#include "Header.h"

string cleanText(const string& text) {
    string result;

    for (char c : text) {
        if (c != ' ' && c != '\n' && c != '\r') {
            result += c;
        }
    }

    return result;
}

string readFile(const string& filename) {
    ifstream in(filename);
    string text, line;

    while (getline(in, line)) {
        text += line;
    }

    return text;
}

map<string, int> BigramFreq(const string& text) {
    map<string, int> freq;

    for (size_t i = 0; i + 1 < text.size(); i++) {
        string bg;
        bg += text[i];
        bg += text[i + 1];

        freq[bg]++;
    }
    return freq;
}

map<string, int> BigramFreqN(const string& text) {
    map<string, int> freq;

    for (size_t i = 0; i + 1 < text.size(); i += 2) {
        string bg;
        bg += text[i];
        bg += text[i + 1];

        freq[bg]++;
    }
    return freq;
}

void printTopBigrams(map<string, int> freq, ofstream& out, int top) {
    vector<pair<string, int>> vec(freq.begin(), freq.end());

    sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
        return a.second > b.second;
        });

    out << "\nТОП-" << top << " біграм:\n";

    for (int i = 0; i < min(top, (int)vec.size()); i++) {
        out << vec[i].first << " : " << vec[i].second << "\n";
    }
}

void printBigram(const string& text, ofstream& out) {
    map<string, int> freq;
    set<char> letters;

    int total = 0;
    for (char c : text) {
        letters.insert(c);
    }

    for (size_t i = 0; i + 1 < text.size(); i++) {
        string bg;
        bg += text[i];
        bg += text[i + 1];

        freq[bg]++;
        total++;
    }

    out << "\nМатриця біграм (з перетином):\n   ";

    for (char c : letters) {
        char dchar = (c == ' ') ? '_' : c;
        out << setw(9) << dchar;
    }
    out << "\n";

    for (char row : letters) {
        char drow = (row == ' ') ? '_' : row;
        out << setw(6) << drow;

        for (char col : letters) {
            string bg;
            bg += row;
            bg += col;

            double prob = (double)freq[bg] / total;
            out << setw(9) << fixed << setprecision(6) << prob;
        }
        out << "\n";
    }
}

void printBigramN(const string& text, ofstream& out) {
    map<string, int> freq;
    set<char> letters;
    int total = 0;

    for (char c : text) {
        letters.insert(c);
    }

    for (size_t i = 0; i + 1 < text.size(); i += 2) {
        string bg;
        bg += text[i];
        bg += text[i + 1];
        freq[bg]++;
        total++;
    }

    out << "\nМатриця біграм (без перетину):\n   ";

    for (char c : letters) {
        char dchar = (c == ' ') ? '_' : c;
        out << setw(9) << dchar;
    }
    out << "\n";

    for (char row : letters) {
        char drow = (row == ' ') ? '_' : row;
        out << setw(6) << drow;

        for (char col : letters) {
            string bg;
            bg += row;
            bg += col;

            double prob = (double)freq[bg] / total;
            out << setw(9) << fixed << setprecision(6) << prob;
        }
        out << "\n";
    }
}