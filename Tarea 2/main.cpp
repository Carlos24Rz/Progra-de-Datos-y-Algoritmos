#include <iostream>
#include <vector>

using namespace std;

// Variables para contar las comparaciones de busqueda
int comparacionesSecuencial=0;
int comparacionesBinaria=0;

// Complejidad: O(n^2)
int ordenaIntercambio(vector<int> v){

    int size = v.size();
    int comparaciones = 0;
    for(int i=0; i<size-1; i++)
        for(int j=i+1; j<size; j++)
            if(v.at(i)>v.at(j)){
                int temp = v.at(1);
                v.at(1) = v.at(j);
                v.at(j) = temp;
                comparaciones++;
            }
    return comparaciones;
}

// Complejidad: O(n^2)    Mejor caso: O(n)
int ordenaBurbuja(vector<int> &v){ 

    int comparaciones=0;
    bool swapped = true;
    int size = v.size();

    for(int i=0; i<size-1 && swapped; i++){
        swapped = false;                
        for(int j=0; j<size-i-1; j++)
            if(v.at(j) > v.at(j+1)){
                int temp = v.at(j);
                v.at(j) = v.at(j+1);
                v.at(j+1) = temp;
                swapped = true;         
                comparaciones++;
            } 
    }
    return comparaciones;
}

// void ordenaMerge(vector<int> &v) //Carlos
// {

// }

// Complejidad: O(n)
int busqSecuencial(vector<int> v, int x){

    int size = v.size();
    for(int i=0; i<size; i++){
        comparacionesSecuencial++;
        if(v.at(i) == x)
            return i;
    }
    return -1;
}


// Complejidad: O(logn)
int busqBinaria(vector<int> v, int left, int right, int number){

    comparacionesBinaria++;
    int mid = (left+right) / 2;

    if(left>right)
        return -1;

    if(number == v.at(mid))
        return mid;

    if(number < v.at(mid))
        return busqBinaria(v, left, mid-1, number);

    else // if(number > arr[mitad])
        return busqBinaria(v, mid+1, right, number);
    

}


int main(){

    cout << "\n------------------" << endl;

    vector<int> myVector;
    int n, temp;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> temp;
        myVector.push_back(temp);
    }
    cout << endl;

    int q;
    cin >> q;
    vector<int> consultasBusqueda;
    for(int i=0; i<q; i++){
        cin >> temp;
        consultasBusqueda.push_back(temp);
    }
    cout << endl;


    // Aqui mostramos las comparaciones de cada algoritmo
    cout << "\nALGORTIMOS DE ORDENAMIENTO" << endl;
    cout << ordenaIntercambio(myVector) << " " ;
    cout << ordenaBurbuja(myVector) << " " <<endl;
    // cout << ordenaMerge(myVector) << endl;
    // Nota: el ultimo ordenamiento debe pasarse por referencia en la funcion


    // for(auto element : myVector)
    //     cout << element << " ";


    // Aqui mostramos las q lineas con / posicion / comparacionesSecuencial / comparacionesBinaria
    cout << "\nResultados de la busqueda" << endl;
    for(int i=0; i<q; i++){
        cout << busqBinaria(myVector, 0, myVector.size(), consultasBusqueda.at(i)) << " " ;  // Se imprime la posicion
        busqSecuencial(myVector, consultasBusqueda.at(i));                                   // Se llama para contar las comparacionees
        cout << comparacionesSecuencial << " " ;
        cout << comparacionesBinaria << endl;
        comparacionesSecuencial=0; comparacionesBinaria=0;    // Se reinician los valores
    }

    cout << "\n------------------" << endl;

    return 0;
}