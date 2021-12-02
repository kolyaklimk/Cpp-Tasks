//Лабораторная 6, задача 9. Выполнена: Климкович Н. В.

/*Сумма чисел в строке
В заданной строке, состоящей из букв, цифр и прочих символов, найдите
сумму всех чисел.*/

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	int i, u, q, g, o = 1;
	double sum, t, sum1 = 0;
	getline(cin, s);

	//замена "лишнего" на пробел
	for (i = 0; i < s.length(); i++)
		if ((s[i] < '0' || s[i] > '9') && s[i] !='-')
			s[i] = ' ';
	s += ' ';
	for (i = 0; i < s.length(); i++)
		if (s[i] == '-' && s[i+1] == ' ')
			s[i] = ' ';
	cout << s;
	for (i = 0; i < s.length();) {
		while (s[i] == ' ' && i + 1 < s.length()) i++;
		if (i + 1 == s.length()) break;
		u = 1;
		g = i;
		while (s[i + 1] != ' ' && s[i + 1] != '-' && i + 1 < s.length()) {
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
		sum1 += sum * o;
		o = 1;
		i += u + 1;
	}
	cout << sum1;
}