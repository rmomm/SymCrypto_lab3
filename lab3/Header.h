#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <set>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

string cleanText(const string& text);
string readFile(const string& filename);
map<string, int> BigramFreq(const string& text);
map<string, int> BigramFreqN(const string& text);
void printTopBigrams(map<string, int> freq, ofstream& out, int top = 10);
void printBigram(const string& text, ofstream& out);
void printBigramN(const string& text, ofstream& out);

int extendedgcd(int a, int b, int& x, int& y);
int modInverse(int a, int m);
vector<int> LinCongr(int a, int b, int m);