#include <iostream>
#include <utility>
#include <string>
using namespace std;



class Auto{

    private:
        string m_placa;   // es la key
        string m_marca;
        string m_modelo;
        int m_anio;

    public:
        Auto(){
            m_placa = "No placa";
            m_marca = "No marca";
            m_modelo = "No modelo";
            m_anio = 0;
        };

        Auto(string placa, string marca, string modelo, int anio){
            m_placa = placa;
            m_marca = marca;
            m_modelo = modelo;
            m_anio = anio;
        }

        string getPlaca(){
            return m_placa;
        }

        string getAuto(){
            return m_placa + " " + m_marca + " " + m_modelo + " " + to_string(m_anio);
        }
};



class HashTable{

    private:
        int size = 97;
        pair<Auto, char>  hashT[97];

        // flags para el char: 
        // o = ocupado
        // v= vacío
        // b= borrado

        // para el pair
        // pair.first = Auto
        // pair.second = char

    public:
        HashTable(){
            for(int i=0; i<97; i++)
                hashT[i] = make_pair(Auto(), 'v');
        };

        // hash function
        int hashCode(string placa){
            // some computation
            
            return 0;
        }

        // NOTA: LA LLAVE ES: car.getPlaca() -----------------------------

        // insertar y eliminar requieren de la busqueda
        int search(Auto car){
            // obtener el hashcode
            // NOTA, IMPORTANTE VERIFICAR LA FLAG DEL ELEMENTO PAIR

            // comparar el hashcode con la posicion del array
            // si es el elemento buscado, se termina
            // si no, se mueve a la siguiente casilla

            // si se llego a una posicion vacia o a la direccion base, no esta el elemento
            return 0;
        }


        void ins(Auto car){
            // Se debe llamar a hashCode() para generar el codigo que debe ser insertado en el array
            // NOTA, IMPORTANTE VERIFICAR LA FLAG DEL ELEMENTO PAIR
            // En esta parte se deben manejar las colisiones

            // al final deberia quedar algo como:   
            // hastT[hCode] = make_pair(car, flag);

        }

        void del(Auto car){
            // Se debe llamar a hashCode() para generar el codigo que debe ser insertado en el array
            // NOTA, IMPORTANTE VERIFICAR LA FLAG DEL ELEMENTO PAIR

        }

        void print(){

            // NOTA, IMPORTANTE VERIFICAR LA FLAG DEL ELEMENTO PAIR

            for(int i=0; i<97; i++){

                cout << i << " " ;
                if(hashT[i].second == 'v')
                    cout << hashT[i].first.getAuto();
                
                cout << endl;
            }
        }
};





int main(){

    HashTable myHashTable;

    myHashTable.print();



    cout << endl;

    return 0;
}

