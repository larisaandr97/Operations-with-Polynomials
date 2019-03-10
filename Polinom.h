#ifndef POLINOM_H
#define POLINOM_H
#include <iostream>
using namespace std;

template <class Ttype>class Polinom
{
public:
    Polinom(); //constructor fara parametri
    ~Polinom(); //destructor
    Polinom(Polinom <Ttype> &p); //constructor de copiere
    Polinom (int n); //constructor cu un parametru- numarul maxim de elemente n
    Polinom(int n, Ttype *a); //constructor cu doi parametri- vectorul de coeficienti de tip Ttype a si numarul maxim de elemente n,intreg
    int grad_polinom(); //functie care returneaza gradul polinomului, de tip int
    void adaugare_termen(int i, Ttype coef); // adaugarea unui termen de grad i, nr intreg,si coeficient coef de tip Ttype
    void eliminare_termen(int i); //eliminarea termenului de grad i, de tip int
    Ttype calcul_valoare(Ttype x); //calcularea valorii polinomului in x de tip Ttype
    template <class T> friend istream &operator>>(istream &c, Polinom  <T> &p); //supraincarcarea operatorului de citire cu functie friend
    template <class T> friend ostream &operator<<(ostream &co, Polinom <T> &p);//supraincarcarea operatorului de afisare cu functie friend
    Ttype operator[](int grad) ;//supraincarcarea operatorului [] care returneaza coeficientul termenului de grad i
    Polinom <Ttype> & operator=(Polinom <Ttype> & p); //supraincarcarea operatorului =
    Polinom <Ttype> & operator-(Polinom <Ttype> & p); //supraincarcarea operatorului - pentru scaderea a doua polinoame
    Polinom <Ttype> & operator+(Polinom <Ttype> & p); //supraincarcarea operatorului + pentru adunarea a doua polinoame
    Polinom <Ttype> & operator*(Polinom <Ttype> & p); //supraincarcarea operatorului * pentru inmultirea a doua polinoame
    Polinom <Ttype> & operator*(Ttype scalar); //supraincarcarea operatorului * pentru inmultirea unui polinom cu un scalar
    Polinom <Ttype> & operator/(Polinom <Ttype> & p); //supraincarcarea operatorului / pentru imopartirea a doua polinoame

protected:

private:
    int nr_maxim_elem; //numarul maxim de elemente pe care il poate avea vectorul de coeficienti la alocare
    Ttype *v; //vectorul de coeficienti
};

//constructor fara parametri
template <class Ttype>
Polinom <Ttype>::  Polinom()
{
    nr_maxim_elem=7;
    v=new Ttype[8];
    for(int i=0; i<=nr_maxim_elem; i++)
        v[i]=0;
}

// constructorul de copiere
template <class Ttype>
Polinom <Ttype>:: Polinom (  Polinom <Ttype> & p)
{
    int n=p.grad_polinom();
    this->nr_maxim_elem=p.nr_maxim_elem;
    this->v=new Ttype[n+1];
    for( int i=0; i<=n; i++)
        this->v[i]=p.v[i];
}

//destructor
template <class Ttype>
Polinom <Ttype>::  ~Polinom()
{
    delete[] v;
}

// constructorul cu un parametru(nr_maxim_elem)
template <class Ttype>
Polinom <Ttype>:: Polinom::Polinom(int n)
{
    nr_maxim_elem=n;
    v=new Ttype[n+1];
    for(int i=0; i<=n; i++)
        v[i]=0;
}

// constructor cu doi parametri -nr_maxim_elem si vectorul a
template <class Ttype>
Polinom <Ttype>::  Polinom(int n, Ttype *a)
{
    nr_maxim_elem=n;
    v = new Ttype[n+1];
    for(int i=0; i<=n; i++)
        v[i]=a[i];
}

// calcularea gradului polinomului
template <class Ttype>
int Polinom <Ttype>::grad_polinom()
{
    int grad=0;
    for(int i=0; i<=nr_maxim_elem; i++)
    {
        if(v[i]!=0) //ultimul coeficient diferit de 0 indica gradul polinomului-indicele vectorului de coeficienti v
            grad=i;
    }
    return grad;
}

// adaugarea unui termen de grad i si coeficient coef
template <class Ttype>
void Polinom <Ttype>::adaugare_termen(int i, Ttype coef)
{
    if(i>this->grad_polinom()) //daca termenul pe care il adaug are gradul mai mare decat gradul curent al polinomului
    {
        Ttype *aux=new Ttype[i+1]; //aloc un vector in care pot adauga termenul de grad i
        int n=this->grad_polinom();
        nr_maxim_elem=i;
        for(int j=0; j<=n; j++)
        {
            aux[j]=v[j]; //copiez elementele din vectorul de coeficienti v in vectorul nou creat aux
        }
        for(int j=n+1; j<=i; j++)
            aux[j]=0; //copiez zeouri in rest, incepand de gradul polinomului +1
        delete[] v; //dezaloc vechiul vector de coeficienti
        v=aux; //identific vectorul v acum cu vectorul aux
    }
    v[i]=v[i]+coef; // incrementam coeficientul termenului de grad i cu coef
}

// eliminarea termenului de grad i
template <class Ttype>
void Polinom <Ttype>:: eliminare_termen(int i)
{
    if(i>=0 && i<=this->grad_polinom())
        v[i]=0;
}

// calculul polinomului intr-o valoare x data, de tip Ttype
template <class Ttype>
Ttype Polinom <Ttype>:: calcul_valoare(Ttype x)
{
    Ttype val=this->v[0],putere;
    int i, j, n=this->grad_polinom();
    for(i=1; i<=n; i++)
    {
        putere=1;
        if(this->v[i]!=0)
        {
            for(j=1; j<=i; j++)
                putere=putere*x;
            val=val+putere*(this->v[i]);
        }
    }
    return val;
}

//supraincarcarea operatorului de citire
template <class Ttype>
istream& operator>>(istream &c, Polinom <Ttype> &p)
{
    for(int i=0; i<=p.nr_maxim_elem; i++)
    {
        c>>p.v[i];
    }
    return c;
}

//supraincarcarea operatorului de afisare
template <class Ttype>
ostream &operator<<(ostream &co, Polinom <Ttype> &p)
{
    int i, n=p.grad_polinom();
    if(n==0)
    {
        co<<p.v[0]<<endl;
        return co;
    }
    if(p.v[n]!=1 && p.v[n]!=-1)
        co<<p.v[n];
    co<<"x";
    if(n!=1 && n!=-1)
        co<<"^"<<n;
    for(i=n-1; i>1; i--)
        if(p.v[i]!=0)
        {
            if(p.v[i]>0)
                co<<"+";
            if(p.v[i]!=1 && p.v[i]!=-1)
                co<<p.v[i];
            co<<"x^"<<i;
        }
    if(n!=1)
    {
        if(p.v[1]!=0)
        {
            if(p.v[1]>0)
                co<<"+";
            co<<p.v[1]<<"x";
        }
        if(p.v[0]!=0 )
        {
            if(p.v[0]>0)
                co<<"+";
            co<<p.v[0];
        }
    }
    co<<endl;
    return co;
}
// supraincararea operatorului []
template <class Ttype>
Ttype Polinom <Ttype >::operator [](int grad)
{
    if(grad>=0 && grad<=this->grad_polinom())
        return v[grad];
    return 0; //daca polinomul meu nu are un termen de un asemenea grad, coeficientul implicit este 0
}

// supraincarcarea operatorului =
template <class Ttype>
Polinom  <Ttype >& Polinom <Ttype>:: operator=(Polinom <Ttype >& p)
{
    int n=p.grad_polinom();
    int m=this->grad_polinom();
    int i;
    for(i=0; i<=m; i++)
        this->v[i]=0; //resetez vectorul de coeficienti ai polinomului curent la 0
    for(i=0; i<=n; i++)
        this->adaugare_termen(i, p.v[i]); // adaug termenii din polinomul p la polinomul curent
    return *this;

}

// supraincarcarea operatorului +
template <class Ttype>
Polinom <Ttype> & Polinom <Ttype>:: operator+( Polinom <Ttype> & p)
{
    int i, n, m, maxim, ok=0;
    n=this->grad_polinom();
    m=p.grad_polinom();
    if(n>m) //compar cele doua grade si memorez in variabila maxim maximul dintre cele doua
    {
        maxim=n;
        ok=1;
    }
    else maxim=m;
    Polinom <Ttype> *rezultat;
    rezultat=new Polinom <Ttype> [maxim];// acesta va fi polinomul rezultat in urma adunarii polinoamelor
    if(ok!=0) //daca gradul polinomului curent este mai mare
    {
        for(i=0; i<=m; i++) //pana la gradul polinomului p adun la coeficientii Polinomului rezultat coeficientii ambilor polinoame
            (*rezultat).v[i]=this->v[i]+p.v[i];
        for(i=m+1; i<=n; i++) //pana la gradul maxim-al polinomului curent- adun doar coeficientii polinomului curent
            (*rezultat).v[i]=this->v[i];
    }
    else // daca gradul polinomului p este mai mare
    {
        for(i=0; i<=n; i++) //pana la gradul polinomului curent adun la coeficientii Polinomului rezultat coeficientii ambilor polinoame
            (*rezultat).v[i]=this->v[i]+p.v[i];
        for(i=n+1; i<=m; i++) //pana la gradul maxim-al polinomului p- adun doar coeficientii polinomului p
            (*rezultat).v[i]=p.v[i];
    }
    return *rezultat; //returnez polinomul rezultat
}

// supraincarcarea operatorului *
template <class Ttype>
Polinom <Ttype> & Polinom <Ttype>:: operator*( Polinom <Ttype> & p)
{
    int i, j, n, m;
    n=this->grad_polinom();
    m=p.grad_polinom();
    Polinom <Ttype> *rezultat;
    rezultat=new Polinom <Ttype>[n+m];// acesta va fi polinomul rezultat in urma inmultirii polinoamelor
    for(i=0; i<=n; i++)
        for(j=0; j<=m; j++)
            (*rezultat).v[i+j]=(*rezultat).v[i+j]+this->v[i]*p.v[j]; //inmultesc pe rand coeficientii primului polinom cu fiecare din coeficientii celui de-al doilea polinom,inmultire prin care se vor obtine termeni de grad i+j
    return *rezultat;
}

//inmultirea unui polinom cu un scalar de tip Ttype
template <class Ttype>
Polinom <Ttype> & Polinom <Ttype>::operator*(Ttype scalar)
{
    int n=this->grad_polinom();
    for(int i=0; i<=n; i++)
        this->v[i]=this->v[i]*scalar;
    return (*this);
}

//supraincarcarea operatorului -, necesara pentru supraincarcarea operatorului /
template <class Ttype>
Polinom <Ttype>& Polinom <Ttype>:: operator-(Polinom <Ttype> & p)
{
    int i, n, m, maxim, ok=0;
    n=this->grad_polinom(); //memoram in n gradul descazutului
    m=p.grad_polinom(); //memoram in m gradul scazatorului
    if(n>m) //compar gradele celor doua polinoame si memorez in maxim gradul cel mai mare
    {
        maxim=n;
        ok=1;
    }
    else maxim=m;
    Polinom <Ttype> *rezultat;
    rezultat=new Polinom <Ttype>[maxim];// acesta va fi polinomul rezultat in urma scaderii polinoamelor
    if(ok!=0) //daca polinomul curent are gradul mai mare
    {
        for(i=0; i<=m; i++)
            (*rezultat).v[i]=this->v[i]- p.v[i]; //pana la gradul polinomului p-cel cu gradul mai mic, scad coeficientii
        for(i=m+1; i<=n; i++)
            (*rezultat).v[i]=this->v[i]; // in rest, pastrez gradul polinomului cu gradul mai mare- in acest caz, cel curent
    }
    else //daca polinomul p are gradul mai mare
    {
        for(i=0; i<=n; i++)
            (*rezultat).v[i]=this->v[i]-p.v[i]; //pana la gradul polinomului curent- cel cu gradul mai mic, scad coeficientii
        for(i=n+1; i<=m; i++)
            (*rezultat).v[i]=p.v[i]; // in rest, pastrez gradul polinomului cu gradul mai mare- in acest caz, p
    }
    return *rezultat;
}

//supraincarcarea operatorului /
template <class Ttype>
Polinom <Ttype> & Polinom  <Ttype> :: operator/(Polinom <Ttype> & p)
{
    Polinom <Ttype> copie (*this); //copie a polinomului
    int n, m;
    n=copie.grad_polinom(); //memoram in n gradul deimpartitului
    m=p.grad_polinom(); //memoram in m gradul impartitorului
    Polinom <Ttype >* rezultat;
    rezultat=new Polinom <Ttype>(n-m);// polinomul in care punem rezultatul final al impartirii-catul
    Polinom <Ttype> *temp; // polinom temporar in care se va memora coeficientul unei impartiri dintre doi polinomi cu cate un singur termen
    temp=new Polinom <Ttype>(n-m);
    while(n>=m)
    {
        temp=new Polinom <Ttype>(n-m); //polinomul temp este initializat de fiecare data pentru a putea fi refolosit
        (*temp).v[n-m]=(copie.v[n] / p.v[m]); //pastram in polinomul temp impartirea coeficientilor de grad maxim din cele doua polinoame
        (*rezultat)=((*rezultat) + (*temp)); //adunam la polinomul rezultat impartirea
        copie=(copie-((*temp)*p));  //scadem din copia polinomului produsul dintre impartitor si valoarea memorata in temp, apoi actualizam copia
        n=copie.grad_polinom(); //actualizam gradul polinomului copie-deimpartitul
    }
    return *rezultat; //returnam polinomul rezultat-catul
}

#endif // POLINOM_H
