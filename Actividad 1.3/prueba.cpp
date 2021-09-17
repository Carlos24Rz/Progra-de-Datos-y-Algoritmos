#include <iostream>
#include <vector>

using namespace std;

// 0 = Queremos buscar el numero mayor que el indice (Buscamos limite inferior)
// 1 = Queremos buscar el numero menor que el indice (Buscamos el limite superior)
// El upDown es importante
int binarySearch(vector<int> v, int left, int right, int number, int upDown){

    int mid = (left+right) / 2;

    if(left>right && upDown==0)
        return left;    

    if(left>right && upDown==1)
        return right;    


    if(number == v.at(mid))
        return mid;

    if(number < v.at(mid))
        return binarySearch(v, left, mid-1, number, upDown);

    else // if(number > arr[mitad])
        return binarySearch(v, mid+1, right, number, upDown);
}

// Cuando un elemento se repite, se busca el indice inferior
int limitDown(vector <int> v, int index){
    int magicNumber = v.at(index);

    if(index>0)
        while(v.at(index-1)==magicNumber){
            index--;
            if(index==0)
                return index;
        }
            

    return index;
}

// Cuando un elemento se repite, se busca el indice superior
int limitUp(vector <int> v, int index){
    int magicNumber = v.at(index);
    // cout << "Size in Limit Up: " << v.size() << endl;

    if(index==v.size()-1)
        return index;

    if(index>0)
        while(v.at(index+1)==magicNumber)
            index++;
            
    return index;
}




int main(){

    cout << "\n------------------------------" << endl;

    // vector <int> arr = {1,2,2,2,3,4,5,5,6,7,7,8,8};
    vector <int> arr = {3,5,5,6,6,6,9,9,10,11,11,11,15,20,20,27,29,30};

    int number = 1;

    int indexBusqueda = binarySearch(arr, 0,arr.size()-1, number, 0);
    cout << "Funciono binarySearch!" << endl;

    int inferior = limitDown(arr, indexBusqueda);
    cout << "Funciono inferior!" << endl;

    int superior = limitUp(arr, indexBusqueda);
    cout << "Funciono superior!" << endl;

    cout << "Mi numero es: " << number << endl;
    cout << "Binary Search: " << indexBusqueda << endl;
    cout << "Respuesta " << arr[indexBusqueda] << endl;
    cout << "El down limit es: " << inferior << endl;
    cout << "El up limit es: " << superior << endl;








    cout << "\n------------------------------" << endl;

    return 0;
}