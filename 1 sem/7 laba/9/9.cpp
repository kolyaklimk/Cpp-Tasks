﻿//Лабораторная 7, задача 9. Выполнена: Климкович Н. В.

/*Вчера на уроке математики Саша (возможно Богом данный) узнал
о том, что иногда полезно использовать вместо десятичной системы
счисления какую-нибудь другую. Однако, учительница (как иронично) не
объяснила, почему в системе счисления по основанию b в качестве цифр
выбирают числа от 0 до b - 1. Немного подумав, Саша понял, что можно
выбирать и другие наборы цифр. Например, вместо троичной системы
счисления можно рассмотреть систему счисления, где вместо обычных цифр
0, 1, 2 есть цифры 1, 2 и 3. Саша заинтересовался вопросом, а как перевести
число n в эту систему счисления? Например, число 7 в этой системе
записывается как 21, так как 7 = 2∙3+1, а число 22 записывается как 211, так
как 22 = 2 ∙ 9 + 1 ∙ 3 + 1.

Входные данные:
натуральное число n, 1 ≤ n ≤ 2•109.

Выходные данные:
число n записанное в указанной системе счисления.*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    string s;
    cin >> n;
    while (cin.fail() || n < 1 || n > 2e9) {
        cin.clear();
        cin.ignore(9999, '\n');
        cout << "incorrect value, n = ";
        cin >> n;
    }
    while (n) {
        s += n % 3 + '0';
        n /= 3;
    }
    for (int j = 0, j1 = s.length() - 1; j < s.length() / 2; j++, j1--)
        swap(s[j], s[j1]);
    cout << s;
}