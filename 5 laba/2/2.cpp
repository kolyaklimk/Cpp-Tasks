//Лабораторная 5, задача 2. Выполнена: Климкович Н. В.

/*Для заданного одномерного массива С из N элементов найти произведение
множителей, вычисляемых по формуле. Рекурсивную функцию
применять каждый раз отдельно для первой трети массива и для остальной части (2/3)
массива. Рекурсивные вызовы заканчивать, когда останется только один или два
элемента.*/

#include <iostream>
#include <iomanip>
using namespace std;

double fun(int* a, int n, int q, int k) {
	if (q == k)
		return 1;
	else
		return (sin(a[q])-cos(a[q])) * fun(a, n, q + 1, k);
}

int main()
{
	int i, n;
	srand(time(NULL));
	cout << "N = ";
	cin >> n;

	int* a = new int [n];
	
	//ввод значений в массив
	for (i = 0; i < n; i++) 
		a[i] = rand() % 100;
	
	cout << fun(a, n, 0, n / 3.0) * fun(a, n, n / 3.0, n);

	delete[] a;
}