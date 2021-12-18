//Лабораторная 7, задача 3. Выполнена: Климкович Н. В.

/*Осуществить сложение чисел. Разработать функции для
выполнения операции сложения. Предусмотреть ввод положительных и
отрицательных чисел.

9. Найдите сумму двоичных чисел, заданных в естественной форме.
Сложение выполните в дополнительном коде. Ответ выразите в прямом
коде.*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void swap_cod(string& dva) {
	for (int j = 0, j1 = dva.length() - 1; j < dva.length() / 2; j++, j1--)
		swap(dva[j], dva[j1]);
}

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

	swap_cod(dva);

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

bool cin_string(string& s, char* minus, int p, bool& dot) {
	getline(cin, s);

	if (s.find('.') == -1) {
		s.insert(s.length(), ".");
		s.insert(s.length(), "0000000000");
	}

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
		while ((s[e] < '0' || s[e]>'9') && s[e] != '.') {
			cout << "Incorrect value\n";
			return 0;
		}
	}
	return 1;
}

string dop_code(string dva, char* minus) {
	if (minus[0] == '0') return dva;
	string s,s2;
	int tt = 0, z;
	if (dva[1]==',') {
		tt = 1;
		if (dva[0]) z = 1;
		else z = 0;
		dva.erase(0, 2);
	}
	swap_cod(dva);
	dva.erase(10, 1);
	s += '1';

	int dot = 10;
	if (dva.find('1') > 9)dva.erase(0, 10);
	else {
		dot = dva.find('1');
		dva.erase(0, dot);
	}

	for (int y = 0; y < dva.length(); y++) {
		if (dva[y] == '0') dva[y] = '1';
		else dva[y] = '0';
	}

	for (int y = 0, n = 0; y < dva.length(); y++) {
		s += '0';
		n = 1;
	}

	int c;
	bool t = 0;
	for (int y = 0; y < dva.length(); y++) {
		c = dva[y] + s[y] - 2 * '0' + t;
		if (c < 2) {
			s2 += c + '0';
			t = 0;
		}
		else {
			s2 += '0';
			t = 1;
		}
	}
	s = "";
	for (int y = 0; y < dot; y++) s += '0';
	s2 = s + s2;
	s2.insert(10, ".");
	swap_cod(s2);
	if (tt) {
		if (z) s2.insert(0, "1");
		else s2.insert(0, "0");
		s2.insert(1, ",");
	}
	return s2;
}

bool cin_to_dop(string& s, string& dva) {
	bool dot = 0;
	char minus[] = "0";

	if (!cin_string(s, minus, 0, dot)) return 0;
	dva = after_dot(s, s, dva);
	dva = dop_code(dva, minus);
	dva.insert(0, minus);
	dva.insert(1, ",");
	return 1;
}

string summa(string dva, string dva2) {
	string s;
	dva.erase(1, 1);
	dva2.erase(1, 1);

	swap_cod(dva);
	swap_cod(dva2);

	dva.erase(10, 1);
	dva2.erase(10, 1);

	if (dva.length() > dva2.length())
		for (int y = 0, y1 = dva.length() - dva2.length(); y < y1; y++)
			dva2 += '0';
	if (dva.length() < dva2.length())
		for (int y = 0, y1 = dva2.length() - dva.length(); y < y1; y++)
			dva += '0';

	bool t = 0;
	int c;
	s = "";
	for (int y = 0; y < dva.length(); y++) {
		c = dva[y] + dva2[y] - 2 * '0' + t;
		switch (c) {
		case 2:
			s += '0';
			t = 1; break;
		case 3:
			s += '1';
			t = 1; break;
		default:
			s += c + '0';
			t = 0; break;
		}
	}
	s.insert(10, ".");
	swap_cod(s);
	s.insert(1, ",");
	return s;
}

int main() {
	string s, dva, s2, dva2;

	if (!cin_to_dop(s, dva)) return 0;
	if (!cin_to_dop(s2, dva2)) return 0;
	s = summa(dva, dva2);
	char minus[2];
	minus[0] = s[0];
	s = dop_code(s, minus);
	cout << s << '\n';
}