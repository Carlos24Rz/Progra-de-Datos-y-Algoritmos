#include "resumen.h"


class HashTable{

    private:
                // 32768
        int size = 32749;
        pair<Resumen, char>  hashT[32749];

        // flags para el char: 
        // o = ocupado
        // v= vacío

    public:
        HashTable(){
            for(int i=0; i<size; i++)
                hashT[i] = make_pair(Resumen(), 'v');
        };

        // Descripcion: Funcion hash que genera un hashcode
        // Entrada: llave (red)
        // Salida: hashCode
        // Complejidad: O(n)
        int hashCode(string red){

            int firstPoint = red.find('.');
            string red1 = red.substr(0, firstPoint);
            string red2 = red.substr(firstPoint+1);

            string red3 = red1 + red2;
            
            int redHash = stoi(red3);

            
            int mod = redHash % size;
            
            return mod;
        }

        // NOTA: next position = (i+1)%N, where N=numberElements

        // Descripcion: Buscar un elemento de acuerdo a su llave (red)
        // Entrada: llave del elemento (placa)
        // Salida: objeto resumen encontrado
        // Complejidad: O(n)
        Resumen* search(string red){

            // Sacar hashC
            int hashC = hashCode(red);

            // HashC vacio
            if(hashT[hashC].second == 'v'){
                cout << "Dato no encontrado" << endl;
                return NULL;
            }
            
            // HashC ocupada
            else{
                // Resulta que el hashC tiene la misma placa que la llave
                if(red == hashT[hashC].first.m_red){
                    return &hashT[hashC].first;
                }
                
                // El hashC no tiene la misma placa que la llave
                else{
                    // se debe recorrer todo hasta encontrar la placa, 
                    // encontrar una casilla vacia, o haber recorrido todo el arreglo
                    int temp = (hashC+1)%size; 
                    while(hashT[temp].second == 'o' && temp!=hashC){

                        // Se encuentra la placa al recorrer a la derecha
                        if(red == hashT[temp].first.m_red)
                            return &hashT[hashC].first;
                        
                        temp = (temp+1)%size;
                    }
                    cout << "Dato no encontrado" << endl;
                    return NULL;
                }
            }
        }


        // Descripcion: Insertar un dato en la estructura de 
        // Entrada: El objeto a insertar que tiene su llave (red)
        // Salida: Nada
        // Complejidad: O(n)
        void ins(Resumen resumen){
            // Guardar el indice
            int hashC = hashCode(resumen.m_red);

            // Casilla hashC vacia
            if(hashT[hashC].second == 'v'){
                hashT[hashC] = make_pair(resumen, 'o');
                return;
            }

            // Casilla hashC ocupada
            else{
                int temp = (hashC+1)%size;
                while(hashT[temp].second == 'o' && temp!=hashC) {
                    temp = (temp+1)%size;
                }

                if(hashT[temp].second == 'v'){
                    hashT[temp] = make_pair(resumen, 'o');
                    return;
                }
                else{
                    cout << "Tabla llena, imposible insertar" << endl;
                }
            }
        }


};
