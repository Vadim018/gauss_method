#include <iostream>
#include <locale> // для задач пов'язаних з локалізацію
#include <math.h> // виконання простих математичних операцій
#include <stdlib.h> // містить у собі функції, що займаються виділенням пам'яті, контролем процесу виконання програми, перетворенням типів
using namespace std;

int main()
{
    setlocale(LC_ALL, "Ukr");
    int i, j, l, n, m;
    double aa, bb;
    cout << "Введ*ть матрицю!" << endl;
    cout << "К*лькість рядк*в: ";
    cin >> n;
    cout << "К*льк*сть стовпц*в: ";
    cin >> m;

    int* x;
    x = (int*)malloc(n * sizeof(int)); // виділяє достатньо місця для розміщення двох об’єктів типу double  
    int** a;
    a = (int**)calloc(n, sizeof(int*));

    for (i = 0; i < n; i++)
    a[i] = (int*)calloc(m, sizeof(int));
    cout << endl << "Вих*дна матриця: " << endl; // запис введеної матриці

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            cin >> a[i][j];
        }
    }
    cout << endl;
    cout << "Перетворення..." << endl;
    for (int k = 0; k < n; k++) // пошук максимального елемента у першому стовпці
    {
        aa = abs(a[k][k]);
        i = k;

        for (l = k + 1; l < n; l++)
            if (abs(a[l][k]) > aa)
            {
                i = l;
                aa = abs(a[l][k]);
            }

        if (aa == 0) // перевірка на нульовий елемент
        {
            cout << endl << "Система не має р*шень!" << endl;   
            return 0;
        }

        if (i != k) // перестановка i-го рядка, що містить головний елемент k-го рядка
        {
            for (j = k; j < m; j++)
            {
                bb = a[k][j];
                a[k][j] = a[i][j];
                a[i][j] = bb;
            }
        }
        cout << endl;
        for (i = 0; i < n; i++) // перетворення матриці
        {
            for (j = 0; j < m; j++)
            {
                cout << fixed; // fixed - є значенням за промовчанням для будь-якого іншого типу проекту
                cout.precision(); // задає кількість знаків після коми
                cout << a[i][j] << " ";
            }
            cout << endl;
        }
        aa = a[k][k]; // перетворення k-го рядка (обчислення масштабуючих множників)
        a[k][k] = 1;
        for (j = k + 1; j < m; j++) 
            a[k][j] = a[k][j] / aa;

        for (i = k + 1; i < n; i++) // перетворення рядків за допомогою k-го рядка
        {
            bb = a[i][k];
            a[i][k] = 0;

            if (bb != 0)
                for (j = k + 1; j < m; j++)
                    a[i][j] = a[i][j] - bb * a[k][j];
        }
        cout << endl;

        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
            {
                cout << fixed;
                cout.precision();
                cout << a[i][j] << " ";
            }
            cout << endl;
        }

        for (i = 0; i < n; i++) // перевірка на безкінченну кількість рішень
        {
            for (j = i + 1; j < n; j++)
                if (a[i][j] == 0)
                {
                    cout << endl << "Система має безл*ч р*шень!" << endl;
                    return 0;
                }
        }
    }

    for (i = n - 1; i >= 0; i--) // знаходження рішень СЛАР
    {
        x[i] = 0;
        aa = a[i][n];

        for (j = n; j > i; j--)
            aa = aa - a[i][j] * x[j];
        x[i] = aa;
    }
    cout << endl << "Р*шення: " << endl;

    for (i = 0; i < n; i++)
    {
        cout << "x[" << i + 1 << "] = " << x[i];
        cout << endl;
    }
}