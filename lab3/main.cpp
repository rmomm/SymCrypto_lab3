#include "Header.h"

int main() {
    string inputFile = "12.txt";     
    string outputFile = "output.txt";   

    string text = readFile(inputFile);
    text = cleanText(text);
    ofstream out(outputFile);

    if (!out.is_open()) {
        cout << "Помилка відкриття output файлу\n";
        return 1;
    }

    out << "Довжина тексту: " << text.size() << "\n";

    auto freq1 = BigramFreq(text);
    auto freq2 = BigramFreqN(text);

    printTopBigrams(freq1, out);
    printTopBigrams(freq2, out);

  
    printBigram(text, out);
    printBigramN(text, out);

    out.close();

    return 0;
}