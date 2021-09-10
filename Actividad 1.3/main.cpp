
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include <vector>
#include "registro.h"

using namespace std;

vector<Registro> leerArchivo()
{
    vector<Registro> registro;
    string str;
    string file = "bitacora.txt";
    ifstream s(file);

    if (s.is_open())
    {
        int contador = 0;
        while (getline(s, str) && contador<10)
        {
            stringstream ss(str);
            string string[5];

            int i = 0;

            // getline(ss, string[i], ' ');
            
            for(int i = 0; i <= 4; i++){

                if(i==4)
                    getline(ss, string[i]);
                
                else
                    getline(ss, string[i], ' ');



                if(i==4)
                    cout << string[i] << endl;
                else
                    cout << string[i] << " " ;
            }
            contador++;

        }
    }

    return registro;
}

int main(){

    leerArchivo();
    return 1; 
}

