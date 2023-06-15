//Лабораторная 2, задача 9. Выполнена: Климкович Н. В.

/*Даны действительные положительные числа x, y, z. Выяснить,
существует ли треугольник с длинами сторон x, y, z.*/

#include <iostream>
using namespace std;
int main()
{
    double x, y, z;
    cout << "x = "; cin >> x;
    cout << "y = "; cin >> y;
    cout << "z = "; cin >> z;

    while (x <= 0 || y <= 0 || z <= 0) {
        cout << "Enter the correct value\n";
        cout << "\nx = "; cin >> x;
        cout << "y = "; cin >> y;
        cout << "z = "; cin >> z;
    }

    if (x < y + z && y < x + z && z < x + y)
        cout << "Triangle exists";
    else cout << "Triangle doesn't exist";
    
    return 0;
}