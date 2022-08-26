//Лабораторная 2, задача 7. Выполнена: Климкович Н. В.

//Составить программу для решения уравнений трёх видов.

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
    double a, b, c, p, q, D, x1, x2, t1, t2, D1, D2, x0, R, g, pi, y1, y2, y3;
    pi = 3.14159265359;
    cout << "a = "; cin >> a;
    cout << "b = "; cin >> b;
    cout << "c = "; cin >> c;
    cout << "p = "; cin >> p;
    cout << "q = "; cin >> q;

    // ax^4 + bx^2 + c = 0
    cout << "\n\nax^4 + bx^2 + c = 0";

    if (a == 0 && b == 0 && c == 0) cout << "\nno solutions";

    if (a != 0 && b != 0 && c != 0) {
        D = b * b - 4 * a * c;

        if (D >= 0) {
            x1 = (-b + sqrt(D)) / 2 / a;
            x2 = (-b - sqrt(D)) / 2 / a;

            if (x1 == x2) {
                if (x1 >= 0) {
                    x1 = sqrt(x1);
                    cout << "\nx = " << -x1 << ", " << x1;
                }
                else cout << "\nno solutions";
            }

            else {
                if (x1 >= 0) {
                    x1 = sqrt(x1);
                    cout << "\nx = " << -x1 << ", " << x1;
                }
                else cout << "\nno solutions";


                if (x2 >= 0) {
                    x2 = sqrt(x2);
                    cout << ", " << -x2 << ", " << x2;
                }
            }
        }
        else cout << "\nno solutions";
    }

    // bx^2 + c = 0
    if (a == 0 && b != 0 && c != 0) {
        x1 = (-c) / b;
        if (x1 > 0) {
            x1 = sqrt(x1);
            cout << "\nx = " << -x1 << ", " << x1;
        }
        else cout << "\nno solutions";
    }

    // ax^4 + c = 0
    if (a != 0 && b == 0 && c != 0) {
        x1 = (-c) / a;
        if (x1 > 0) {
            x1 = sqrt(sqrt(x1));
            cout << "\nx = " << -x1 << ", " << x1;
        }
        else cout << "\nno solutions";
    }

    // ax^4 + bx^2 = 0  -->  ax^2 + b = 0
    if (a != 0 && b != 0 && c == 0) {
        x1 = (-b) / a;
        cout << "\nx = 0";
        if (x1 > 0) {
            x1 = sqrt(x1);
            cout << ", " << -x1 << ", " << x1;
        }
    }

    // c = 0
    if (a == 0 && b == 0 && c != 0) cout << "\nno solutions";

    //  bx^2 = 0
    if (a == 0 && b != 0 && c == 0) cout << "\nx = 0";

    // ax^4 = 0
    if (a != 0 && b == 0 && c == 0) cout << "\nx = 0";

    //////////////////////////////////////////////////////////////

    // ax^4 + bx^3 + cx^2 + bx + a = 0
    // https://resh.edu.ru/subject/lesson/3785/conspect/158887/

    cout << "\n\nax^4 + bx^3 + cx^2 + bx + a = 0";

    if (a == 0 && b == 0 && c == 0) cout << "\nno solutions";

    if (a != 0 && b != 0 && c != 0) {
        D = b * b - 4 * a * (c - 2 * a);

        if (D >= 0) {
            t1 = (b + sqrt(D)) / 2 / a;
            t2 = (b - sqrt(D)) / 2 / a;

            D1 = t1 * t1 - 4;
            x1 = (-t1 + sqrt(D1)) / 2;
            x2 = (-t1 - sqrt(D1)) / 2;
            if (D1 >= 0) {
                if (x1 == x2) cout << "\nx = " << x1;
                else cout << "\nx = " << x1 << ", " << x2;
            }

            D2 = t2 * t2 - 4;
            x1 = (-t1 + sqrt(D2)) / 2;
            x2 = (-t1 - sqrt(D2)) / 2;
            if (D2 >= 0) {
                if (x1 == x2) cout << "\nx = " << x1;
                else cout << "\nx = " << x1 << ", " << x2;
            }

            if (D1 < 0 && D2 < 0) cout << "\nno solutions";
        }
        else cout << "\nno solutions";
    }

    // bx^3 + cx^2 + bx = 0  ==>  bx^2 + cx + b = 0
    if (a == 0 && b != 0 && c != 0) {
        D = c * c - 4 * b * b;
        x0 = 0;
        if (D >= 0) {
            x1 = (-c + sqrt(D)) / 2 / b;
            x2 = (-c - sqrt(D)) / 2 / b;

            if (x1 == x2) cout << "\nx = 0, " << x1 << ", " << x0;

            else cout << "\nx = 0, " << x1 << ", " << x2 << ", " << x0;
        }
        else cout << "\nx = 0";
    }

    // ax^4 + cx^2 + a = 0    
    if (b == 0 && a != 0 && c != 0) {
        D = c * c - 4 * a * a;

        if (D >= 0) {
            x1 = (-c + sqrt(D)) / 2 / a;
            x2 = (-c - sqrt(D)) / 2 / a;

            if (x1 == x2) {
                if (x1 >= 0) {
                    x1 = sqrt(x1);
                    cout << "\nx = " << -x1 << ", " << x1;
                }
                else cout << "\nno solutions";
            }

            else {
                if (x1 >= 0) {
                    x1 = sqrt(x1);
                    cout << "\nx = " << -x1 << ", " << x1;
                }
                else cout << "\nno solutions";


                if (x2 >= 0) {
                    x2 = sqrt(x2);
                    cout << ", " << -x2 << ", " << x2;
                }
            }
        }
        else cout << "\nno solutions";
    }

    // ax^4 + bx^3 + bx + a = 0
    if (c == 0 && a != 0 && b != 0) {
        D = b * b - 4 * a * ( 0 - 2 * a);

        if (D >= 0) {
            t1 = (b + sqrt(D)) / 2 / a;
            t2 = (b - sqrt(D)) / 2 / a;

            D1 = t1 * t1 - 4;
            x1 = (-t1 + sqrt(D1)) / 2;
            x2 = (-t1 - sqrt(D1)) / 2;
            if (D1 >= 0) {
                if (x1 == x2) cout << "\nx = " << x1;
                else cout << "\nx = " << x1 << ", " << x2;
            }

            D2 = t2 * t2 - 4;
            x1 = (-t1 + sqrt(D2)) / 2;
            x2 = (-t1 - sqrt(D2)) / 2;
            if (D2 >= 0) {
                if (x1 == x2) cout << "\nx = " << x1;
                else cout << "\nx = " << x1 << ", " << x2;
            }

            if (D1 < 0 && D2 < 0) cout << "\nno solutions";
        }
        else cout << "\nno solutions";
    }

    // cx^2= 0 
    if (a == 0 && b == 0 && c != 0) cout << "\nx = 0";

    // bx^3 + bx = 0  
    if (a == 0 && b != 0 && c == 0) cout << "\nx = 0";

    // ax^4 + a = 0  
    if (a != 0 && b == 0 && c == 0) cout << "\nno solutions";

    ////////////////////////////////////////////////////////////

    // x^3 + px + q = 0
    // https://ru.intemodino.com/math/algebra/equations/cardano%27s-formula-for-solving-cubic-equations.html
    // https://www.mccme.ru/circles/oim/mmks/works2013/akhtyamov2.pdf

    cout << "\n\nx^3 + px + q = 0";

    if (p == 0 && q == 0) cout << "\nx = 0";

    if (p != 0 && q != 0) {
        D = pow(p / 3, 3) + pow(q / 2, 2);
        if (D > 0) {
            R = cbrt(-q / 2 + sqrt(D));
            x1 = R - p / 3 / R;
            cout << "\nx = " << x1;
        }
        else {
            if (q < 0) g = atan(sqrt(-D) / (-q) * 2);
            if (q > 0) g = atan(sqrt(-D) / (-q) * 2) + pi;
            if (q == 0) g = pi/2;
            y1 = 2 * sqrt((-p) / 3) * cos(g / 3);
            y2 = 2 * sqrt((-p) / 3) * cos(g / 3 + pi * 2 / 3);
            y3 = 2 * sqrt((-p) / 3) * cos(g / 3 + pi * 4 / 3);
            cout << "\nx = " << y1 << ", " << y2 << ", " << y3;
        }
    }

    // x^3 + q = 0
    if (p == 0 && q != 0) cout << "\nx = " << cbrt(-q);

    // x^3 + px = 0
    if (p != 0 && q == 0) {
        cout << "\nx = 0";
        if (p < 0) {
            x1 = sqrt(-p);
            cout << ", " << -x1 << ", " << x1;
        }
    }

    return 0;
}