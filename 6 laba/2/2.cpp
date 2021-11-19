//Лабораторная 6, задача 2. Выполнена: Климкович Н. В.

/* Рассматривать строки как указатель типа char.
Найти, каких букв в тексте больше – гласных или согласных. */

#include <iostream>
#include <Windows.h>
using namespace std;

int main() {
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	//int i, q = 0, w = 0;
	char gl[21];
	strcpy(gl, "аиеёоуыэюяАИЕЁОУЫЭЮЯ");

	char s[81];
	cin.get(s, 81);


	/*
	for (i = 0; i < 81; i++) {

		if (s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'a' || s[i] == 'y' ||
			s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U' || s[i] == 'A' || s[i] == 'Y')
			q++;
		else
			if (s[i] >= 'a' && s[i] <= 'z' || s[i] >= 'A' && s[i] <= 'Z')
				w++;
	}
	if (q > 0 || w > 0) {
		if (q > w) cout << "\nГласных больше чем согласных";
		if (q < w) cout << "\nСогласных больше чем гласных";
	}
	else cout << "\nНет ни гласных, ни согласных";
	*/
}