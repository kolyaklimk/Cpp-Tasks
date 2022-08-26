//Лабораторная 7, задача 4. Выполнена: Климкович Н. В.

/*Осуществить сложение и вычитание чисел в заданной системе
счисления. В другую систему счисления не переводить. В системах
счисления больших десятичной использовать буквы по аналогии с
шестнадцатеричной системой. Разработать функции для выполнения
операции сложения и функции для выполнения операции вычитания.
Предусмотреть ввод положительных и отрицательных чисел.

https://matworld.ru/calculator/perevod-chisel.php
https://poschitat.online/shestnadcaterichnyi-kalkulyator
https://planetcalc.ru/2096/
https://calculatori.ru/slozhenie.html

9) в одиннадцатеричной*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

void swap_cod(string& dva) {
	for (int j = 0, j1 = dva.length() - 1; j < dva.length() / 2; j++, j1--)
		swap(dva[j], dva[j1]);
}

bool cin_string(string& s, char* minus) {
	getline(cin, s);
	int p = 0;

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
		}
		while (p > 1) {
			cout << "Incorrect value\n";
			return 0;
		}
	}
	for (int e = 0; e < s.length(); e++) {
		while ((s[e] < '0' || s[e]>'9') && s[e] != '.' && s[e] != 'A') {
			cout << "Incorrect value\n";
			return 0;
		}
	}
	return 1;
}

bool cin_to_dop(string& s) {
	char minus[] = "0";

	if (!cin_string(s, minus)) return 0;
	if (minus[0]=='1') s = '-' + s;
	return 1;
}

string summa(string dva, string dva2) {
	string s;

	swap_cod(dva);
	swap_cod(dva2);

	dva.erase(10, 1);
	dva2.erase(10, 1);
	dva += '0';
	dva2 += '0';
	if (dva.length() > dva2.length())
		for (int y = 0, y1 = dva.length() - dva2.length(); y < y1; y++)
			dva2 += '0';
	if (dva.length() < dva2.length())
		for (int y = 0, y1 = dva2.length() - dva.length(); y < y1; y++)
			dva += '0';

	int c, t = 0, dv, dv2;
	s = "";
	for (int y = 0; y < dva.length(); y++) {
		if (dva[y] == 'A') dv = 10;
		else dv = dva[y] - '0';
		if (dva2[y] == 'A') dv2 = 10;
		else dv2 = dva2[y] - '0';
		c = dv + dv2+t;
		if (c < 10) {
			s += c + '0';
			t = 0;
			continue;
		}
		if (c == 10) {
			s += 'A';
			t = 0;
			continue;
		}
		c--;
		if (c > 10) {
			s += c + '0'-10;
			t = 1;
			continue;
		}
		if (c == 10) {
			s += '0';
			t = 1;
			continue;
		}
	}
	s.insert(10, ".");
	swap_cod(s);
	while (s[0] == '0') s.erase(0, 1);
	if (s[0]=='.') s.insert(0, "0");
	return s;
}

string subtraction(string dva, string dva2) {
	string s;

	swap_cod(dva);
	swap_cod(dva2);

	dva.erase(10, 1);
	dva2.erase(10, 1);
	dva += '0';
	dva2 += '0';
	if (dva.length() > dva2.length())
		for (int y = 0, y1 = dva.length() - dva2.length(); y < y1; y++)
			dva2 += '0';
	if (dva.length() < dva2.length())
		for (int y = 0, y1 = dva2.length() - dva.length(); y < y1; y++)
			dva += '0';

	int c, t = 0, dv, dv2;
	s = "";
	for (int y = 0; y < dva.length(); y++) {
		if (dva[y] == 'A') dv = 10;
		else dv = dva[y] - '0';
		if (dva2[y] == 'A') dv2 = 10;
		else dv2 = dva2[y] - '0';
		c = dv - dv2 - t;
		if (c >= 0) {
			s += c + '0';
			t = 0;
			continue;
		}
		else c = 11 + c;
		if (c == 10) {
			s += 'A';
			t = 1;
			continue;
		}
		if (c >=0) {
			s += c + '0';
			t = 1;
			continue;
		}
	}
	s.insert(10, ".");
	swap_cod(s);
	while (s[0] == '0') s.erase(0, 1);
	if (s[0] == '.') s.insert(0, "0");
	return s;
}

int main() {
	string s, s3, s2;

	if (!cin_to_dop(s)) return 0;
	if (!cin_to_dop(s2)) return 0;
	s3 = summa(s, s2);
	cout << "\nSum: " << s3; 
	s3 = subtraction(s, s2);
	cout << "\n\nSubtraction: " << s3;
}