#include <iostream>
#include "Polinom.h"
using namespace std;

int main()
{
    cout<<"  Atentie! Pentru impartirea polinoamelor cu coeficienti intregi, este nevoie ca pentru impartitor,coeficientul "<<endl;
    cout<<"termenului de grad maxim sa fie 1 sau -1, altfel impartirea nu poate fi realizata in multimea numerelor intregi."<<endl;
    Polinom <int> p1;
    p1.adaugare_termen(1,-2);
    p1.adaugare_termen(2,1);
    p1.adaugare_termen(3,3);
    p1.adaugare_termen(0,5);
    p1.adaugare_termen(4,1);
    p1.adaugare_termen(2,1);
    p1.adaugare_termen(6,3);
    cout<<"Polinomul p1 este: "<<p1;
    p1.eliminare_termen(2);
    cout<<"Dupa eliminarea termenului de grad 2, polinomul va fi: ";
    cout<<p1;
    p1.adaugare_termen(2,1);
    cout<<"Dupa adaugarea unui termen de grad 2 si coeficient 1, polinomul va fi: ";
    cout<<p1;
    cout<<"Gradul polinomului p1 este: "<<p1.grad_polinom()<<endl;
    cout<<"Introduceti o valoare pentru x: ";
    int x;
    cin>>x;
    cout<<"Valoarea polinomului p1 in x este: "<<p1.calcul_valoare(x)<<endl;
    cout<<"Introduceti un grad x pentru care vreti sa afisati coeficientul: ";
    cin>>x;
    cout<<"Coeficientul termenului de grad "<<x<<" din polinomul p1 este: "<<p1[x]<<endl;
    Polinom <int> p2;
    p2.adaugare_termen(0,4);
    p2.adaugare_termen(1,-1);
    p2.adaugare_termen(2,3);
    p2.adaugare_termen(3,1);
    cout<<"Polinomul p2 este: "<<p2;
    Polinom <int> p3;
    p3=p1+p2;
    cout<<"Polinomul p3 rezultat in urma adunarii polinoamelor p1 si p2 este: ";
    cout<<p3;
    Polinom <int> p4;
    p4=p1*p2;
    cout<<"Polinomul p4 rezultat in urma inmultirii polinoamelor p1 si p2 este: ";
    cout<<p4;
    Polinom <int> p5;
    cout<<"Introduceti o valoare x cu care sa inmultiri polinomul p1: ";
    cin>>x;
    p5=p1*x;
    cout<<"Polinomul rezultat, p5, este: ";
    cout<<p5;
    cout<<"Polinomul p1 este:"<<p1;
    cout<<"Polinomul p2 este:"<<p2;
    Polinom <int> p6;
    p6=p1/p2;
    cout<<"Polinomul p6 rezultat in urma impartirii polinoamului p2 la polinomul p1 este: ";
    cout<<p6;
    return 0;
}
