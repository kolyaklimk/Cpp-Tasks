#include "gtest/gtest.h"

#pragma comment(lib, "../x64/Debug/StaticLib1.lib")
#include "../StaticLib1/functions.h"

int task1(int task, int arr, int n, int q, int q1) {
	int** a = new int* [n];
	for (int i = 0; i < n; i++)
		a[i] = new int[n];
	
	for (int i = 1; i < n + 1; i++)
		for (int j = 1; j < n + 1; j++) {
			if (arr == 1) {
				if (i <= 5) a[i - 1][j - 1] = 2 * i * j * j - 2 * j;
				else a[i - 1][j - 1] = 3 * i * j - 3;
			}
			else {
				if (i <= 5) a[j - 1][i - 1] = 2 * i * j * j - 2 * j;
				else a[j - 1][i - 1] = 3 * i * j - 3;
			}
		}

	int Sum;
	if(arr == 1) Sum = sum(a, 1, 0, n);
	else Sum = sum(a, 0, 1, n);

	int ret = a[q][q1];

	delete_m(a, n);

	if (task == 1) return Sum;
	if (task == 2) return ret;
}

TEST(Task1, Test_sum_m_A_1) {
	EXPECT_EQ(task1(1, 1, 10, 0, 0), 3635);
  EXPECT_TRUE(true);
}

TEST(Task1, Test_sum_m_B_1) {
	EXPECT_EQ(task1(1, 0, 10, 0, 0), 3635);
	EXPECT_TRUE(true);
}

TEST(Task1, Test_sum_m_A_2) {
	EXPECT_EQ(task1(1, 1, 23, 0, 0), 81132);
	EXPECT_TRUE(true);
}

TEST(Task1, Test_sum_m_B_2) {
	EXPECT_EQ(task1(1, 0, 23, 0, 0), 81132);
	EXPECT_TRUE(true);
}

TEST(Task1, Test_transp_1) {
	EXPECT_EQ(task1(2, 2, 10, 0, 2), 4);
	EXPECT_TRUE(true);
}

TEST(Task1, Test_transp_2) {
	EXPECT_EQ(task1(2, 2, 5, 2, 3), 66);
	EXPECT_TRUE(true);
}

TEST(Task1, Test_transp_3) {
	EXPECT_EQ(task1(2, 2, 13, 12, 12), 504);
	EXPECT_TRUE(true);
}

//////////////////////////////////////////////////////////////////////
#include <Windows.h>

double task2(int n) {
	int* a = new int[n];

	for (int i = 0; i < n; i++)
		a[i] = i + 1;

	HINSTANCE load;
	load = LoadLibrary(L"Dll1.dll");
	typedef double (*Fun) (int*, int, int, int);
	Fun fun;
	fun = (Fun)GetProcAddress(load, "fun");

	double ret = round(fun(a, n, 0, n / 3) * fun(a, n, n / 3, n) * 1e6) / 1e6;

	FreeLibrary(load);

	delete[] a;

	return ret;
}

TEST(Task2, Test_âdll_1) {
	EXPECT_EQ(task2(2), 0.399182);
	EXPECT_TRUE(true);
}

TEST(Task2, Test_âdll_2) {
	EXPECT_EQ(task2(5), 0.057878);
	EXPECT_TRUE(true);
}

TEST(Task2, Test_âdll_3) {
	EXPECT_EQ(task2(14), -0.001777);
	EXPECT_TRUE(true);
}

//////////////////////////////////////////////////////////////////////
int task3_1(int task, float n, float k,int q_, int q1_, int y_) {
	int i, j, ret;

	int* b = new int[max(n, k)];

	int** a = new int* [n];
	for (i = 0; i < n; i++)
		a[i] = new int[k];

	int buf = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < k; j++)
			a[i][j] = buf++;

	if (k > n) {
		int g = floor(k / n);
		int g1 = g;
		for (int q = 0; q < n - 1; q++) {
			for (int q1 = g; q1 < k; q1++)a[q][q1] = INT_MAX - 2;
			g += g1;
		}
	}
	else {
		int g1 = ceil(n / k);
		int g = n - g1;
		for (int q1 = k-1; q1 >= 0; q1--) {
			for (int q = g; q >= 0; q--) a[q][q1] = INT_MAX - 2;
			g -= g1;
		}
	}

	i = 0;
	j = 0;
	int t = 0;
	int y = 0;
	while (j < k) {
		while (a[i][j] == INT_MAX - 2) {
			i++;
			if (a[i][j - 1] % 2 == 0 && a[i][j] == INT_MAX - 2 && b[y - 1] != a[i][j - 1]) {
				b[y] = a[i][j - 1];
				y++;
				t++;
			}
		}
		if (a[i][j] % 2 == 0) {
			b[y] = a[i][j];
			y++;
			t++;
		}
		j++;
	}

	j--;
	i++;
	while (i < n) {
		if (a[i][j] % 2 == 0) {
			b[y] = a[i][j];
			t++;
			y++;
		}
		i++;
	}

	if (task == 1) ret = a[q_][q1_];
	if (task == 2) ret= b[y_];

	for (i = 0; i < n; i++)
		delete[] a[i];
	delete[]a;
	
	delete[]b;

	return ret;
}

TEST(Task3_1, Test_del_hi_diag_1) {
	EXPECT_EQ(task3_1(1, 3, 7, 0, 3, 0), INT_MAX - 2);
	EXPECT_TRUE(true);
}

TEST(Task3_1, Test_del_hi_diag_2) {
	EXPECT_EQ(task3_1(1, 3, 7, 0, 3, 0), INT_MAX - 2);
	EXPECT_TRUE(true);
}

TEST(Task3_1, Test_del_hi_diag_3) {
	EXPECT_EQ(task3_1(1, 7, 3, 3, 2, 0), INT_MAX - 2);
	EXPECT_TRUE(true);
}

TEST(Task3_1, Test_main_diag_1) {
	EXPECT_EQ(task3_1(2, 3, 7, 1, 2, 1), 10);
	EXPECT_TRUE(true);
}

TEST(Task3_1, Test_main_diag_2) {
	EXPECT_EQ(task3_1(2, 2, 6, 1, 5, 2), 12);
	EXPECT_TRUE(true);
}

TEST(Task3_1, Test_main_diag_3) {
	EXPECT_EQ(task3_1(2, 7, 3, 2, 1, 1), 8);
	EXPECT_TRUE(true);
}

//////////////////////////////////////////////////////////////////////
int task3_2_null(int n, int q, int q1) {
	double** a = new double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new double[n];

	int buf = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = buf++;

	a[q][q1] = 0;

	int x = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (a[i][j] == 0)
				x++;

	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[]a;

	return x;
}

int task3_2_swap(int n, int q, int q1) {
	double** a = new double* [n];
	for (int i = 0; i < n; i++)
		a[i] = new double[n];

	int buf = 1;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			a[i][j] = buf++;

	for (int i = 0, i1 = n - 1; i < n; i++, i1--)
		for (int j = 0, j1 = n - 1; j < n; j++, j1--) {
			if (i >= ceil(double(n) / 2) || i == n / 2 && j >= n / 2) break;
			std::swap(a[i][j], a[i1][j1]);
		}
	int x = a[q][q1];

	for (int i = 0; i < n; i++)
		delete[] a[i];
	delete[]a;

	return x;
}

TEST(Task3_2, Test_null_1) {
	EXPECT_EQ(task3_2_null(5, 2, 4), 1);
	EXPECT_TRUE(true);
}

TEST(Task3_2, Test_null_2) {
	EXPECT_EQ(task3_2_null(15, 7, 3), 1);
	EXPECT_TRUE(true);
}

TEST(Task3_2, Test_null_3) {
	EXPECT_EQ(task3_2_null(32, 21, 17), 1);
	EXPECT_TRUE(true);
}

TEST(Task3_2, Test_swap_1) {
	EXPECT_EQ(task3_2_swap(3, 0, 0), 9);
	EXPECT_TRUE(true);
}

TEST(Task3_2, Test_swap_2) {
	EXPECT_EQ(task3_2_swap(5, 1, 3), 17);
	EXPECT_TRUE(true);
}

TEST(Task3_2, Test_swap_3) {
	EXPECT_EQ(task3_2_swap(7, 4, 1), 20);
	EXPECT_TRUE(true);
}

//////////////////////////////////////////////////////////////////////
