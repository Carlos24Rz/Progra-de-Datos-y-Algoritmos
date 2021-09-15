#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>
#include "registro.h"

using namespace std;

//Funcion que guarda contenido de archivo txt en un vector
vector<Registro> leerArchivo()
{
    vector<Registro> registro;
    string str;
    string file = "bitacora.txt";
    ifstream s(file);

    if (s.is_open())
    {
        while (getline(s, str))
        {

            stringstream ss(str);
            string fechas[3];
            string fecha;
            string string[5];
            
            for(int i = 0; i < 5; i++)
            {
                if(i==4)
                    getline(ss, string[i]);
                
                else
                    getline(ss, string[i], ' ');
            }
            
            fecha = string[2];

            stringstream sss(fecha);

            for(int i = 0; i < 3; i++){
                getline(sss, fechas[i], ':');
            }

            Registro r(
                string[0],
                stoi(string[1]),
                stoi(fechas[0]),
                stoi(fechas[1]),
                stoi(fechas[2]),
                string[3],
                string[4]
            );

            registro.push_back(r);

        }
    }

    return registro;
}

void merge(vector<Registro> &v, int l, int m, int r) {
   int i, j, k, nl, nr;
   //size of left and right sub-arrays
   nl = m-l+1; nr = r-m;
   vector<Registro> larr,rarr;
   //fill left and right sub-arrays
   for(i = 0; i<nl; i++)
      larr.push_back(v[l+i]);
   for(j = 0; j<nr; j++)
      rarr.push_back(v[m+1+j]);
   i = 0; j = 0; k = l;
   //marge temp arrays to real array
   while(i < nl && j<nr) {
      if(larr[i] <= rarr[j]) {
         v[k] = larr[i];
         i++;
      }else{
         v[k] = rarr[j];
         j++;
      }
      k++;
   }
   while(i<nl) {       //extra element in left array
      v[k] = larr[i];
      i++; k++;
   }
   while(j<nr) {     //extra element in right array
      v[k] = rarr[j];
      j++; k++;
   }
}

void mergeSort(vector<Registro> &v, int l, int r) {
   int m;
   if(l < r) {
      int m = l+(r-l)/2;
      // Sort first and second arrays
      mergeSort(v, l, m);
      mergeSort(v, m+1, r);
      merge(v, l, m, r);
   }
}

int main()
{
    vector<Registro> r = leerArchivo();
    
    int n = r.size();
    
    mergeSort(r, 0, n-1);

    ofstream Myfile("ordenado.txt");

    for (int i = 0; i < n; i++)
    {
      Myfile << r.at(i).getRegistro() << endl;
    }

    Myfile.close();
    
    

    return 0; 
}

