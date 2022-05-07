//task 8 lab 7 Created by Bahdanau 153502
#include <iostream>
#include "MyVector.h"
#include <algorithm>
#define vector Vector
using namespace std;

void Normalize(vector<int>& c) {
    for (int i = 0; i < c.size() - 1; ++i) {
        c[i + 1] += c[i] >> 1;
        c[i] &= 1;
    }
}

void AddZero(vector<int>& c, int x) {
    c.resize(x + 1);
    c[x] = 0;
}

vector<int> AddNum(const vector<int>& a, const vector<int>& b, int k) {

    vector<int> c(max(a.size(), b.size()) + 1);

    for (int i = 0; i < c.size(); ++i) {
        if (i < a.size()) {
            c[i] += a[i];
        }
        if (i < b.size()) {
            c[i] += b[i];
        }
    }

    Normalize(c);
    AddZero(c, k);

    return c;
}

int GetBit(const vector<int>& v, int b) {
    return v[b] & 1;
}

vector<int> Multiply(const vector<int>& a, int x, int k) {

    vector<int> b = a;
    b.push_back(0);

    for (int i = 0; i < b.size(); ++i) {
        b[i] *= x;
    }

    Normalize(b);
    AddZero(b, k);

    return b;
}

void GenerateSequence(vector<int> n, const vector<vector<int>>& p, int k, int i, vector<pair<int, vector<int>> >& v) {

    if (i == k) {
        n.resize(k + 1);
        if (GetBit(n, k)) {
            v.push_back(make_pair(k, n));
        }
        return;
    }

    if (GetBit(n, i)) {
        return;
    }

    GenerateSequence(n, p, k, i + 1, v);

    if (i) {
        GenerateSequence(AddNum(n, p[i], k + 1), p, k, i + 1, v);
    }
    return;
}


void reversee(vector<int>& v) {
    for (int a = 0; a <= v.size() / 2 + v.size() % 2; a++) {
        std::swap(v[a], v[v.size() - a - 1]);
    }
}

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << "1";
        return 0;
    }
    --n;

    vector<pair<int, vector<int>>> sequence;

    for (int k = 1; n / 2 >= sequence.size(); ++k) {
        vector<int> a(k + 1);
        a[k] = 1;
        vector<vector<int>> b(k + 1);
        b[0].push_back(1);
        AddZero(b[0], k + 1);
        for (int i = 0; i < k; ++i) {
            b[i + 1] = Multiply(b[i], 10, k + 1);
        }
        GenerateSequence(a, b, k, 0, sequence);
    }

    for (int i = 0; i < sequence.size(); ++i) {
        reversee(sequence[i].second);
    }
    //sort(sequence.begin(), sequence.end());
    //cout << &sequence[0] << endl;
    --n;
    vector<int> answer = sequence[n / 2].second;
    reversee(answer);
    if (n % 2) {
        answer[0] ^= 1;
    }
    for (int k = sequence[n / 2].first; k >= 0; --k) {
        cout << GetBit(answer, k);
    }
    return 0;
}
