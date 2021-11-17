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