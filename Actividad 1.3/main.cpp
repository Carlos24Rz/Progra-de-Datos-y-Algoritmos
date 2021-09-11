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

int main()
{
    vector<Registro> r = leerArchivo();
    
    return 1; 
}

