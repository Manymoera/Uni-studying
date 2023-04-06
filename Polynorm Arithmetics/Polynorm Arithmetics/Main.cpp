#include <iostream>
#include <locale>
#include "Monom.h"
#include "CircleList.h"
#include "Polinom.h"

using namespace std;

int main()
{
    int maxpw = 10; //Макс. степень
    int count = 6; //Кол-во переменных

    setlocale(LC_ALL, "rus");
    Monom a(4, 4583);
    Monom m(3, 123);
    Monom n(2, 23);
    cout << endl;

    //Monom

    cout << "Monom A:" << endl;
    cout << a.MonomToString(maxpw, count) << endl;
    cout << endl;

    cout << "Monom M:" << endl;
    cout << m.MonomToString(maxpw, count) << endl;
    cout << endl;

    cout << "Monom N:" << endl;
    cout << n.MonomToString(maxpw, count) << endl;
    cout << endl;

    cout << "Copy from A to B" << endl;
    Monom b(a);
    cout << b.MonomToString(maxpw, count) << endl;

    cout << endl;
    cout << "A = C" << endl;
    Monom c = a;
    cout << c.MonomToString(maxpw, count) << endl;

    cout << endl;
    cout << "C * 3" << endl;
    c = c * 3;
    cout << c.MonomToString(maxpw, count) << endl;

    cout << endl;
    cout << "A - C" << endl;
    a = a - c;
    cout << a.MonomToString(maxpw, count) << endl;

    cout << endl;
    Monom g(a);
    cout << "G + C" << endl;
    c = g + c;
    cout << c.MonomToString(maxpw, count) << endl;

    cout << endl;
    cout << "A * C" << endl;
    Monom G = a.Multiply(c, maxpw, count);
    cout << G.MonomToString(maxpw, count) << endl;
    cout << endl;

    cout << "B * N" << endl;
    Monom p;
    p = m.Multiply(n, maxpw, count);
    cout << p.MonomToString(maxpw, count) << endl;  

    //Cyclic list

    cout << endl;
    cout << "CircleList A:" << endl;
    CircleList p1(a);
    cout << p1.CircleListToString(maxpw, count) << endl;

    Monom z(1, 345);
    cout << endl;
    cout << "CircleList B:" << endl;
    CircleList p2(z);
    cout << p2.CircleListToString(maxpw, count) << endl;
    cout << endl;

    CircleList p3;
    cout << "CList A + CList B" << endl;
    p3 = p2 + p1;
    cout << p3.CircleListToString(maxpw, count) << endl;
    cout << endl;

    cout << "Clist N * 10" << endl;
    CircleList p4 = p3 * 10;
    cout << p4.CircleListToString(maxpw, count) << endl;
    cout << endl;

    CircleList c1(m);
    CircleList c2(n);
    CircleList pE = c1 + c2;
    CircleList pM = c1 + c2;
    cout << "E * M:" << endl;
    CircleList pEM = pE.Multiply(pM, maxpw, count);
    cout << pE.CircleListToString(maxpw, count) << " * " << pM.CircleListToString(maxpw, count) << " = " << pEM.CircleListToString(maxpw, count) << endl;
    cout << endl;

    //Polinom

    Polinom Polinom1("3x1^4x2x3^3 + 2x1x3^2x5^2", maxpw, count);
    Polinom Polinom2("x2^2x3x4^3 + -8x1^2x4x6", maxpw, count);
    Polinom Polinom3("", maxpw, count);
    Polinom Polinom4("", maxpw, count);

    std::cout << "Polinom1: " << Polinom1.getPolinom() << endl;
    std::cout << "Polinom2: " << Polinom2.getPolinom() << endl;
    Polinom3 = Polinom1 * 3;
    Polinom4 = Polinom1 * Polinom2;
    std::cout << "Polinom1 + Polinom2: " << Polinom3.getPolinom() << endl;
    std::cout << "Polinom1 * Polinom2: " << Polinom4.getPolinom() << endl;

    return 0;
}