//Лабораторная 6, задача 7. Выполнена: Климкович Н. В.

/*В заданной строке S найти максимальную по длине подстроку, которая
не является палиндромом.
Формат входных данных:
На вход задается строка S, состоящая из строчных букв латинского
алфавита (1 ⩽ |S| ⩽ 105 ).
Формат выходных данных:
Выведите одно целое число — длина максимального непалиндрома.
Если такой подстроки не существует, то выведите -1.*/

#include <iostream>
#include <string>
using namespace std;

int main() {
	string st,buf,buf2,buf3;
	bool t = 0;
	int d, q, q1, r = 0, w = 0;
	for (;;) {
		getline(cin, st);
		d = st.length();
		if (d > 105 || d < 2) {
			cout << "\nTry again\n";
			continue;
		}
		for (int e = 0; e < d; e++)
			if ((st[e] < 'A' || st[e] > 'Z' && st[e] < 'a' || st[e] > 'z') && st[e] != ' ') t++;
		if (t) {
			cout << "\nTry again\n";
			t = 0;
			continue;
		}
		break;
	}

	while (st.find(' ') != -1) st.erase(st.find(' '), 1);
	
	buf3 = st;
	buf2 = st;
	d = st.length();
	for (q1 = 1; q1 < d; q1++) {
		for (q = 1; q < st.length(); q++) {
			buf = st;
			buf.erase(q + 1, st.length());
			w = 0;
			
			for (r = 1; r < buf.length(); r++)
				if (buf[r] == buf[buf.length() - 1 - r]) w++;

			if (w == buf.length() - 1) {
				st.erase(0, w / 2 + w % 2 - 1);
				buf2[w / 2 + w % 2 + q1 -1] = ' ';
				break;
			}
		}
		st.erase(0, 1);
	}

	for (int f = 0; f < buf2.length(); f++)
		if (buf2[f] == buf2[f + 1]) {
			buf2.erase(f, 1);
			f = -1;
		}

	buf2 += ' ';
	if (buf2.length() == 3) {
		r = -1;
	}
	else
		for (;;) {
			d = buf2.find(' ');
			if (d == -1) break;
			if (d+1> r) r = d +1;
			buf2.erase(0, d + 1);
		}
	if (r > buf3.length()) r = buf3.length();
	cout << r;
}