//Лабораторная 6, задача 9. Выполнена: Климкович Н. В.

/*Сумма чисел в строке
В заданной строке, состоящей из букв, цифр и прочих символов, найдите
сумму всех чисел.*/

#include <iostream>
#include <string>
using namespace std;

int main() {
	string s;
	double c = 0, fra, ex, sum = 0, tmp;
	bool min, exMin;
	getline(cin, s);

	while (c < s.length()) {
		min = false;
		if (isdigit(s[c])) {
			if (c != 0 && s[c - 1] == '-'){
				tmp = s[c] - '0';
				min = true;
			}
			else tmp = s[c] - '0';
			++c;

			while (isdigit(s[c])) {
				tmp = tmp * 10 + (s[c] - '0');
				++c;
			}

			fra = 1;
			if (s[c] == '.' && isdigit(s[c + 1])) {
				++c;
				while (isdigit(s[c])) {
					fra *= 10;
					tmp = tmp + (long double)(s[c] - '0') / fra;
					++c;
				}
			}

			if ((s[c] == 'e' || s[c] == 'E') && (isdigit(s[c + 1]) ||
				(s[c + 1] == '+' && isdigit(s[c + 2])) || (s[c + 1] == '-' && isdigit(s[c + 2])))) {
				exMin = false;
				++c;
				if (s[c] == '-') {
					exMin = true;
					++c;
				}
				else if (s[c] == '+') ++c;
				ex = s[c] - '0';
				++c;
				while (isdigit(s[c])) {
					ex = ex * 10 + (s[c] - '0');
					++c;
				}
				if (exMin) ex *= -1;
				tmp *= pow(10, ex);
			}
			if (min) tmp *= -1;

			sum += tmp;
		}
		++c;
	}
	cout << sum;
}