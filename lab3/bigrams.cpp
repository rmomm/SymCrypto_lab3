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
        string bg = text.substr(i, 2);
        freq[bg]++;
    }
    return freq;
}

map<string, int> BigramFreqN(const string& text) {
    map<string, int> freq;

    for (size_t i = 0; i + 1 < text.size(); i += 2) {
        string bg = text.substr(i, 2);
        freq[bg]++;
    }
    return freq;
}