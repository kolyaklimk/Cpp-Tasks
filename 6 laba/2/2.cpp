//Лабораторная 6, задача 2. Выполнена: Климкович Н. В.

/* Рассматривать строки как указатель типа char.
Найти, каких букв в тексте больше – гласных или согласных. */

#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int w = 1, gl_ = 0, sog = 0;
	char gl[21] = "аиеёоуыэюяАИЕЁОУЫЭЮЯ";

	char* s = (char*)malloc(w * sizeof(char));
	while (cin >> s[w - 1]) {
		if (cin.peek() == '\n') break;
		s = (char*)realloc(s, ++w * sizeof(char));
	}

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < 21; j++)
			if (gl[j] == s[i]) {
				gl_++;
				break;
			}
		if (s[i] > 'а' && s[i] < 'я' || s[i]>'А' && s[i] < 'Я') sog++;
	}

	for (int i = 0; i < w; i++)
		cout << s[i];

	if (sog > 0 || gl_ > 0) {
		if (gl_ > sog) cout << "\nГласных больше чем согласных";
		if (gl_ < sog) cout << "\nСогласных больше чем гласных";
		if (gl_ == sog) cout << "\nСогласных = гласных";
	}
	else cout << "\nНет ни гласных, ни согласных";
}