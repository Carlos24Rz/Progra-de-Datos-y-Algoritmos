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
        
        while (getline(s, str))
        {
            stringstream ss(str);
            string fecha[3];
            string string[5];
            
            for(int i = 0; i < 5; i++)
            {
                if(i==4)
                    getline(ss, string[i]);
                
                else
                    getline(ss, string[i], ' ');
            }


            stringstream sss(string[2]);

            for(int i = 0; i < 3; i++){
                getline(sss,fecha[3], ';');
            }

            Registro r(
                string[0],
                stoi(string[1]),
                stoi(fecha[0]),
                stoi(fecha[1]),
                stoi(fecha[2]),
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
    cout << r[0].getRegistro() << endl;
    return 1; 
}

