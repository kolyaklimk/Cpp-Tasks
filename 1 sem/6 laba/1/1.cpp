//Лабораторная 6, задача 1. Выполнена: Климкович Н. В.

/*Дана строка символов, состоящая из цифр, разделенных пробелами. 
Вывести на экран числа этой строки в порядке возрастания их значений.*/

#include <iostream>
using namespace std;

int main() {
	int i, u, q, g,q1, min, w = 0, o = 1;
	double sum, t;
	char s[81];
	cin.get(s, 81);

	//замена "лишнего" на пробел
	for (i = 0; i < 80; i++)
		if ((s[i] < '0' || s[i] > '9') && s[i] != '-')
			s[i] = ' ';
	for (i = 0; i < 80; i++)
		if (s[i] == '-' && (s[i+1] < '0' || s[i+1] > '9'))
			s[i] = ' ';

	double* r = (double*)malloc(w * sizeof(double));
	for (i = 0; i < 80;) {
		while (s[i] == ' ' && i + 1 < 80) i++;
		if (i + 1 == 80) break;
		u = 1;
		g = i;
		while (s[i + 1] != ' ' && s[i + 1] != '-' && i+1 < 80) {
			i++;
			u++;
		}
		i = g;
		t = 1;
		sum = 0;
		if (s[i] == '-') {
			i++;
			o = -1;
			u--;
		}
		for (q = u + i - 1; q >= i; q--) {
			sum += (s[q] - '0') * t;
			t *= 10;
		}
		r = (double*)realloc(r, ++w * sizeof(double));
		r[w - 1] = sum*o;
		o = 1;
		i += u+1;
	}
	
	//сортировка
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
	free(r);
}