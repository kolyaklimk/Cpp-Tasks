//Лабораторная 8, задача 1. Выполнена: Климкович Н. В.

/*Разработать программу в соответствии с вариантом, реализующую
работу со структурами в консольном приложении.
Использовать динамический массив структур, содержащий поля согласно
варианту индивидуального задания.
Программа должна содержать необходимые комментарии.
Следует ввод/вывод на экран входных и выходных данных. Для
форматированного ввода-вывода использовать scanf и printf, предусмотреть
некорректный ввод. Обрабатываемая структура должна иметь не менее пяти
полей (элементов) двух и более типов (если в задании указано меньше -
добавить). В каждом варианте задания реализовать следующие функции
для работы со структурой:
1. Функцию формирования динамического одномерного массива структур,
значения которых вводятся с клавиатуры. Предусмотреть возможность
заполнения одного поля структуры, используя известные значения других полей
структуры (придумать самим). С массивом структур работать через оператор new.
При вводе структур необходимо реализовать следующие механизмы:
• ввод заранее заданного количества структур;
• ввод до появления структуры с заданным признаком;
• диалог с пользователем о необходимости продолжать ввод.
2. Функцию просмотра содержимого динамического массива структур.
3. Функцию дополнения уже существующего массива структур новыми
структурами.
4. Функцию поиска и вывода на экран структуры (структур) с заданным
значением элемента.
5. Функции удаления и изменения элемента массива структур с заданным
значением элемента.
6. Функцию упорядочения массива структур по одному из полей
(элементов). Поле для сортировки выбрать самим. Способ указан в скобках.


Вариант 9: Различные цеха завода выпускают продукцию нескольких наименований.
Сведения о выпущенной продукции включают наименование, количество, номер
цеха. Для заданного цеха вывести количество выпущенных изделий (Шейкер
сортировка по убыванию).*/

#include <iostream>
#include <cmath>
#include <string>
#include <Windows.h>
using namespace std;

void clear_m() {
	cin.clear();
	cin.ignore(9999, '\n');
}
void error(int a) {
	clear_m();
	cout << "\nВведите корректное значение: ";
	cin >> a;
}
struct Cex {
	string name;
	int amount = 0;
	short number = 0;
};
bool correct(string a) {
	for (int u = 0; u < a.length(); u++)
		if (a[u] < 'a' && a[u]>'Z' || a[u] < 'A' || a[u]>'z')
			return 1;
	return 0;
}
void cout_s(Cex* ceh, int m) {
	cout << '\n';
	for (int y = 0; y < m; y++) 
		cout  << ceh[y].name << ", " << ceh[y].amount << " шт.; " << "Цех " << ceh[y].number << '\n';
}
void shekerSort(Cex* mass, int count){
	Cex t;
	int left = 0, right = count - 1;
	int flag = 1; 
	while ((left < right) && flag > 0)
	{
		flag = 0;
		for (int i = left; i < right; i++) 
		{
			if (mass[i].name[0] < mass[i + 1].name[0]) 
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
			if (mass[i - 1].name[0] < mass[i].name[0])
			{
				t = mass[i];
				mass[i] = mass[i - 1];
				mass[i - 1] = t;
				flag = 1;
			}
		}
		left++;
	}
	cout_s(mass, count);
}
void cin_s(Cex* ceh, int zero, int m) {
	bool b,k;
	for (int y = zero; y < m + zero; y++) {
		b = 0;
		clear_m();
		cout << "\nЦех " << y + 1 << "\nНаименование изделия: ";
		getline(cin, ceh[y].name);
		b = correct(ceh[y].name);
		while (ceh[y].name.length() == 0 || b) {
			b = 0;
			cout << "Введите корректное значение: ";
			getline(cin, ceh[y].name);
			b = correct(ceh[y].name);
		}

		cout << "Количество: ";
		cin >> ceh[y].amount;
		while (cin.fail() || ceh[y].amount < 1) {
			clear_m();
			cout << "Введите корректное значение: ";
			cin >> ceh[y].amount;
		}
		cout << "Номер цеха: ";
		cin >> ceh[y].number;
		k = 0;
		for (int g = 0; g < y; g++) {
			if (ceh[y].number == ceh[g].number) {
				k++;
				break;
			}
		}
		while (cin.fail() || ceh[y].number < 1 || k) {
			clear_m();
			cout << "Введите корректное значение: ";
			cin >> ceh[y].number;
			k = 0;
			for (int g = 0; g < y; g++) {
				if (ceh[y].number == ceh[g].number) {
					k++;
					break;
				}
			}
		}
	}
	cout_s(ceh, m);
}
void dop(Cex*& ceh, int& m) {
	int y = m;
	cout << "Сколько цехов добавить (0=назад): ";
	cin >> y;
	if (!y) return;
	while (cin.fail() || y < 1) {
		clear_m();
		cout << "\nВведите корректное значение (0=назад): ";
		cin >> y;
		if (!y) return;
	}
	Cex* buf = new Cex[m];
	for (int u = 0; u < m; u++) {
		buf[u] = ceh[u];
	}
	delete[] ceh;
	ceh = new Cex[m+y];
	for (int u = 0; u < m; u++) {
		ceh[u] = buf[u];
	}
	delete[] buf;
	cin_s(ceh, m, y);
	m += y;
	cout_s(ceh, m);
}
void delete_s(Cex*& ceh, int& m) {
	short d;
	bool r = 0;
	cout << "Какой цех из списка удалить? (0=назад) ";
	cin >> d;
	if (!d) return;
	while (cin.fail() || d < 1) {
		clear_m();
		cout << "\nВведите корректное значение (0=назад): ";
		cin >> d;
		if (!d) return;
	}
	for (int u = 0; u < m; u++) {
		if (ceh[u].number == d) {
			d = u;
			r = 1;
			break;
		}
	}
	if (!r) {
		cout << "В списке нет такого цеха";
		return;
	}
	for (int u = d; u < m-1; u++)
		ceh[u] = ceh[u + 1];
	Cex* buf = new Cex[--m];
	for (int u = 0; u < m; u++) {
		buf[u] = ceh[u];
	}
	delete[] ceh;
	ceh = new Cex[m];
	for (int u = 0; u < m; u++) {
		ceh[u] = buf[u];
	}
	delete[] buf;
	cout_s(ceh, m);
}
void detail(Cex*& ceh, int m) {
	bool k=0;
	int j, i;
	cout << "Номер цеха (0=назад): ";
	cin >> j;
	if (!j) return;
	for (int g = 0; g < m; g++) {
		if (j == ceh[g].number) {
			i = g;
			k++;
			break;
		}
	}
	while (cin.fail() || j < 1 || !k) {
		clear_m();
		cout << "Введите корректное значение (0=назад): ";
		cin >> j;
		k = 0;
		for (int g = 0; g < m; g++) {
			if (j == ceh[g].number) {
				i = g;
				k++;
				break;
			}
		}
		if (!j) return;
	}
	cout << ceh[i].amount << " шт.";
}

int main() {
	setlocale(LC_ALL, "Russian");
	int m;
	cout << "Количество цехов: ";
	cin >> m;
	while (cin.fail() || m < 1) {
		clear_m();
		cout << "\nВведите корректное значение: ";
		cin >> m;
	}
	Cex* ceh = new Cex[m];
	cin_s(ceh, 0, m);
	for (;;) {
		cout << "\n\n		Выберите пункт:" <<
			"\n		1 - просмотр полного списка"<<
			"\n		2 - отсортировать список" <<
			"\n		3 - дополнить список" <<
			"\n		4 - удаление одного элемента из списка" <<
			"\n		5 - количество выпущенных изделий определённого цеха" <<
			"\n		6 - выход\n";
		int l;
		cin >> l;
		while (cin.fail() || l < 1 || l>6) {
			clear_m();
			cout << "\nВведите корректное значение: ";
			cin >> l;
		}
		switch (l)
		{
		case 1: cout_s(ceh, m); break;
		case 2: shekerSort(ceh, m); break;
		case 3: dop(ceh, m); break;
		case 4: delete_s(ceh, m); break;
		case 5: detail(ceh, m); break;
		case 6: return 0; break;
		}
	}
}