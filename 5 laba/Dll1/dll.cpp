#include "dll.h"
#include <cmath>

double fun(int* a, int n, int q, int k) {
	if (q == k)
		return 1;
	else
		return (sin(a[q]) - cos(a[q])) * fun(a, n, q + 1, k);
}
