//Лабораторная 8, задача 2. Выполнена: Климкович Н. В.

/*Разработать программу в соответствии с вариантом,
реализующую работу с файлами в консольном приложении.
Информация, обрабатываемая программой, должна храниться
в файле, результат работы занести в другой файл и отобразить на экране.
Использовать динамический массив структур, содержащий поля согласно
варианту индивидуального задания. Выделение памяти реализовать через
calloc.
Программа должна содержать необходимые комментарии.
Следует предусмотреть простейший вывод на экран входных и выходных
данных. В каждом варианте задания реализовать следующие функции
для работы со структурой: инициализации данных, добавления,
удаления, корректировки и просмотра записей файла.


Вариант 9: Для книг, хранящихся в библиотеке, задаются: регистрационный
номер книги, автор, название, год издания, издательство, количество
страниц. Вывести список книг с фамилиями авторов в алфавитном порядке,
изданных после заданного года.*/

#include <fstream>
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;

void clear_m() {
	cin.clear();
	cin.ignore(9999, '\n');
}
struct Bib {
	char register_cod[100];
	char author[100];
	char name_book[100];
	int year;
	char izd[100];
	int amount;
};
void cout_sss(Bib* ceh, int m) {
	ofstream file;
	file.open("txt.txt");
	file.is_open();
	for (int y = 0; y < m; y++)
		file << "Рег. номер: " << ceh[y].register_cod <<
		" Автор: " << ceh[y].author <<
		" Название: " << ceh[y].name_book <<
		" Год: " << ceh[y].year <<
		" Издательство: " << ceh[y].izd <<
		" Стр.: " << ceh[y].amount << '\n';
	file.close();
}
void cout_s(Bib* ceh, int m) {
	cout << '\n';
	for (int y = 0; y < m; y++)
		cout << "Рег. номер: " << ceh[y].register_cod <<
		" Автор: " << ceh[y].author <<
		" Название: " << ceh[y].name_book <<
		" Год: " << ceh[y].year <<
		" Издательство: " << ceh[y].izd <<
		" Стр.: " << ceh[y].amount << '\n';
	cout_sss(ceh, m);
}
void correct(Bib*& ceh, int m) {
	int d;
	char da[100];
	bool r = 0;
	clear_m();
	cout << "\nРегистрационный номер книги для удаления (0=назад): ";
	cin.get(da, 100);
	while (da[0] == '\0') {
		clear_m();
		cout << "Введите корректное значение: ";
		cin.get(da, 100);
	}
	if (da[0] == '0' && da[1] == '\0') {
		return;
	}
	int h;
	for (h = 0; h < m; h++) {
		if (ceh[h].register_cod[0] == da[0]) {
			r = 1;
			d = h;
			break;
		}
	}
	if (!r) {
		cout << "В списке нет такого номера";
		return;
	}
	for (int j = 0; j < 100; j++) {
		if (ceh[h].register_cod[j] == '\0' && da[j] == '\0') break;
		if (ceh[h].register_cod[j] == da[j]) continue;
		else {
			cout << "В списке нет такого номера";
			return;
		}
	}
	cout << "\nЧто исправить?\n" <<
		"1 - регистрационный номер книги\n" <<
		"2 - автор\n" <<
		"3 - название\n" <<
		"4 - год издания\n" <<
		"5 - издательство\n" <<
		"6 - количество страниц\n" <<
		"7 - выход\n"; 
	int l;
	cin >> l;
	while (cin.fail() || l < 1 || l>7) {
		clear_m();
		cout << "\nВведите корректное значение: ";
		cin >> l;
	}
	switch (l)
	{
	case 1: cin >> ceh[d].register_cod; 
		if (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Введите корректное значение: ";
			cin >> ceh[d].register_cod;
		}break;
	case 2: cin >> ceh[d].author;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Введите корректное значение: ";
			cin >> ceh[d].author;
		}break;
	case 3: cin >> ceh[d].name_book;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Введите корректное значение: ";
			ceh[d].name_book;
		}break;
	case 4: cin >> ceh[d].year;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Введите корректное значение: ";
			cin >> ceh[d].year;
		}break;
	case 5: cin >> ceh[d].izd;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Введите корректное значение: ";
			cin >> ceh[d].izd;
		}break;
	case 6: cin >> ceh[d].amount;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Введите корректное значение: ";
			cin >> ceh[d].amount;
		}break;
	case 7: return; break;
	}
	cout_s(ceh, m);
}
void shekerSort(Bib* mass, int count, bool u) {
	Bib t;
	int left = 0, right = count - 1;
	int flag = 1;
	while ((left < right) && flag > 0)
	{
		flag = 0;
		for (int i = left; i < right; i++)
		{
			if (mass[i].author[0] > mass[i + 1].author[0])
			{
				t = mass[i];
				mass[i] = mass[i + 1];
				mass[i + 1] = t;
				flag = 1;
			}
		}
		right--;
		for (int i = right; i > left; i--)
		{
			if (mass[i - 1].author[0] > mass[i].author[0])
			{
				t = mass[i];
				mass[i] = mass[i - 1];
				mass[i - 1] = t;
				flag = 1;
			}
		}
		left++;
	}
	if (u) cout_s(mass, count);
}
void cin_s(Bib* ceh, int zero, int m) {
	char buf[10];
	for (int j = zero; j < m + zero;j++) {
		cout << "Рег номер: ";
		cin.getline(ceh[j].register_cod, 100);
		cout << "Автор: ";
		cin.getline(ceh[j].author, 100);
		cout << "Название: ";
		cin.getline(ceh[j].name_book, 100);
		cout << "Год: ";
		cin >> ceh[j].year;
		while (cin.fail()) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Введите корректное значение: ";
			cin >> ceh[j].year;
		}
		cin.clear();
		cin.ignore(9999, '\n');
		cout << "Издательство: ";
		cin.getline(ceh[j].izd, 100);
		cout << "Количество страниц: ";
		cin >> ceh[j].amount;
		while (cin.fail() || ceh[j].amount < 1) {
			cin.clear();
			cin.ignore(9999, '\n');
			cout << "Введите корректное значение: ";
			cin >> ceh[j].amount;
		}
		cin.clear();
		cin.ignore(9999, '\n');
	}
	cout_s(ceh, m);
}
void dop(Bib*& ceh, int& m) {
	int y = m;
	cout << "книш добавить: (0=назад): ";
	cin >> y;
	while (cin.fail() || y < 0) {
		clear_m();
		cout << "\nВведите корректное значение (0=назад): ";
		cin >> y;
	}
	cin.clear();
	cin.ignore(9999, '\n');
	if (y == 0) return;
	Bib* buf = (Bib*)calloc(m, sizeof(Bib));
	for (int u = 0; u < m; u++) {
		buf[u] = ceh[u];
	}
	free(ceh);
	ceh = (Bib*)calloc(m + y, sizeof(Bib));
	for (int u = 0; u < m; u++) {
		ceh[u] = buf[u];
	}
	free(buf);
	cin_s(ceh, m, y);
	m += y;
}
void delete_s(Bib*& ceh, int& m) {
	int d;
	char da[100];
	bool r = 0;
	clear_m();
	cout << "\nРегистрационный номер книги для удаления (0=назад): ";
	cin.get(da, 100);
	while (da[0] == '\0') {
		clear_m();
		cout << "Введите корректное значение: ";
		cin.get(da, 100);
	}
	if (da[0] == '0' && da[1] == '\0') {
		return;
	}
	int h;
	for (h = 0; h < m; h++) {
		if (ceh[h].register_cod[0] == da[0]) {
			r = 1;
			d = h;
			break;
		}
	}
	if (!r) {
		cout << "В списке нет такого номера";
		return;
	}
	for (int j = 0; j < 100; j++) {
		if (ceh[h].register_cod[j] == '\0' && da[j] == '\0') break;
		if (ceh[h].register_cod[j] == da[j]) continue;
		else {
			cout << "В списке нет такого номера";
			return;
		}
	}
	for (int u = d; u < m - 1; u++)
		ceh[u] = ceh[u + 1];

	Bib* buf = (Bib*)calloc(--m, sizeof(Bib));
	for (int u = 0; u < m; u++) {
		buf[u] = ceh[u];
	}
	free(ceh);
	ceh = (Bib*)calloc(m, sizeof(Bib));
	for (int u = 0; u < m; u++) {
		ceh[u] = buf[u];
	}
	free(buf);
	cout_s(ceh, m);
}
bool cin_ss(Bib*& ceh, int& m) {
	char buf[10];
	ifstream fin;
	fin.open("file.txt");
	if (!fin.is_open()){
		cout << "File open error\n";
		return 1;
	}
	
	fin >> m;
	if (fin.fail()) {
		fin.clear();
		fin.ignore(9999, '\n');
		fin.close();
		return 1;
	}
	fin.clear();
	fin.ignore(9999, '\n');
	ceh = (Bib*)calloc(m, sizeof(Bib));
	for (int j = 0; j < m && !fin.eof(); j++) {
		fin.getline(ceh[j].register_cod, 100);
		fin.getline(ceh[j].author, 100);
		fin.getline(ceh[j].name_book, 100);
		fin >> ceh[j].year;
		if (fin.fail()) {
			fin.clear();
			fin.ignore(9999, '\n');
			fin.close();
			return 1;
		}
		fin.clear();
		fin.ignore(9999, '\n');
		fin.getline(ceh[j].izd, 100);
		fin >> ceh[j].amount;
		if (cin.fail()) {
			fin.clear();
			fin.ignore(9999, '\n');
			fin.close();
			return 1;
		}
		fin.clear();
		fin.ignore(9999, '\n'); 
		fin.getline(buf, 10);
	}
	cout_s(ceh, m);
	fin.close();
	return 0;
}
void task(Bib* ceh, int m) {
	int u;
	cout << "Год: ";
	cin >> u;
	shekerSort(ceh, m, 0);
	cout << '\n';
	for (int y = 0; y < m; y++)
		if (ceh[y].year>u)
		cout << "Рег. номер: " << ceh[y].register_cod <<
		" Автор: " << ceh[y].author <<
		" Название: " << ceh[y].name_book <<
		" Год: " << ceh[y].year <<
		" Издательство: " << ceh[y].izd <<
		" Стр.: " << ceh[y].amount << '\n';

	ofstream file;
	file.open("txt.txt");
	file.is_open();
	for (int y = 0; y < m; y++)
		if (ceh[y].year > u)
		file << "Рег. номер: " << ceh[y].register_cod <<
		" Автор: " << ceh[y].author <<
		" Название: " << ceh[y].name_book <<
		" Год: " << ceh[y].year <<
		" Издательство: " << ceh[y].izd <<
		" Стр.: " << ceh[y].amount << '\n';
	file.close();
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	Bib* bib;
	int m;
	if(cin_ss(bib,m)) return 0;
	cout_sss(bib, m);
	for (;;) {
		cout << "\n\n		Выберите пункт:" <<
			"\n		1 - просмотр полного списка" <<
			"\n		2 - отсортировать список" <<
			"\n		3 - дополнить список" <<
			"\n		4 - удаление одного элемента из списка" <<
			"\n		5 - корректировка" <<
			"\n		6 - задание" <<
			"\n		7 - выход\n";
		int l;
		cin >> l;
		while (cin.fail() || l < 1 || l>7) {
			clear_m();
			cout << "\nВведите корректное значение: ";
			cin >> l;
		}
		switch (l)
		{
		case 1: cout_s(bib, m); break;
		case 2: shekerSort(bib, m,1); break;
		case 3: dop(bib, m); break;
		case 4: delete_s(bib, m); break;
		case 5: correct(bib, m); break;
		case 6: task(bib, m); break;
		case 7: return 0; break;
		}
	}
}