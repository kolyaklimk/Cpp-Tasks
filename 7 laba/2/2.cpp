//Лабораторная 7, задача 2. Выполнена: Климкович Н. В.

/*Перевести числа. Предусмотреть ввод положительных и
отрицательных чисел.

9. Из естественной формы в прямой код*/

#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int main()
{
	string s;
	long double ten, size;
	bool buf = 0;
	int w = 1, size2, size3, buff;
	char c[5], minus[] = "0";
	long double* r = (long double*)malloc(w * sizeof(long double));
	r[w - 1] = 0;
	while (cin.peek() != '\n') {
		for (int y = 4; y >= 0; y--) c[y]=' ';
		ten = 1;
		cin.get(c, 5);
		for (int y = 3; y >= 0; y--) {
			if (c[y] == '-') {
				minus[0] = '1';
				continue;
			}
			if (c[y] == ' ' || c[y] == '\0' || c[y]=='-') continue;
			if (w != 1 && c[y] == '0') {
				r[w - 2] *= 10;
				continue;
			}
			r[w - 1] += (c[y] - '0') * ten;
			ten *= 10;
		 }
		r = (long double*)realloc(r, ++w * sizeof(long double));
		r[w - 1] = 0;
	}
	//for (int y = 0; y < w-1; y++) cout  << r[y] << " ";
	//cout << "\n\n";

	for (;;) {
		for (int y = 0; y < w - 1; y++) {
			if (!r[y]) {
				buf = 0;
				continue;
			}

			size = r[y];
			size2 = 0;
			while (size >= 1) {
				size /= 10;
				size2++;
			}
			if (buf) r[y] += pow(10, size2);

			buf = fmod(r[y], 2);

			r[y] = trunc(r[y]/2);

			size = r[y];
			size3 = 0;
			while (size >= 1) {
				size /= 10;
				size3++;
			}

			buff = 0;
			if (size3 < size2 && y != 0) r[y-1] *= 10;
			if (y == w - 2) {
				s += buf + '0';
				buf = 0;
			}
		}
		for (int kk = w - 2; kk > 0; kk--)
			if (r[kk] == 0 && r[kk - 1] != 0)
				for (int k = kk; k > 0; k--)
					r[k] = r[k - 1];
		//for (int y = 0; y < w - 1; y++) cout << r[y] << ' ';
		//cout << "\n" << s << "\n\n\n";
		if (r[w - 2] == 1 && r[w - 3] == 0 && r[0] == 0) {
			s += '1';
			break;
		}
		if (r[w - 2] == 0) break;
	}

	for (int j = 0, j1 = s.length() - 1; j < s.length() / 2; j++, j1--)
		swap(s[j], s[j1]);
	s.insert(0, minus);
	s.insert(1, ".");
	cout << s;
}