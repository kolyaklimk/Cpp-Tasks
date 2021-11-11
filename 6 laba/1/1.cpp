//Лабораторная 6, задача 1. Выполнена: Климкович Н. В.

/*Дана строка символов, состоящая из цифр, разделенных пробелами. 
Вывести на экран числа этой строки в порядке возрастания их значений.*/

#include <iostream>
#include <string>
using namespace std;

int main() {
	int i, u, q, g,q1, min, w = 0;
	double sum, t;
	string s1;
	getline(cin, s1);
	while (s1.length() > 80) getline(cin, s1);
	s1 += ' ';
    int l = s1.length() ;
	char* s = new char[l];
	s1.copy(s, l, 0);
	for (i = 0; i < l; i++)
		if (s[i] < '0' || s[i] > '9')
			s[i] = ' ';
	double* r = (double*)malloc(w * sizeof(double));
	for (i = 0; i < l;) {
		while (s[i] < '0' || s[i] > '9') i++;
		u = 1;
		g = i;
		while (s[i + 1] != ' ' && i < l) {
			i++;
			u++;
		}
		i = g;
		t = 1;
		sum = 0;
		for (q = u + i - 1; q >= i; q--) {
			sum += (s[q] - '0') * t;
			t *= 10;
		}
		r = (double*)realloc(r, ++w * sizeof(double));
		r[w - 1] = sum;
		i += u+1;
	}
	for (i = 0; i < w; i++) {
		min = r[i];
		q1 = i;
		for (q = i; q < w; q++)
			if (min > r[q]) {
				min = r[q];
				q1 = q;
			}
		swap(r[i], r[q1]);
	}
	for (i = 0; i < w; i++)
		cout << r[i] << " ";
}