//Лабораторная 2, задача 10. Выполнена: Климкович Н. В.

/*Из величин, определяемых выражениями a = sinx, b = cosx, c = ln|x|
при заданном х, определить и вывести на экран дисплея минимальное
значение. Библиотеку <cmath> использовать запрещено.*/

#include <iostream>
using namespace std;
int main()
{
    double a, b, c, pi, sin, sin1, cos, cos1, ln, ln1;
    double q1, q1_, q2_, k, f, F, x, x1, x2, x3, x33, m;
    cout << "x = "; cin >> x;
    pi = 3.14159265359;
    x1 = x; x2 = x; x3 = x;

    // Преобразование для sin
    if (x1 > 360 || x1 < -360) {
        while (x1 > 360) x1 = x1 - 360;
        while (x1 < -360) x1 = x1 + 360;
    }
    if (x1 == 360 || x1 == -360 ) x1 = 0;
    if (x1 == 180 || x1 == -180) x1 = 0;
    
    // решение sin
    if (x1 != 0) {
        x1 = x1 * pi / 180;
        sin = x1; sin1 = 999; k = 2;

        // ряд Тейлора
        while (sin1 != sin) {
            q1_ = 1; q2_ = 1; F = 1;
            f = (2 * k - 1);
            q1 = k - 1;
            sin1 = sin;

            for (double f1 = 1; f1 <= f; f1++) F *= f1;
            for (int q11 = 1; q11 <= q1; q11++) q1_ *= (-1.0);
            for (int q21 = 1; q21 <= f; q21++) q2_ *= x1;
            sin += q1_ * q2_ / F;
            k++;
        }
        x1 = sin;
    }

    //cout << "\na) sinx = " << x1;
    
    // Преобразование для cos
    while (x2 > 360) x2 = x2 - 360;
    while (x2 < -360) x2 = x2 + 360;
    if (x2 == 360 || x2 == -360) x2 = 999;
    if (x2 == 180 || x2 == -180) x2 = -999;
    if (x2 < 360 && x2 > 180) x2 = x2 - 360;
    if (x2 > -360 && x2 < -180) x2 = x2 + 360;
    if (x2 == 90 || x2 == -90) x2 = -9999;

    // решение cos
    if (x2 != 999 && x2 != -999 && x2 != -9999) {
        x2 = x2 * pi / 180;
        cos = 1; cos1 = 0; k = 1;

        // ряд Тейлора
        while (cos1 != cos) {
            q1_ = 1; q2_ = 1; F = 1;
            f = 2 * k;
            q1 = k;
            cos1 = cos;

            for (double f1 = 1; f1 <= f; f1++) F *= f1;
            for (int q11 = 1; q11 <= q1; q11++) q1_ *= (-1.0);
            for (int q21 = 1; q21 <= f; q21++) q2_ *= x2;
            cos += q1_ * q2_ / F;
            k++;
        }
        x2 = cos;
    }
    if (x2 == 999) x2 = 1;
    if (x2 == -999) x2 = -1;
    if (x2 == -9999) x2 = 0;

    //cout << "\nb) cosx = " << x2;

    // модуль для x  -->  ln|x|
    m = 0;
    x33 = x3;
    while (x33 < 0) {
        x33++;
        m++;
    }
    x33 += m;
    if (x33 - m < 1) x33 = x33 - 2*(x3 + m);
    x3 = x33;

    // решение ln
    if (x3 != 0) {
        ln = 0; ln1 = 1; k = 0;

        // ряд Тейлора
        while (ln1 != ln) {
            q2_ = 1;
            ln1 = ln;

            for (int q21 = 1; q21 <= k; q21++) q2_ *= (x3 - 1) * (x3 - 1) / (x3 + 1) / (x3 + 1);
            ln += 1.0 / (2 * k + 1) * q2_;
            k++;
        }
        x3 = ln * 2 * (x3 - 1) / (x3 + 1);
    }
    else x3 = 9999;

    //if (x3 == 9999) cout << "\nc) ln|x| - there is no decision";
    //else cout << "\nc) ln|x| = " << x3;

    cout << "\nmin: ";

    // сравнение
    a = x1; b = x2; c = x3;
    if (a < b && a < c)
        cout << "a = " << a;
    if (b < a && b < c)
        cout << "b = " << b;
    if (c < a && c < b)
        cout << "c = " << c;
    return 0;
}