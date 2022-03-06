//Лабораторная 6, задача 3. Выполнена: Климкович Н. В.

/* Ввести массив строк. В функции для каждой строки
проверить, является она симметричной или нет. (Симметричной считается
строка, которая одинаково читается слева направо и справа налево).
Вывести на экран саму строку и результат её обработки. Стандартных
функций работы со строками не использовать. */

#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int w = 1, w1 = 1, p = 0, st_ = 1, b = 0;

	//кол-во строк
	int* st = (int*)malloc(st_ * sizeof(int));

	char** s = (char**)malloc(w * sizeof(char*));
	s[w - 1] = (char*)malloc(w1 * sizeof(char));

	while (cin.get(s[w - 1][w1-1])) {
		if (cin.peek() != '\n') p = 0;

		if (p) {
			free(s[w - 1]);
			break;
		}

		if (cin.peek() == '\n') {
			p++; 
			
			if (w - 1 == 0) {
				s[0] = (char*)realloc(s[0], ++w1 * sizeof(char));
				for (int i = w1 - 1; i > 0; i--)
					s[0][i] = s[0][i - 1];
				s[0][0] = '\n';
			}

			st[st_ - 1] = w1;

			st = (int*)realloc(st, ++st_ * sizeof(int));

			w1 = 1;
			s = (char**)realloc(s, ++w * sizeof(char*));
			s[w - 1] = (char*)malloc(w1 * sizeof(char));
			continue;
		}

		s[w - 1] = (char*)realloc(s[w - 1], ++w1 * sizeof(char));
	}

	for (int i = 0, st1 = 0; i < w-1; i++, st1++) {

		char* buf = new char[st[st1]];
		
		for (int j = 1, j1 = st[st1] - 1; j < st[st1]; j++, j1--)
			buf[j1] = s[i][j];

		for (int j = 1, j1 = 0; j < st[st1]; j++, j1++) {
			if (buf[j] == s[i][j]) continue;
			else b++;
		}

		if (b) {
			b = 0;
			cout << i + 1 << " строка является не симметричной\n";
		}
		else  cout << i + 1 << " строка является симметричной\n";

		delete[] buf;
	}

	free(st);
	for (int i = 0; i < w-1; i++)
		free(s[i]);
	free(s);
}