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
using namespace std;

int find(int L, int m, string s, string s2)
{
	int an = 1;
	int z1 = s.length();
	int z2 = s2.length();
	if (L > z1 + z2)
	{
		for (int i = 0; i < L - z1 - z2; i++) an = (an * 26) % m;
		an = (an * 2) % m;
		return an;
	}
	else
		if (L == z1 + z2) return 2;
		else
		{
			an = 2;
			int j = 0;
			for (int i = L - z2; i < z1; i++, j++)
				if (s[i] != s2[j])
				{
					an--;
					break;
				}
			j = 0;
			for (int i = L - z1; i < z2; i++, j++)
				if (s2[i] != s[j])
				{
					an--;
					break;
				}
			return an;
		}
}

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

		cout << find(L, m, s, s2) << '\n';
	}
}