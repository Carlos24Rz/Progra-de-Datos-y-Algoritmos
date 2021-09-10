
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
            string string[4];

            int i = 0;

            getline(ss, string[i++], ' ');
            
            for(int i = 0; i < 4; i++) cout << string[i] << endl;;
        }
    }

    return registro;
}

int main(){

    leerArchivo();
    return 1; 
}

