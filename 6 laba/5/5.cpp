//Лабораторная 6, задача 5. Выполнена: Климкович Н. В.


/*Во многих прикладных задачах, таких как поиск в сети или расшифровка
генома, требуется совершать некоторые действия со строками. Например,
часто требуется по некоторым данным о строке восстановить ее саму.
Вам даны две строки S1 и S2. Известно, что одна из них была суффиксом
искомой строки S, а другая — ее префиксом. Также известна длина искомой
строки L, а также то, что строка S состояла только из строчных букв
латинского алфавита.
Необходимо определить число строк, удовлетворяющих этим
ограничениям. Так как это число может быть достаточно большим, то
необходимо вывести его по модулю m.
*/
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

int main() {
	string s, s2;
	double L;
	int p, t,m;
	cin >> t;
	while (cin.fail() || t<1 || t> 100) {
		cin.clear();
		cin.ignore(9999, '\n');
		cin >> t;
	}

	for (int d = 0; d < t; d++) {
		cin >> L;
		while (cin.fail() || L < 1 || L> 1e9) {
			cin.clear();
			cin.ignore(9999, '\n');
			cin >> L;
		}

		cin >> m;
		while (cin.fail() || L < 1 || L> 1e4) {
			cin.clear();
			cin.ignore(9999, '\n');
			cin >> m;
		}
		cin.clear();
		cin.ignore(9999, '\n');
		getline(cin, s);
		while (s.length()>200)
			getline(cin, s);
		getline(cin, s2);
		while (s2.length() > 200) 
			getline(cin, s2);

		if (s2.length()==L || s.length() == L) {
			cout << "0\n\n";
			continue;
		}
		p = L - s2.length() - s.length();
		if (p < 0) {
			cout << "1\n\n";
			continue;
		}
		cout << fmod(pow(26, p) * 2, m) << "\n\n";

	}
}