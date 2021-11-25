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

        void setAuto(string placa, string marca, string modelo, int anio){
            m_placa = placa;
            m_marca = marca;
            m_modelo = modelo;
            m_anio = anio;
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
            for(int i=0; i<size; i++)
                hashT[i] = make_pair(Auto(), 'v');
        };

        // hash function
        int hashCode(string placa){

            int counter = 0;

            for(char c : placa)
                counter += c;

            int mod = counter % size;
            return mod;
        }

        // NOTA: next position = (i+1)%N, where N=numberElements

        // insertar y eliminar requieren de la busqueda
        string search(string placa){

            // Guardar el indice
            int hashC = hashCode(placa);

            // Verificar si la casilla del hashC esta vacia
            if(hashT[hashC].second == 'v')
                return "dato no encontrado";
            
            // Verificar si la casilla del hashC esta ocupada
            // if(hashT[hashC].second == 'o')
            else{

                // Resulta que el hashC tiene la misma placa que la llave
                if(placa == hashT[hashC].first.getPlaca()){
                    return hashT[hashC].first.getAuto();
                }

                // El hashC no tiene la misma placa que la llave
                else{
                    // se debe recorrer todo hasta encontrar la placa, 
                    // encontrar una casilla vacia, o haber recorrido todo el arreglo
                    // next position = (i+1)%N,
                    int temp = (hashC+1)%size; 
                    while(hashT[temp].second != 'v' && temp!=hashC){

                        // Se encuentra la placa al recorrer a la derecha
                        if(placa == hashT[temp].first.getPlaca())
                            return hashT[temp].first.getAuto();
                        
                        // next position = (i+1)%N
                        temp = (temp+1)%size;
                    }
                    return "dato no encontrado";
                }
            }
            // obtener el hashcode
            // NOTA, IMPORTANTE VERIFICAR LA FLAG DEL ELEMENTO PAIR
            // comparar el hashcode con la posicion del array
            // si es el elemento buscado, se termina
            // si no, se mueve a la siguiente casilla
            // si se llego a una posicion vacia o a la direccion base, no esta el elemento
            return 0;
        }


        void ins(Auto car){
            // Guardar el indice
            int hashC = hashCode(car.getPlaca());
            // cout << "Insertar: " << hashC << endl;

            // Si la casilla del hashC esta vacia o borrada, inserta el valor
            if(hashT[hashC].second == 'v' || hashT[hashC].second == 'b'){
                hashT[hashC] = make_pair(car, 'o');
                return;
            }

            // Si la casilla del hashC esta ocupada, se debe recorrer el hashT
            else{
                int temp = (hashC+1)%size; 
                while(hashT[temp].second == 'o' && temp!=hashC) {
                    
                    // Si la placa ya se encuentra en el hash, se cierra
                    if(hashT[temp].first.getPlaca() == car.getPlaca()){
                        cout << "imposible insertar, placa duplicada" << endl;
                        return;
                    }
                    
                    // next position = (i+1)%N
                    temp = (temp+1)%size;
                }

                if(hashT[temp].second != 'o'){
                    hashT[temp] = make_pair(car, 'o');
                    return;
                }
                else{ // temp==hashC
                    cout << "Tabla llena, imposible insertar" << endl;
                    return;
                }
            }
        }


        void del(string placa){
            
            // Guardar el indice
            int hashC = hashCode(placa); 
            // cout << "Hashcode: " << hashC << endl;
            // cout << "Flag del hash code: " << hashT[hashC].second << endl;

            // Cuando la casilla a eliminar coincide con su hashC y esta ocupada
            if(hashT[hashC].second == 'o' && hashT[hashC].first.getPlaca() == placa){
                
                hashT[hashC].second = 'b';
                // cout << "Flag del elemento: " << hashT[hashC].second << endl;
                // cout << "Elemento eliminado: " << hashT[hashC].first.getAuto() << endl;
                cout << "Elemento eliminado" << endl;
                return;
                
            }
            
            // Cuando se debe recorrer a la derecha
            else{
                int temp = (hashC+1)%size; 
                while(hashT[temp].second != 'v' && temp!=hashC) {

                    if(hashT[temp].second == 'o' && hashT[temp].first.getPlaca() == placa){
                        // cout << "Se elimino el elemento[" << temp << "]  " << hashT[temp].first.getAuto() << endl;
                        hashT[temp].second = 'b';
                        cout << "Elemento eliminado" << endl;
                        return;
                    }

                    // next position = (i+1)%N
                    temp = (temp+1)%size;
                }
                cout << "Elemento no encontrado" << endl;

            }

        }


        void print(){

            // NOTA, IMPORTANTE VERIFICAR LA FLAG DEL ELEMENTO PAIR
            cout << "-------------" << endl;
            cout << "Printing" << endl;
            for(int i=0; i<size; i++){

                
                if(hashT[i].second == 'o') {
                    cout << i << " " ;
                    cout << hashT[i].first.getAuto();
                    cout << endl;
                }

            }
            cout << "-------------" << endl;
            
        }




};





int main(){

    HashTable myHashTable;

    cout << "\n--------" << endl;

    int input = 10;
    string placa, marca, modelo;
    int anio;
    Auto miAuto;


    while(input != 0) {
        cin >> input;
        
        switch(input) {
            case 1: {
                // cout << "Insertar" << endl;
                cin >> placa >> marca >> modelo >> anio;
                // Auto miAuto(placa, marca, modelo, anio);
                miAuto.setAuto(placa, marca, modelo, anio);
                // Borrar si el objeto no se puede insertar
                myHashTable.ins(miAuto);
                break;
            }
            case 2: {
                cout << "Delete:" << endl;
                cin >> placa;
                myHashTable.del(placa);
                break;
            }
            case 3: {
                // cout << "Imprimir" << endl;
                myHashTable.print();
                break;
            }
            case 4: {
                cout << "Search: " << endl;
                cin >> placa;
                cout << myHashTable.search(placa) << endl;
            }
        }
    }

    cout << endl;

    return 0;
}

