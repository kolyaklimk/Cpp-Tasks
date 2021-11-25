//Лабораторная 6, задача 4. Выполнена: Климкович Н. В.


/*1 апреля 20?? года будет проведена реформа английского языка,
позволяющая облегчить его освоение иностранцами и английскими
школьниками. Во-первых, из алфавита уберут четыре буквы C, Q, W и X (на
клавиатуре компьютера вместо них будут клавиши, вызывающие программы
Word, eXcel и другие). Вместо c перед буквами e, i, y нужно будет писать
букву s, а в остальных случаях – букву k. Вместо буквы q нужно будет писать
букву k, вместо сочетания qu –
kv, вместо x – ks, а вместо w – v. Во-вторых, сочетание букв ph будет
записываться как f, you и oo – как u, ee – как i, th – как z. Кроме того, все
двойные согласные (включая образовавшиеся после замен), вызывающие
большие трудности у учащихся, станут одинарными, например, apple после
реформы нужно писать как aple.
В связи с реформой нужно переработать огромное количество текстов.
Напишите программу, выполняющую эту работу.

Входные данные:
Во входном файле содержится текст на английском языке, без
переносов слов. Длина строк не превышает 100 символов.

Выходные данные:
В выходной файл вывести тот же текст, но уже соответствующий
реформе. Если первая буква заменяемого сочетания букв была прописной,
то первая буква замены должна быть также прописной. Вторая буква в
заменах x→ks, qu→kv должна быть всегда строчной.
*/
#include <iostream>
#include <string>
using namespace std;
int main()
{
	string st,buf;
	for(;;) {
		getline(cin, buf);
		if (buf.length() == 0) break;
		st += buf;
	}
	int l = st.length();
	int bu;

	for (int s = 0; s < l; s++) {
		bu = st.find_first_of("bcdfghjklmnpqrstvwxz");
		if (st[s + 1] == st[s]) st.erase(bu, 1);
	}



	for (int s = 0; s < l; s++) {
		bu = st.find("qu");
		if (bu != -1)st.replace(bu, 2, "kv");
	}

	for (int s = 0; s < l; s++) {
		bu = st.find("x");
		if (bu != -1) {
			st.erase(bu, 1);
			st.insert(bu, "ks");
		}
	}

	for (int s = 0; s < l; s++) {
		bu = st.find("ph");
		if (bu != -1) {
			st.erase(bu, 2);
			st.insert(bu, "f");
		}
	}

	for (int s = 0; s < l; s++) {
		bu = st.find("you");
		if (bu != -1) {
			st.erase(bu, 3);
			st.insert(bu, "u");
		}
	}

	for (int s = 0; s < l; s++) {
		bu = st.find("oo");
		if (bu != -1) {
			st.erase(bu, 2);
			st.insert(bu, "u");
		}
	}

	for (int s = 0; s < l; s++) {
		bu = st.find("ee");
		if (bu != -1) {
			st.erase(bu, 2);
			st.insert(bu, "i");
		}
	}

	for (int s = 0; s < l; s++) {
		bu = st.find("th");
		if (bu != -1) {
			st.erase(bu, 2);
			st.insert(bu, "z");
		}
	}

	for (int s = 0; s < l; s++) {
		bu = st.find('c');
		if (bu != -1) {
			if (st[bu + 1] == 'e' || st[bu + 1] == 'i' || st[bu + 1] == 'y')
				st.replace(bu, 1, "s");
			else st.replace(bu, 1, "k");
		}
	}

	for (int s = 0; s < l; s++) {
		bu = st.find('w');
		if (bu != -1)st.replace(bu, 1, "v");
	}

	for (int s = 0; s < l; s++) {
		bu = st.find('q');
		if (bu != -1)st.replace(bu, 1, "k");
	}
	
	cout << st;
}