#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

int extendedgcd(int a, int b, int& x, int& y);
int modInverse(int a, int m);
vector<int> LinCongr(int a, int b, int m);

string cleanText(const string& text);
string readFile(const string& filename);
map<string, int> BigramFreq(const string& text);
map<string, int> BigramFreqN(const string& text);

int bigramToNum(const string& bg);
string numToBigram(int x);
string decrypt(const string& text, int a, int b);
bool isRusText(const string& text);
void findKeyAndDecrypt(const string& text, ofstream& out);