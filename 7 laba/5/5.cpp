//Лабораторная 7, задача 5. Выполнена: Климкович Н. В.

/*Перевести число из арабской системы записи чисел в римскую*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void swap_cod(string& dva) {
	for (int j = 0, j1 = dva.length() - 1; j < dva.length() / 2; j++, j1--)
		swap(dva[j], dva[j1]);
}

void subtraction(string& dva, string dva2, string& s2, char f) {
	string s;
	swap_cod(dva);
	swap_cod(dva2);

	//cout << "\n\n" << dva;

	if (dva.length() > dva2.length())
		for (int y = 0, y1 = dva.length() - dva2.length(); y < y1; y++)
			dva2 += '0';
	if (dva.length() < dva2.length())
		for (int y = 0, y1 = dva2.length() - dva.length(); y < y1; y++)
			dva += '0';

	int c, t = 0, dv, dv2;
	for (int y = 0; y < dva.length(); y++) {
		dv = dva[y] - '0';
		dv2 = dva2[y] - '0';
		c = dv - dv2 - t;
		if (c >= 0) {
			s += c + '0';
			t = 0;
			continue;
		}
		else c = 10 + c;
		if (c >= 0) {
			s += c + '0';
			t = 1;
			continue;
		}
	}
	s2 += f;
	swap_cod(s);
	while (s[0] == '0') s.erase(0, 1);
	dva = s;
}

void change(string& s2) {
	swap_cod(s2);
	string buf = s2 + '0', buf2;
	int c = 1;
	for (int a = 0; a < buf.length(); a++) {
			cout << "\n\n" << buf;
		if (buf[a] == buf[a + 1]) {
			c++;
			continue;
		}
		else {
			if (c == 4) {
				buf2 += buf[a] - '0' + 1 + '0';
				buf2 += buf[a];
				buf.erase(0, c);
				a = -1;
				c = 1;
				continue;
			}
			if (c == 6) {
				buf2 += buf[a];
				buf2 += buf[a] - '0' +1 + '0';
				buf.erase(0, c);
				a = -1;
				c = 1;
				continue;
			}
			if (c == 7) {
				for (int l = 0; l < 2; l++) buf2 += buf[a];
				buf2 += buf[a] - '0' +1 + '0';
				buf.erase(0, c);
				a = -1;
				c = 1;
				continue;
			}
			if (c == 8) {
				for (int l = 0; l < 3; l++) buf2 += buf[a];
				buf2 += buf[a] - '0' + 1 + '0';
				buf.erase(0, c);
				a = -1;
				c = 1;
				continue;
			}
			if (c == 9) {
				buf2 += buf[a] - '0' + 1 + '0';
				buf2 += buf[a];
				buf.erase(0, c);
				a = -1;
				c = 1;
				continue;
			}
			for (int y = 0; y < c; y++) buf2 += buf[y];
			buf.erase(0, c);
			a = -1;
			c = 1;
		}
	}
	s2 = buf2;
	swap_cod(s2);
}

void change2(string& s2) {
	string buf;
	for (int a = 0; a < s2.length(); a++) {
		switch (s2[a] - '0') {
		case 1: buf += 'I'; break;
		case 2: buf += 'V'; break;
		case 3: buf += 'X'; break;
		case 4: buf += 'L'; break;
		case 5: buf += 'C'; break;
		case 6: buf += 'D'; break;
		case 7: buf += 'M'; break;
		}
	}
	s2 = buf;
}

int main() {
	string s, s2;

	getline(cin, s);
	for (int e = 0; e < s.length(); e++)
		while (s[e] < '0' || s[e]>'9') {
			cout << "Incorrect value\n";
			return 0;
		}

	while (s.length() > 3) subtraction(s, "1000", s2, '7');
	while (s.length() == 3 && (s[0] - '0') % 5 == 0) subtraction(s, "500", s2, '6');
	while (s.length() == 3) subtraction(s, "100", s2, '5');
	while (s.length() == 2 && (s[0] - '0') % 5 == 0) subtraction(s, "50", s2, '4');
	while (s.length() == 2) subtraction(s, "10", s2, '3');
	while ((s[0] - '0') % 5 == 0) subtraction(s, "5", s2, '2');
	while (s.length()) subtraction(s, "1", s2, '1');
	cout << "\n\n" << s2;
	change(s2);
	cout << "\n\n\n" << s2<< "\n\n";
	change2(s2);
	cout << "\n\n" << s2;
}