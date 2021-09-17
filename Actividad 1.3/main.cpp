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


// upOrDown
// 0 = Queremos buscar el numero mayor que el indice (Buscamos limite inferior)
// 1 = Queremos buscar el numero menor que el indice (Buscamos el limite superior)
// dayOrMonth
// 0 = Queremos buscar por mes
// 1 = Queremos buscar por dia
int binarySearch(vector<Registro> v, int left, int right, int number, int upOrDown, int dayOrMonth){

    int mid = (left+right) / 2;

    if(left>right && upOrDown==0)
        return left;    

    if(left>right && upOrDown==1)
        return right;    


    if(dayOrMonth == 0){
        if(number == v.at(mid).getMes())
            return mid;

        if(number < v.at(mid).getMes())
            return binarySearch(v, left, mid-1, number, upOrDown, dayOrMonth);

        else // if(number > arr[mitad])
            return binarySearch(v, mid+1, right, number, upOrDown, dayOrMonth);
    }

    else{ // dayOrMonth == 1
        if(number == v.at(mid).getDia())
            return mid;

        if(number < v.at(mid).getDia())
            return binarySearch(v, left, mid-1, number, upOrDown, dayOrMonth);

        else // if(number > arr[mitad])
            return binarySearch(v, mid+1, right, number, upOrDown, dayOrMonth);
    }


}

// Cuando un elemento se repite, se busca el indice inferior
// dayOrMonth
// 0 = Queremos buscar por mes
// 1 = Queremos buscar por dia
int lowerLimit(vector <Registro> v, int index, int dayOrMonth){
    
    if(index>0 && dayOrMonth==0){
        int magicNumber = v.at(index).getMes();
        while(v.at(index-1).getMes()==magicNumber){
            index--;
            // cout << "Indice: " << index << endl;
            if(index==0)
                return index;
        }
    }
    else if(index>0 && dayOrMonth==1){
        int magicNumber = v.at(index).getDia();
        while(v.at(index-1).getDia()==magicNumber){
            index--;
            if(index==0)    
                return index;
        }
    }
            
    return index;
}

// Cuando un elemento se repite, se busca el indice superior
int upperLimit(vector <Registro> v, int index, int dayOrMonth){
    
    cout << "Entrando al upper limit" << endl;

    if(index==v.size()-1)
        return index;

    if(index>0 && dayOrMonth==0){
        int magicNumber = v.at(index).getMes();
        while(v.at(index+1).getMes()==magicNumber){
            cout << "indice: " << index << endl;
            index++;
        }
            
    }

    else if(index>0 && dayOrMonth==1){
        int magicNumber = v.at(index).getDia();
        while(v.at(index+1).getDia()==magicNumber)
            index++;
    }
    return index;
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
    
    

    cout << "\n--------------------------" << endl;
    
    int mesInferior, mesSuperior, diaInferior, diaSuperior;

    cout << "Ingresa el mes inferior: ";    cin >> mesInferior;
    cout << "Ingresa el dia inferior: ";     cin >> diaInferior;
    cout << "Ingresa el mes superior: ";    cin >> mesSuperior;
    cout << "Ingresa el dia superior: ";    cin >> diaSuperior;

    // Se buscan los limites de ambos meses
    int indInferiorMes = binarySearch(r, 0, n-1, mesInferior, 0, 0);
    int downInferiorMes = lowerLimit(r, indInferiorMes, 0);
    int upInferiorMes = upperLimit(r, indInferiorMes, 0);

    int indSuperiorMes = binarySearch(r, 0, n-1, mesSuperior, 1, 0);
    int downSuperiorMes = lowerLimit(r, indSuperiorMes, 0);
    int upSuperiorMes = upperLimit(r, indSuperiorMes, 0);

    // Se imprimen los limites de ambos meses (BORRAR DESPUES)
    cout << "\nBinary search mes inferior: " << indInferiorMes << endl;
    cout << "Limite inferior del mes: " << downInferiorMes << endl;
    cout << "Limite superior del mes: " << upInferiorMes << endl;
    cout << "\nBinary search mes superior: " << indSuperiorMes << endl;
    cout << "Limite inferior del mes: " << downSuperiorMes << endl;
    cout << "Limite superior del mes: " << upSuperiorMes << endl;

    cout << "======================================" << endl;

    // Se buscan los limites de ambos dias
    int indInferiorDia = binarySearch(r, downInferiorMes, upInferiorMes, diaInferior, 0, 1);
    int downInferiorDia = lowerLimit(r, indInferiorDia, 1);

    cout << "INFERIOR FUNCION" << endl;

    // 1 1 12 30
    int indSuperiorDia = 0;

    if(upSuperiorMes==r.size()-1)
        indSuperiorDia = r.size()-1;
    else
        indSuperiorDia = binarySearch(r, downSuperiorMes, upSuperiorMes, diaSuperior, 1, 1);

    cout << "Funciona binary search: " << indSuperiorDia << endl;


    int upSuperiorDia = upperLimit(r, indSuperiorDia, 1);

    // Se imprime el lower limit del dia inferior, y el upper limit del dia superior
    // De estos limites se tendran que generar los registros
    // (BORRAR DESPUES)
    cout << "El dia inferior esta en la posicion: " << downInferiorDia << " y es: " << r.at(downInferiorDia).getDia() << endl;
    cout << "El dia superior esta en la posicion: " << upSuperiorDia << " y es: " << r.at(upSuperiorDia).getDia() << endl;


    cout << "\n**************************************" << endl;

    // Se muestran los registros (BORRAR DESPUES)
    cout << "\nR E G I S T R O S" << endl;

    for(int i=downInferiorDia; i<=upSuperiorDia; i++)
        cout << r.at(i).getRegistro() << endl;



    cout << "\n--------------------------" << endl;

    return 0; 
}



// NOTAS
// Revisar que en las busquedas funcionen bien los inferiores y superiores valores

