//Лабораторная 7, задача 2. Выполнена: Климкович Н. В.

/*Перевести числа. Предусмотреть ввод положительных и
отрицательных чисел.

9. Из естественной формы в прямой код*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

string to_dva(string s, string dva, int t, int k, int c) {
	for (;;) {
		for (int u = 0; u < s.length() - 1; u++) {
			if (s[u] == '0') {
				k = 0;
			}
			else {
				k = 1;
				break;
			}
		}
		if (s[s.length() - 1] == '1' && !k) {
			dva += '1';
			break;
		}
		if (s[s.length() - 1] == '0' && !k) {
			dva += '0';
			break;
		}

		for (int e = 0; e < s.length(); e++) {
			c = s[e] - '0';
			if (c % 2) {
				c = (c + t * 10) / 2;
				s[e] = c + '0';
				t = 1;
			}
			else {
				c = (c + t * 10) / 2;
				s[e] = c + '0';
				t = 0;
			}
			if (e == s.length() - 1) {
				if (t) dva += '1';
				else  dva += '0';
				t = 0;
			}
		}
	}

	for (int j = 0, j1 = dva.length() - 1; j < dva.length() / 2; j++, j1--)
		swap(dva[j], dva[j1]);

	return dva;
}

string after_dot(string s, string s2, string dva) {
	s2.erase(0, s2.find('.') + 1);
	if (s2.length() > 10) s2.erase(8, s2.length() - 1);
	s.erase(s.find('.'), s.length());
	dva = to_dva(s, dva, 0, 0, 0);
	dva += '.';
	int size = s2.length() - 1;
	double dota = 0;
	for (int d = 0; d < s2.length(); d++) dota += pow(10, size--) * (s2[d] - '0');
	size = s2.length();
	for (int d = 0; d < 10; d++) {
		dota *= 2;
		if (dota - pow(10, size) > 0) {
			dva += '1';
			dota -= pow(10, size);
		}
		else dva += '0';
	}
	return dva;
}

int main() {
	string s, dva, s2;
	int p = 0;
	bool dot = 0;
	char minus[] = "0";
	getline(cin, s);

	if (s[0] == '-') {
		minus[0] = '1';
		s.erase(0, 1);
	}

	for (int e = 0; e < s.length(); e++) {
		if (s[e] == '.' || s[0] == '.' || s[s.length() - 1] == '.') {
			p++;
			dot++;
		}
		while (p > 1) {
			cout << "Incorrect value\n";
			return 0;
		}
	}

	for (int e = 0; e < s.length(); e++) {
		while ((s[e] < '0' || s[e]>'9') && s[e]!='.') {
			cout << "Incorrect value\n";
			return 0;
		}
	}

	if (!dot) dva = to_dva(s, dva, 0, 0, 0);
	else dva = after_dot(s,s,dva);

	dva.insert(0, minus);
	dva.insert(1, ",");

	cout << dva;
}