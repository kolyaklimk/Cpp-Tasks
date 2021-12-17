//Лабораторная 7, задача 8. Выполнена: Климкович Н. В.

/*Брюс недавно получил работу в NEERC (Numeric Expression Engineering &
Research Center), где изучают и строят много различных любопытных
чисел. Его первым заданием стало исследование двудесятичных чисел.
Натуральное число называется двудесятичным, если его десятичное
представление является суффиксом его двоичного представления; и
двоичное и десятичное представление рассматривается без ведущих
нулей. Например, 1010 = 10102, так что 10 двудесятичное число. Числа
101010 = 11111100102 и 4210 = 1010102 не являются двудесятичными.
Сначала Брюс хочет создать список двудесятичных чисел. Помогите
ему найти n-ое наименьшее двудесятичное число.*/

#include <iostream>
#include <string>
using namespace std;

void bin(int a, string& s) {
	int mx = 0;
	while ((a >> mx++) > 1);
	int num = a, bin;
	while (mx > 0) {
		bin = pow(2, --mx);
		if (num < bin) s += '0';
		else {
			s += '1';
			num -= bin;
		}
	}
}

int main() {
	int our = 0, n; 
	cin >> n;

	for (int i = 1; i <= 10000; ++i) {
		bool sa = 0;
		string bina, dig = to_string(i);
		bin(i, bina);

		for (int j = 0; bina != dig; ++j) {
			if (bina.length() == 0) break;
			bina.erase(0, 1);
		}

		if (bina.length()) sa = 1;
		if (sa) ++our; 
		if (our == n) { 
			cout << i; 
			break; 
		}
	}
}