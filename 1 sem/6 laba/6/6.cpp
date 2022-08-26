//Лабораторная 6, задача 6. Выполнена: Климкович Н. В.

/*Анаграммой слова называется любая перестановка всех букв слова.
Например, из слова SOLO можно получить 12 анаграмм: SOLO, LOSO,
OSLO, OLSO, OSOL, OLOS, SLOO, LSOO, OOLS, OOSL, LOOS,
SOOL.
Напишите программу, которая выводит количество различных
анаграмм, которые могут получиться из этого слова.*/

#include <iostream>
#include <string>
using namespace std;

int rec(string& st, int d, int& i) {
	if (st[i] != st[i + 1]) return 1;
	int b = 0;
	if (st[i] == st[i + 1]) b++;
	i++;
	return b + rec(st, d, i);
}

double fact(int a) {
	if (a == 1) return 1;
	return a * fact(a - 1);
}

int main() {
	string st;
	bool t = 0;
	int d, i, q1, b;
	double an;
	char buf = 0, min;
	for (;;) {
		getline(cin, st);
		d = st.length();
		if (d > 14) {
			cout << "\nString > 14 words, try again\n";
			continue;
		}
		for (int e = 0; e < d; e++)
			if (st[e] < 'A' || st[e] > 'Z' && st[e] < 'a' || st[e] > 'z') t++;
		if (t) {
			cout << "\nTry again\n";
			t = 0;
			continue;
		}
		break;
	}

	//сортировка
	for (int i = 0; i < d; i++) {
		min = st[i];
		q1 = i;
		for (int q = i; q < d; q++)
			if (min > st[q]) {
				min = st[q];
				q1 = q;
			}
		swap(st[i], st[q1]);
	}

	an = fact(d);
	for (int i = 0; i < d; i++)
		an /= fact(rec(st, d, i));

	cout << an;
}