#include "Header.h"

int main() {
    string text = cleanText(readFile("12.txt"));
    ofstream out("output.txt");

    if (!out.is_open()) {
        cout << "Error\n";
        return 1;
    }

    findKeyAndDecrypt(text, out);

    return 0;
}