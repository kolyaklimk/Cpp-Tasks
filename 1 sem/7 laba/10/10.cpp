﻿//Лабораторная 7, задача 10. Выполнена: Климкович Н. В.

/* Патриций решил устроить праздник и для этого приготовил 240
бочек вина. Однако к нему пробрался недоброжелатель, который подсыпал
яд в одну из бочек. Недоброжелателя тут же поймали, дальнейшая его судьба
неизвестна. Про яд известно, что человек, который его выпил, умирает в
течение 24 часов. До праздника осталось два дня, то есть 48 часов. У
патриция есть пять рабов, которыми он готов пожертвовать, чтобы узнать, в
какой именно бочке яд. Каким образом можно это узнать?*/

#include <iostream>
using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	int t, g, bochka;
	cout << "Время смерти(мин): ";
	cin >> t;
	cout << "раб: ";
	cin >> g;
	while (cin.fail() || t < 1 || t > 1440 || g < 1 || g > 5) {
		cin.clear();
		cin.ignore(9999, '\n');
		cout << "Время смерти(мин): ";
		cin >> t;
		cout << "раб: ";
		cin >> g;
	}
	if (g == 1) {
		t /= 30;
		bochka = t;
		cout << bochka;
	}
	if (g == 2) {
		t /= 30;
		bochka = t + 48;
		cout << bochka;
	}
	if (g == 3) {
		t /= 30;
		bochka = t + 96;
		cout << bochka;
	}
	if (g == 4) {
		t /= 30;
		bochka = t + 144;
		cout << bochka;
	}
	if (g == 5) {
		t /= 30;
		bochka = t + 192;
		cout << bochka;
	}
}