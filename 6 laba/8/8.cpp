﻿//Лабораторная 6, задача 8. Выполнена: Климкович Н. В.

/*У вас есть строка s и фишка, которую вы можете поставить на любой символ
этой строки.
После того, как вы поставите фишку, вы можете подвинуть ее вправо
несколько (возможно, ноль) раз, то есть сделать следующее действие
несколько раз: если текущая позиция фишки обозначена как i, фишка
перемещается в позицию i+1. Конечно же, это действие невозможно, если
фишка находится в последней позиции строки.
После того, как вы закончите двигать фишку вправо, вы можете подвинуть ее
влево несколько (возможно, ноль) раз, то есть сделать следующее действие
несколько раз: если текущая позиция фишки обозначена как i, фишка
перемещается в позицию i−1. Конечно же, это действие невозможно, если
фишка находится в первой позиции строки.
Когда вы ставите фишку или перемещаете ее, вы выписываете символ, на
котором оказалась фишка. Например, если строка s — abcdef, вы ставите
фишку на 3-й символ, двигаете ее вправо 2 раза, а затем двигаете ее влево 3
раза, вы выпишете строку cdedcb.
Вам даны две строки s и t. Ваше задание — определить, можно ли так
выполнить описанные операции со строкой s, что в результате вы выпишете
строку t.
Входные данные:
В первой строке задано одно целое число q (1≤q≤500) — количество наборов
входных данных.
Каждый набор входных данных состоит из двух строк. В первой строке
задана строка s (1≤|s|≤500), во второй строке — строка t (1≤|t|≤2⋅|s|−1). Обе
строки состоят из строчных букв латинского алфавита.
Гарантируется, что сумма |s| по всем наборам входных данных не
превосходит 500.
Выходные данные:
Для каждого набора выходных данных выведите «YES», если можно
выписать строку t, проводя описанные в условии действия со строкой s, или
«NO» в противном случае.
Каждую букву можно выводить в любом регистре (YES, yes, Yes будут
распознаны как положительный ответ, NO, no и nO будут распознаны как
отрицательный ответ).*/

#include <iostream>
#include <string>
using namespace std;
void search_r(string s, string t, int q, int r, int& y, int i) {
	if (q + 1 < s.length() && q >= 0 && !i && s[q + 1] == t[r]) {
		q++;
		r++;
		y++;
		return search_r(s, t, q, r, y, i);
	}
	else {
		if (q < s.length() && q - 1 >= 0 && s[q - 1] == t[r]) {
			q--;
			r++;
			y++;
			i++;
			return search_r(s, t, q, r, y, i);
		}
		else return;
	}
}
void search_l(string s, string t, int q, int r, int& y, int i) {
	if (q < s.length() && q - 1 >= 0 && s[q - 1] == t[r] && !i) {
		q--;
		r++;
		y++;
		return search_l(s, t, q, r, y, i);
	}
	else {
		if (q + 1 < s.length() && q >= 0 && s[q + 1] == t[r]) {
			q++;
			r++;
			y++;
			i++;
			return search_l(s, t, q, r, y, i);
		}
		else return;
	}
}

int main() {
	string s,t;
	int q, r = 0, y = 0, y1, v;
	cin >> v;
	while (cin.fail() || v < 1 || v > 500) {
		cin.clear();
		cin.ignore(9999, '\n');
		cin >> v;
	}
	cin.clear();
	cin.ignore(9999, '\n');

	for (int d = 0; d < v; d++) {
		getline(cin, s);
		while (s.length() < 1 || s.length() > 500)
			getline(cin, s);
		getline(cin, t);
		while (t.length() < 1 || t.length() > s.length() * 2 - 1)
			getline(cin, t);
		y1 = 0;
		for (q = 0; q < s.length(); q++) {
			if (s[q] == t[r]) {
				r++;
				y = 1;
				search_r(s, t, q, r, y,0);
				if (y > y1) y1 = y;
				r = 1;
				y = 1;
				search_r(s, t, q, r, y, 0);
				if (y > y1) y1 = y;
				r = 0;
			}
		}

		if (y1 == t.length())cout << "YES\n\n";
		else cout << "NO\n\n";
	}
	return 0;
}