#include "Header.h"

int extendedgcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }

    int x1, y1;
    int gcd = extendedgcd(b, a % b, x1, y1);

    x = y1;
    y = x1 - y1 * (a / b);

    return gcd;
}

int modInverse(int a, int m) {
    int x, y;
    int g = extendedgcd(a, m, x, y);

    if (g != 1) {
        return -1; 
    }

    return (x % m + m) % m;
}

vector<int> LinCongr(int a, int b, int m) {
    int x, y;
    int g = extendedgcd(a, m, x, y);

    vector<int> solutions;

    if (b % g != 0) { 
        return solutions; 
    } 

    int a1 = a / g;
    int b1 = b / g;
    int m1 = m / g;

    int inv = modInverse(a1, m1);

    int x0 = (inv * b1) % m1;

    for (int i = 0; i < g; i++) {
        solutions.push_back((x0 + i * m1) % m);
    }

    return solutions;
}