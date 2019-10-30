#include <iostream>
#include <time.h>
#include <windows.h>
using namespace std;

#define Varsta_Maxima 60
#define LINII 20
#define COLOANE 20
class Tabela;
class Individ
{
    int i,j;
    char tip;
    int varsta;
    double energie;
    unsigned char viu;
public:
    Individ() {}
    Individ(int a,int b,char c );
    Individ& operator=(Individ &A);
    void hraneste(Tabela &x);
    void inmulteste(Tabela &x);
    int getI()
    {
        return this->i;
    }
    int getJ()
    {
        return this->j;
    }
    char getTip()
    {
        return this->tip;
    }
    int getVarsta()
    {
        return this->varsta;
    }
    double getEnergie()
    {
        return this->energie;
    }
    void setEnergie(double b)
    {
        this->energie = b;
    }
    unsigned char getViu()
    {
        return this->viu;
    }
    void afisareIndivid();
    void moare()
    {
        this->viu = 0;
    }
    void imbatraneste()
    {
        varsta += 5;
        energie -=10;
        if(varsta == Varsta_Maxima || energie <= 0)
        {
            moare();
        }
    }
    void ataca(Tabela &x);
};

void Individ::afisareIndivid()
{
    cout<<"\n";
    cout<<" Individul de pe linia "<<i<<" coloana "<<j<<" , caracteristici : \n -"<<tip<<" tip."<<"\n -"<<varsta<<" varsta. \n -"<<energie<<" energie \n";
    if(viu)
        cout<<"este viu!";
    else
        cout<<" A murit de curand!";
}
Individ &Individ::operator=(Individ &A)
{
    //cout<<"AM SCHIMBAT "<<i<<" col "<<j<<" cu "<<A.getI()<<" col "<<A.getJ();
    this->i = A.getI();
    this->j = A.getJ();
    this->tip = A.getTip();
    this->energie = A.getEnergie();
    this->viu = A.getViu();
    this->varsta = A.getVarsta();
    return *this;
}
Individ :: Individ(int i,int j,char tip)
{
    this->varsta=0;
    this->viu=1;
    this->energie=50;
    this->i = i;
    this->j = j;
    this->tip=tip;
}


class Tabela
{
    Individ v[(LINII+2)*(COLOANE+2)];
    int M[LINII+2][COLOANE+2]; // am creeat "o bordura " pentru a fi usor de determinat unde se termina matricea
    int copii[LINII+2][COLOANE+2]; // o copie a matricii de joc in care se salveaza pozitiile si tipurile copiilor urmand sa fie inserati in joc
    int totalIndivizi;
    friend class Individ;
public :
    void setCopii(int l,int c,int tip)
    {
        copii[l][c]=tip;
    }
    void NouaGeneratie()
    {
        for(int i=0; i<=LINII+1; i++)
        {
            for(int j=0; j<=COLOANE+1; j++)
            {
                copii[i][j]=0;
            }
        }
    }
    void PuneIndivid();
    // functia actualizare apeleaza ciclic functiile de hranire , imbatraneste , inmulteste si ataca
    void actualizare()
    {
        for(int i=0; i<totalIndivizi; i++)
        {
            v[i].hraneste(*this);
            v[i].imbatraneste();
        }
        for(int indv=0; indv<totalIndivizi; indv++)
        {
            v[indv].inmulteste(*this);

            for(int i=1; i<=LINII; i++)
            {
                for(int j=1; j<=COLOANE; j++)
                {
                    if(copii[i][j]!=0)
                        PuneIndivid(i,j,copii[i][j]);
                }
            }
        }
        for(int i=0; i<totalIndivizi; i++)
        {
            v[i].ataca(*this);
        }


    }
   // functia afisare pe langa bordura si tipul indivizilor coloreaza consola
    void afisare()
    { cout<<"\u001b[42m";
        cout<<"\n\n Avem "<<totalIndivizi<<" indivizi ";
        int nr=0;
        for(int i=0; i<=LINII+1; i++)
        {
            cout<<"\n";
            for(int j=0; j<=COLOANE+1; j++)
            {
                if(M[i][j]==1)
                {
                    if(v[nr].getViu() == 0)
                    {
                        M[i][j]=-1;
                        eliminaElement(i,j);
                        cout<<"_";
                    }
                    else {
                        char tip = v[nr].getTip();
                        if( tip == (char)232 )
                            cout<<"\u001b[31;1m\u001b[42m" << tip << "\u001b[0m\u001b[42m";
                        else
                            cout <<"\u001b[33;1m\u001b[42m"<< tip << "\u001b[0m\u001b[42m";
                    }
                    nr++;
                }
                else if(M[i][j]==0)
                {
                    cout<<"#";
                }
                else {
                    cout<<"_";
                }
            }
        }
        cout<<"\n\n\n\n";
        cout<<"\u001b[0m";
    }
   // functia initializare dupa creearea bordurii si spatiilor goale ,
   // parcurge toata matricea si pe fiecare pozitie stabileste prin randoom daca pune sau nu individ , daca pune stabileste si tipul
    void initializare()
    {
        int i,j;
        for(i=0; i<COLOANE+2; i++)
            M[0][i]=0;
        for(i=0; i<LINII+2; i++)
            M[i][COLOANE+1]=0;
        for(i=0; i<COLOANE+2; i++)
            M[LINII+1][i]=0;
        for(i=0; i<LINII+2; i++)
            M[i][0]=0;


        for(i=1; i<LINII+1; i++)
        {
            for(j=1; j<COLOANE+1; j++)
            {
                M[i][j]=-1;
            }
        }
        totalIndivizi=0;
        srand(time(NULL));

        for(i=1; i<=LINII; i++, Sleep(2))
        {
            srand(clock());
            for(int k=0; k<10000; k++) {}
            for(j=1; j<=COLOANE; j++)
            {
                srand(rand());
                //for(int k=0;k<10000;k++){ for(int k2=0;k2<1000;k2++){}}
                Sleep(1);
                srand(clock());
                int este = rand()%6;
                if(este==0)
                {
                    M[i][j]=1;
                    srand(rand());
                    int rasa=rand()%2;
                    if(rasa==0)
                    {
                        Individ x(i,j,157);
                        v[totalIndivizi++]=x;
                    }
                    else
                    {
                        Individ x(i,j,232);
                        v[totalIndivizi++]=x;
                    }
                }
            }
        }
    }
    // functie folosita pentru experimente
    void InitializareVida()
    {
        int i,j;
        for(i=0; i<COLOANE+2; i++)
            M[0][i]=0;
        for(i=0; i<LINII+2; i++)
            M[i][COLOANE+1]=0;
        for(i=0; i<COLOANE+2; i++)
            M[LINII+1][i]=0;
        for(i=0; i<LINII+2; i++)
            M[i][0]=0;


        for(i=1; i<LINII+1; i++)
        {
            for(j=1; j<COLOANE+1; j++)
            {
                M[i][j]=-1;
            }
        }

        totalIndivizi=0;
    }

    // functia pune in matricea de joc si in vectorul de indivizi un nou invid ( primeste ca parametrul si tipul pentru ca nu am stiut cum sa il transmit)
    void PuneIndivid(int L,int C, char Tip)
    {
        if(M[L][C] == -1)
        {
            int nr=0;
            for(int l=1; l<=L; l++)
            {
                for(int c=1; c<=COLOANE; c++)
                {
                    if(l==L && c > C)
                        break;
                    if(M[l][c] == 1)
                    {
                        nr++;
                    }

                }

            }
            int c=totalIndivizi;
            if(c!=nr)    // In cazul in care adaugam la final (nr=totalindivizi) evit folosirea operatorului de copiere inutil pentru ultimul element.
            {
                for(; c>=nr; c--)
                {
                    v[c]=v[c-1];
                }

                M[L][C]=1;
                Individ x(L,C,Tip);
                v[c+1]=x;
                totalIndivizi++;
            }
            else
            {
                M[L][C]=1;
                Individ x(L,C,Tip);
                v[c]=x;
                totalIndivizi++;
            }
        }
    }


    int (*getM())[COLOANE+2] {return this->M;}
    void adaugaIndivizExperimental()
    {

        M[1][1]=1;
        Individ x(1,1,157);
        v[0]=x;
        M[1][3]=1;
        Individ y(1,3,232);
        v[1]=y;
        M[2][3]=1;
        Individ x2(2,3,157);
        v[2]=x2;
        totalIndivizi = 3;
    }
    // elimina un element din vector prin parsarea elementelor si prin eliberarea zonei din matrice
    void eliminaElement(int i,int j)
    {
        int nr=-1;
        int l,c;
        for(l=1; l<=i; l++)
        {
            for(c=1; c<=COLOANE; c++)
            {
                if(l==i && c > j)
                    break;
                if(M[l][c]==1)
                    nr++;
            }
        }
        for(int elem=nr; elem<totalIndivizi; elem++)
        {
            v[elem]=v[elem+1];
        }
        M[i][j]=-1;
        totalIndivizi--;
    }

    /// Returneaza tipul individului de pe o pozitie din matrice ( din cand in cand astea imi dau segmentation fault i si j iau niste valori mari
                                                                  /// (ziua predarii ) inca nu am inteles de ce...
    char getTipul(int i,int j)
    {
        if (M[i][j] == -1) return 0;
        int nr=-1;
        for(int l=1; l<=i; l++)
        {
            for(int c=1; c<=COLOANE; c++)
            {
                if(l==i && c > j)
                    break;
                if(M[l][c]==1)
                    nr++;
            }
        }
        char a=v[nr].getTip();
        return a;
    }

    double getEnergie(int i,int j)
    {  if(M[i][j] == -1) return 0;
        int nr=-1;
        for(int l=1; l<=i; l++)
        {
            for(int c=1; c<=COLOANE; c++)
            {
                if(l==i && c > j)
                    break;
                if(M[l][c]==1)
                    nr++;
            }
        }
        double a= v[nr].getEnergie();
        return a;
    }


};

void Individ :: hraneste(Tabela &Mapa)
{
    int peLinie, peColoana;
    int (*M)[COLOANE+2] = Mapa.getM();
    double counter=0;
    if(M[i][j]==1){
            counter++;
    for(peLinie=i-1 ; peLinie <= i+1 ; peLinie ++ )
    {
        for(peColoana=j-1; peColoana<=j+1; peColoana++)
        {

            if(M[peLinie][peColoana] == -1 )
                counter++;
        }

    }}
    this->energie += counter;
}

// functie de inmultire  ce scade energia proportional cu varsta si numarul de fii.
void Individ :: inmulteste(Tabela &Mapa)
{
    int energieScazuta;
    Mapa.NouaGeneratie();
    if(Varsta_Maxima-varsta <=5 && Varsta_Maxima-varsta >0)
    {
        energieScazuta = 20;
    }
    else if(Varsta_Maxima-varsta > 5 && Varsta_Maxima-varsta <= 10)
    {
        energieScazuta = 15;
    }
    else if(Varsta_Maxima-varsta >10 && Varsta_Maxima-varsta <= 15)
    {
        energieScazuta=14;

    }
    else if(Varsta_Maxima-varsta > 15 && Varsta_Maxima-varsta <=20)
    {
        energieScazuta = 12;
    }
    else if(Varsta_Maxima-varsta >20 && Varsta_Maxima-varsta <= 25)
    {
        energieScazuta = 10;
    }
    else if(Varsta_Maxima-varsta > 25 && Varsta_Maxima-varsta <= 35)
    {
        energieScazuta = 7;
    }
    else
    {
        energieScazuta = 5;
    }


    int numar_fii=0;

    int (*M)[COLOANE+2]=Mapa.getM();

    if(varsta >= 1 && M[i][j]==1)
    {

        for(int i1=i-1; i1<=i+1; i1++)
        {
            for(int j2=j-1; j2<=j+1; j2++)
            {
                if(M[i1][j2] == -1 )
                {
                    Mapa.setCopii(i1,j2,(int)this->tip);
                    numar_fii++;
                }
            }
        }

    }
    this->energie -= numar_fii*energieScazuta;
    if(energie <= 0 )
        {moare(); Mapa.eliminaElement(i,j);}


}
 // functia ataca cauta in cele opt pozitii invecinate indivizi care sunt de rase diferite
 // si au energie mai putina si ii ataca ( atunci cand ataca un individ i se scade din energia proprie energia celui atacat)
void Individ :: ataca(Tabela &Mapa)
{
    int (*M)[COLOANE+2] = Mapa.getM();
    if(M[i][j]==1){
    for(int peLinie = i-1; peLinie<=i+1; peLinie++)
    {

        for(int peColoana = j-1; peColoana<=j+1; peColoana++)
        {

            if(M[peLinie][peColoana]==1)
            {
                if( (Mapa.getTipul(peLinie,peColoana) != Mapa.getTipul(i,j)) && (Mapa.getEnergie(i,j) > Mapa.getEnergie(peLinie,peColoana)) )
                {
                    //cout<<"\n   Individul  "<<i<<"  "<<j<<"de tip "<<Mapa.getTipul(i,j)<<"cu en:"<<Mapa.getEnergie(i,j)<<" l-a atacat pe  "<<peLinie<<" "<<peColoana<<"de tipul "<<Mapa.getTipul(peLinie,peColoana)<<" cu en:"<<Mapa.getEnergie(peLinie,peColoana);
                    this->energie -= Mapa.getEnergie(peLinie,peColoana);
                    //cout<<"\n energia lui "<<i<<" "<<j<<" a devenit "<<energie;
                    Mapa.eliminaElement(peLinie,peColoana);

                }
            }
        }
    }
    }
}






int main()
{  /// Se pot modifa numarul de linii si coloane din define ,
      /// Unele simulari din cand in cand  pot da crash , inca nu am descoperit bug-ul.
    Tabela Mapa;
    Mapa.initializare();

     int numarGeneratii;
     cout<<"\n Introduceti numarul de generatii dorit :";
     cin>>numarGeneratii;
     system("cls");
     while(numarGeneratii && cin.get()){
        system("cls");
        Mapa.actualizare();
        Mapa.afisare();
        numarGeneratii--;
     }


    return 0;
}
