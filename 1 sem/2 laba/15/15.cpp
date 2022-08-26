//Лабораторная 2, задача 15. Выполнена: Климкович Н. В.

/*Для дробного числа К напечатать фразу "мы нашли К грибов в лесу",
согласовав окончание слова "гриб" с числом К.*/

#include <iostream> 
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	double k, a, b, x, y, y1, y2;
	cout << "K = "; cin >> k;
	while (k < 0) {
		cout << "Enter the correct value\n";
		cout << "\nK = "; cin >> k;
	}

	// значение после точки
	x = 10;
	b = 0;
	a = floor(k);

	while (b < 1){
		b = (k - a) * x;
		x *= 10;
	}

	// значение окончания от 1 до 4
	y = round((k / 10 - floor(k / 10))*10);
	y1 = round((k / 100 - floor(k / 100)) * 100-1);

	if (y == 1 && y1 == 10) {
		cout << "Мы нашли " << k << " грибов в лесу";
		exit(0);
	}
	else if (y == 1 && y1 != 10) {
		cout << "Мы нашли " << k << " гриб в лесу";
		exit(0);
	}

	if (b > 0 || y > 0 && y < 5) cout << "Мы нашли " << k << " гриба в лесу";
	else cout << "Мы нашли " << k << " грибов в лесу";

	return 0;
}