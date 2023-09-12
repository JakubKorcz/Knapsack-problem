#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
#include <chrono>

using namespace std;

int** tab_el;
int** plecak;
int** pomplecak;
double* opl;
int** macierz;

void swap(int a,int b)
{
     for(int i=0;i<3;i++)
    {
        int pom = tab_el[a][i];
        tab_el[a][i] = tab_el[b][i];
        tab_el[b][i] = pom;
    }
     double pom1 = opl[a];
     opl[a] = opl[b];
     opl[b] = pom1;
}

void stworzplik()
{
    int il_el=20;
    int poj_plecaka = 90;
    
    fstream plik;
    srand(time(NULL));
    plik.open("dane.txt", ios::trunc|ios::out);
    if (plik.good() == true)
    {
        plik << il_el << " " << poj_plecaka << endl;;
        for(int i=0;i<poj_plecaka;i++)
        {
        //waga//wartosc
            int liczba = rand()%50+1;
            int liczba1 = rand() % 30 + 1;
            plik << liczba <<" " << liczba1<<endl;
        
        
        } 
        }
    else
    {
        cout << "Cos sie zjebalo kurwa mac,aksgdu\n";
    }
    plik.close();
}

void wypisz(int p)
{
    cout << endl;
    cout <<"\tZawartosc plecaka: "<< endl;   
    cout << "\t" << "Id" << "\t" << "Waga" << "\t" << "Wartosc" << endl;
    for (int i = 0; i < p; i++)
        cout << "\t" << plecak[i][0]<<"\t" << plecak[i][1]<<"\t" << plecak[i][2]<<endl;
}

void p_d(int poj, int il)
{
    macierz = new int* [il+1];
    for(int i=0;i<=il;i++)
    {
        macierz[i] = new int[poj+1];
        for (int j = 0; j <= poj; j++)
        {
            if (i == 0 || j == 0)
            {
                macierz[i][j] = 0;
            }
            else
            {    
                if (tab_el[i-1][1] > j)
                macierz[i][j] = macierz[i - 1][j];
                else
                {      
                    if (macierz[i - 1][j - tab_el[i - 1][1]] + tab_el[i - 1][2] > macierz[i-1][j])
                        macierz[i][j] = macierz[i - 1][j - tab_el[i - 1][1]] + tab_el[i - 1][2];
                    else { macierz[i][j] = macierz[i - 1][j]; }

                }
            }
        }
    }

   /* cout << "-----------Programowanie dynamiczne-----------" << endl;
    for(int i=0;i<=il;i++)
    {
        for (int j = 0;j<=poj;j++)
        {
            cout << macierz[i][j] << "\t";
        }
        cout << endl;
    }*/

}

void algorytm_zachlanny(int poj,int il)
{   
for(int i=0;i<il;i++)
    for(int j=0;j<il-1;j++)
    {
        if (opl[j] < opl[j+1])
            swap(j, j+1);
    }

int cur_w=0;
int val=0;
int pom = 0;

for(int i=0;i<il;i++)
{
    if (cur_w + tab_el[i][1] <= poj)
    {
        cur_w += tab_el[i][1];
        val+= tab_el[i][2];
        plecak[pom][0] = tab_el[i][0]+1;
        plecak[pom][1] = tab_el[i][1];
        plecak[pom][2] = tab_el[i][2];
        pom++;
    }
}

//wypisz(pom);
cout << endl;
cout << "Maksymalna wartosc: \t" << val<<endl;
cout << "Waga: \t\t\t" << cur_w;
cout << endl;
}

void algorytm_siłowy(int poj, int il)
{
    int cur_w = 0;
    int il_it = 0;//ilosc elementow w plecaku
    int max_w=0;
    int max_v=0;
    int val = 0;
    int pom = 0;
    il = (double)il;
    int b=0;//wskazuje na wlasciwy element tablicy

    int a = pow(2.0, il);
 
    for(int i=1;i<a;i++)
    {
        int liczba = i;
        while(liczba!=0)
        {
           if(liczba%2==1)
           {
               if (tab_el[b][1] + cur_w <= poj)
               {
                   cur_w += tab_el[b][1];
                   val += tab_el[b][2];
                   pomplecak[pom][0] = tab_el[b][0] + 1;
                   pomplecak[pom][1] = tab_el[b][1];
                   pomplecak[pom][2] = tab_el[b][2];
                   b++;
                   il_it++;
           }
               else break;
           }
           else   b++;
            
           liczba = liczba / 2;
          
        } 
        if(max_v<val)
        {
            max_w = cur_w;
            max_v = val;
            pom = il_it;
            for (int i = 0; i < il_it; i++)
            {
                plecak[i][0] = pomplecak[i][0];
                plecak[i][1] = pomplecak[i][1];
                plecak[i][2] = pomplecak[i][2];
            }       
        }
        val = 0;
        cur_w = 0;
        b = 0;
        il_it = 0;
    }  
    
    cout << "-----------Algorytm silowy-----------" << endl;
    //wypisz(pom);
    cout << endl;
    cout << "Maksymalna wartosc: \t" << max_v << endl;
    cout << "Waga: \t\t\t" << max_w;
    cout << endl;
}

int main()
{
    int poj_plecak,il_el;
    int a, b;
    int czas,czas1,czas2;
    
    stworzplik();
    fstream plik;
    plik.open("dane.txt", ios::in);
    if (plik.good()==true)
    {
        plik >>il_el >> poj_plecak;
        tab_el = new int*[il_el];
        plecak = new int* [il_el];
        opl = new double[il_el];
        pomplecak = new int* [il_el];
        for (int i = 0; i < il_el; i++)
        {
            tab_el[i] = new int[3];
            plecak[i] = new int[3];
            pomplecak[i] = new int[3];
            tab_el[i][0] = i;
            plik >> tab_el[i][1] >> tab_el[i][2];
            opl[i] = (double)tab_el[i][2] / (double)tab_el[i][1];
        }

        cout << "------------Lista przedmiotow----------- " << endl;
        cout << endl;
        cout<<"\t" << "Id" << "\t" << "Waga" << "\t" << "Wartosc" << endl;
        for(int i=0;i<il_el;i++)
        {
            cout <<"\t" <<tab_el[i][0]+1 << "\t" << tab_el[i][1] << "\t" << tab_el[i][2] << endl;      
        }
        cout << endl;
        
        auto begin = chrono::high_resolution_clock::now();
        algorytm_siłowy(poj_plecak, il_el);
        auto end = chrono::high_resolution_clock::now();
        auto elapsed = chrono::duration_cast<chrono::nanoseconds>(end - begin);
        czas = elapsed.count();
        cout << endl;

        auto begin1 = chrono::high_resolution_clock::now();
        p_d(poj_plecak, il_el);
        auto end1 = chrono::high_resolution_clock::now();
        auto elapsed1 = chrono::duration_cast<chrono::nanoseconds>(end1 - begin1);
        czas1 = elapsed1.count();

        cout << endl;
      // algorytm_zachlanny(poj_plecak, il_el);
       cout << endl;
      
        cout << "-----------Algorytm zachlanny-----------" << endl;
        auto begin2 = chrono::high_resolution_clock::now();
        algorytm_zachlanny(poj_plecak, il_el);
        auto end2 = chrono::high_resolution_clock::now();
        auto elapsed2 = chrono::duration_cast<chrono::nanoseconds>(end2- begin2);
        czas2 = elapsed2.count();

        cout << endl;
        
        cout << czas << endl;
        cout << czas1 << endl;
        cout << czas2 << endl;
    }
    else
    {
        cout << "Cos sie zjebalo kurwa mac\n";
    }
    plik.close();

}


