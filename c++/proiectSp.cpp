#include <iostream>
#include <cstring>
#include <fstream>
#include <ctime>
using namespace std;

ifstream f("cartii.txt");
int nrCarti; //numarul de carti din fisier, pus pe prima linie

class Carte {
    char* titlu;
    char* autor;
    float pret;
    int an;
    int anadd;
public:
    Carte() {};
    Carte(char*, char*, float, int, int);
    Carte(const Carte&);
    friend ostream& operator <<(ostream&, const Carte&);
    Carte& operator += (int);
    Carte& operator -= (int);
    char* getAutor(){return autor;};
    char* getTitlu(){return titlu;};
    float getPret(){return pret;};
    int getAnAdd(){return anadd;};
    int getAn(){return an;};
};

Carte::Carte(char* t, char* a, float p, int an, int anad)
{
    this->an = an;
    anadd = anad;
    pret = p;
    autor = new char[strlen(a) + 1];
    strcpy(autor, a);
    titlu = new char[strlen(t) + 1];
    strcpy(titlu, t);
}

Carte::Carte(const Carte& a)
{
    titlu = new char[strlen(a.titlu) + 1];
    strcpy(titlu, a.titlu);
    autor = new char[strlen(a.autor) + 1];
    strcpy(autor, a.autor);
    pret = a.pret;
    an = a.an;
    anadd = a.anadd;
}

ostream& operator <<(ostream& st, const Carte& a)
{
    st << a.titlu << endl << a.autor << endl << a.pret << endl << a.an << endl << a.anadd << endl;
    return st;
}

Carte& Carte::operator+=(int a)
{
    pret += pret * a / 100;
    return *this;
}

Carte& Carte::operator-=(int a)
{
    pret -= pret * a / 100;
    return *this;
}

Carte carti[100];


Carte citire() //citirea obiectelor de tip carte
{
    char a[100], t[100];
    float pr;
    int an, ad;
    f.get(t, 100);
    f.get();
    f.get(a, 100);
    f >> pr >> an >> ad;
    f.get();
    Carte c = Carte(t, a, pr, an, ad);
    return c;
}

void antet() {
    cout << "1. Adaugare carte" << endl;
    cout << "2. Stergere dupa cod" << endl;
    cout << "3. Afisare cea mai scumpa carte" << endl;
    cout << "4. Afisare cea mai ieftina carte" << endl;
    cout << "5. Afisare carte dupa autor" << endl;
    cout << "6. Afisare cea mai noua carte" << endl;
    cout << "7. Afisare cea mai veche carte" << endl;
    cout << "8. Valoarea totala a tuturor cartilor" << endl;
    cout << "9. Stergerea cartilor din biblioteca mai vechi de 10 ani" << endl;
    cout << "10. Afisare toate cartile" << endl;
    cout << "11. Majorare pret unei anumite cartii dupa cod cu un anumit procent" << endl;
    cout << "12. Reduce pretul unei anumite cartii dupa cod cu un anumit procent" << endl;
}

void adaugare()
{
    cout << endl << "ADAUGARE" << endl << endl;
    nrCarti++;
    char au[100], titlu[100];
    int an, anadd, cod;
    float pret;
    cout << "Introduceti titlul cartii: ";
    cin.get();
    cin.get(titlu, 100);
    cout << "Numele autorului: ";
    cin.get();
    cin.get(au, 100);
    cout << "Pretul cartii: ";
    cin >> pret;
    cout << "Anul aparitiei: ";
    cin >> an;
    cout << "Anul in care cartea a fost adaugata in librarie: ";
    cin >> anadd;
    carti[nrCarti - 1] = Carte(titlu, au, pret, an, anadd);
}

void stergere()
{
    cout << endl << "STERGERE DUPA COD" << endl << endl;
    cout << "Introduceti codul cartii pe care doriti s-o stergeti!" << endl;
    int k;
    cin >> k;
    k-=1;
    int j, ok = 0;
    if (k+1==nrCarti)
        ok=1;
    for (j = k; j < nrCarti-1; j++)
    {
        carti[j] = carti[j + 1];
        ok = 1;
    }
    if (ok == 0)
        {cout << "Cartea nu a fost gasita!";}

    else
        {cout << "Cartea a fost stearsa cu succes!";nrCarti-=1;}
    cout<<endl;
}

void scump()
{
    int id;
    float pret = carti[0].getPret();
    cout << endl << "AFISARE CEA MAI SCUMPA CARTE" << endl << endl;
    for (int i = 1; i < nrCarti; i++)
    {
        if (pret < carti[i].getPret())
        {
            pret = carti[i].getPret();
            id = i;
        }
    }
    cout << "Cea mai scumpa carte este " << carti[id].getTitlu() << " de " << carti[id].getAutor() << " la pretul de " << carti[id].getPret() << " lei" << endl;
}

void ieftin()
{
    int id;
    float pret = carti[0].getPret();
    cout << endl << "AFISARE CEA MAI IEFTINA CARTE" << endl << endl;
    for (int i = 1; i < nrCarti; i++)
    {
        if (pret > carti[i].getPret())
        {
            pret = carti[i].getPret();
            id = i;
        }
    }
    cout << "Cea mai ieftina carte este " << carti[id].getTitlu() << " de " << carti[id].getAutor() << " la pretul de " << carti[id].getPret() << " lei" << endl;

}

void autor()
{
    int i;
    char aut[100];
    cout << endl << "AFISARE DUPA AUTOR" << endl << endl;
    cout << "Introduceti pe care doriti sa-l afisati" << endl;
    cin.get();
    cin.get(aut, 100);
    cout << "Carti scrise de catre autor sunt: ";
    bool ok=true;
    for (i = 0; i < nrCarti; i++)
        if (strcmp(aut, carti[i].getAutor()) == 0)
        {
            if  (ok==false)
                cout<<", ";
            cout << carti[i].getTitlu();
            ok=false;}
    if (ok==true)
        {
            cout << "Autorul precizat nu se afla in baza de date!";
        }
    cout << endl;
}

void nou()
{
    int id;
    int max = carti[0].getAnAdd();
    cout << endl << "AFISARE CEA MAI NOUA CARTE" << endl << endl;
    for (int i = 1; i < nrCarti; i++)
    {
        if (max < carti[i].getAnAdd())
        {
            max = carti[i].getAnAdd();
            id = i;
        }
    }
    cout << "Cea mai noua carte introdusa in librarie este: " << carti[id].getTitlu() << " de " << carti[id].getAutor() << " introdusa in anul " << carti[id].getAnAdd() << endl;

}

void veche()
{
    int id;
    int min = carti[0].getAnAdd();
    cout << endl << "AFISARE CEA MAI VECHE CARTE" << endl << endl;
    for (int i = 0; i < nrCarti; i++)
    {
        if (min > carti[i].getAnAdd())
        {
            min = carti[i].getAnAdd();
            id = i;
        }
    }
    cout << "Cea mai veche carte introdusa in librarie este: " << carti[id].getTitlu() << " de " << carti[id].getAutor() << " introdusa in anul " << carti[id].getAnAdd() << endl;
}

void valoare()
{
    float pret = 0;
    cout << endl << "VALOAREA TOTALA" << endl << endl;
    for (int i = 0; i < nrCarti; i++)
        pret += carti[i].getPret();
    cout << "Valoare toatala: " << pret << endl;
}

void stergere2()
{
    int ancurent ;
    cout << endl << "STERGERE CARTI DE PESTE 10 ANI IN STOC" << endl << endl;
    time_t t = time(NULL);
	tm* timePtr = localtime(&t);
    ancurent=timePtr->tm_year+1900;
    int i, j, ok = 1;
    for(i=0;i<nrCarti;i++)
        if (carti[i].getAnAdd() < ancurent-10)
        {
            for (j = i; j <= nrCarti; j++)
                carti[j] = carti[j + 1];
            nrCarti--;
            i--;
            ok = 0;
        }
    if (ok == 1)
        cout << "Nu s-au gasit carti mai vechi de 10 ani in librarie!";
    else
        cout << "Cartile mai vechi de 10 ani au fost sterse cu succes!";
    cout<<endl;
}

void afisare()
{
    cout << endl << "AFISARE" << endl << endl;
    int i;
    for (i = 0; i < nrCarti; i++)
    {
        cout <<"COD: "<< i+1<< " Titlul: " << carti[i].getTitlu() << " scrisa de: " << carti[i].getAutor() << " in valoare de: " << carti[i].getPret() << " lei, aparuta in anul: " << carti[i].getAn() << " si introdusa in librarie in anul: " << carti[i].getAnAdd() << endl;
    }
}

void majorare()
{
    cout << endl << "MAJORARE" << endl << endl;
    int cod, procent;
    cout << "Introduceti codul carții:";
    cin >> cod;
    cout << "Introduceti procentul:";
    cin >> procent;
    cout << "Pretul pentru " << carti[cod - 1].getTitlu() << " de " << carti[cod - 1].getAutor() << " a fosr modificat de la " << carti[cod - 1].getPret() << " la ";
    carti[cod - 1] += procent;
    cout << carti[cod - 1].getPret() << endl << endl;
}

void reducere()
{
    cout << endl << "REDUCERE" << endl << endl;
    int cod, procent;
    cout << "Introduceti codul carții:";
    cin >> cod;
    cout << "Introduceti procentul:";
    cin >> procent;
    cout << "Pretul pentru " << carti[cod - 1].getTitlu() << " de " << carti[cod - 1].getAutor() << " a fosr modificat de la " << carti[cod - 1].getPret() << " la ";
    carti[cod - 1] -= procent;
    cout << carti[cod - 1].getPret() << endl << endl;
}

void optiune(int op)
{
    if (op == 1)
        adaugare();
    else if (op == 2)
        stergere();
    else if (op == 3)
        scump();
    else if (op == 4)
        ieftin();
    else if (op == 5)
        autor();
    else if (op == 6)
        nou();
    else if (op == 7)
        veche();
    else if (op == 8)
        valoare();
    else if (op == 9)
        stergere2();
    else if (op == 10)
        afisare();
    else if (op == 11)
        majorare();
    else if (op == 12)
        reducere();
    else
        cout <<endl<< "Iesire...";

}

void citireCarti(int n) //citirea vectorului cu carti
{
    for (int i = 0; i < n; i++)
        carti[i] = citire();
}

int main() {
    //inceput citire vector carti

    f >> nrCarti;
    f.get();
    citireCarti(nrCarti);
    //sfarsit citire vector cu carti

    int op;
    cout<<endl<<"ADMINISTRARE LIBRERIE"<<endl<<endl;
    antet();
    do
    {
        cout<<"-------------------------------------------------------------------";
        cout<<endl;
        cout << "Optiunea dumneavoastra este: ";
        cin >> op;
        optiune(op);
    }     while (op <= 12 && op > 0);

    //afisara in fisier la terminarea programului
    ofstream f("cartii.txt");
    f << nrCarti << endl;
    for (int i = 0; i < nrCarti; i++)
    {
        f << carti[i];
    }
    return 0;
}
