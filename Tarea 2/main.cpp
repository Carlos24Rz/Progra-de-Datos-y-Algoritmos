//Programa de ordenamiento y búsqueda.  
//Jose Angel Gonzalez Carrera - A01552274
//Carlos Eduardo Ruiz Lira - A01735706
//08 de septiembre, 2021


#include <iostream>
#include <vector>

using namespace std;

// Variables para contar las comparaciones de busqueda
int comparacionesSecuencial=0;
int comparacionesBinaria=0;

//Funcion que ordena un vector de enteros utilizando el algoritmo de intercambio y retorna el numero de comparaciones realizadas. 
//Entrada: vector de enteros
//Salida: numero de comparaciones realizadas para ordenar el vector.
// Complejidad: O(n^2)  
int ordenaIntercambio(vector<int> v){

    int size = v.size();
    int comparaciones = 0;
    for(int i=0; i<size-1; i++)
        for(int j=i+1; j<size; j++){
            if(v.at(i)>v.at(j)){
                int temp = v.at(1);
                v.at(1) = v.at(j);
                v.at(j) = temp;
            }
        comparaciones++;    
        }
    return comparaciones;
}

//Funcion que ordena un vector de enteros utilizando el algoritmo de ordenamiento burbuja y retorna el numero de comparaciones realizadas. 
//Entrada: vector de enteros
//Salida: numero de comparaciones realizadas para ordenar el vector.
// Complejidad: O(n^2)    Mejor caso: O(n)
int ordenaBurbuja(vector<int> v){ 

    int comparaciones=0;
    bool swapped = true;
    int size = v.size();

    for(int i=0; i<size-1 && swapped; i++){
        swapped = false;                
        for(int j=0; j<size-i-1; j++){
            if(v.at(j) > v.at(j+1)){
                int temp = v.at(j);
                v.at(j) = v.at(j+1);
                v.at(j+1) = temp;
                swapped = true;         
            } 
        comparaciones++;
        }
    }
    return comparaciones;
}

//Funcion auxiliar de método de ordenamiento merge, ordena dos subarreglos del original y los vuelve unir. Retorna el numero de comparaciones realizadas.
//Entrada: subvector izquierdo, subvector derecho, vector original que fue partido a la mitad.
//Salida: numero de comparaciones realizadas para ordenar el vector.
// Complejidad: O(n)    
int merge(vector<int> &l,vector<int> &r,vector<int> &v)
{
  int i,j,k,nL,nR;

  int comparacion = 0;
  

  i = 0; j = 0; k = 0; //apuntadores: i es para arreglo izquierdo, j para derecho, k para arreglo inicial
  nL = l.size(); nR = r.size(); // tamaño de los subarreglos

  while(i < nL && j < nR) // ambos apuntadores no deben ir mas alla del tamaño de los subarreglos.
  {
    if(l.at(i) <= r.at(j)) // encontrar cual elemento es el mas pequeño
    {
      v.at(k) = l.at(i);
      i++; // mover una unidad el apuntador usado
    }
    else // el elemento del subarreglo derecho resulto tener el elemento mas pequeño
    {
      v.at(k) = r.at(j);
      j++;
    }
    comparacion++;
    k++;
  }

  while (i < nL) // el apuntador izquierdo podria no haber acabado aunque el derecho ya lo haya hecho
  {
    v.at(k) = l.at(i);
    i++;
    k++;
  }
  while(j < nR) // el apuntador derecho podria no haber acabado aunque el izquierdo ya lo haya hecho
  {
    v.at(k) = r.at(j);
    j++;
    k++;
  }

  return comparacion;
}

//Funcion que ordena un vector de enteros utilizando el algoritmo recursivo de ordenamiento merge y retorna el numero de comparaciones realizadas. 
//Entrada: vector de enteros
//Salida: numero de comparaciones realizadas para ordenar el vector.
// Complejidad: O(nlogn)
int ordenaMerge(vector<int> &v)
{  
  vector<int> l,r;
  
  int comparacion = 0;

  int n = v.size();

  if(n < 2) return 0; //el vector ya esta ordenado pues solo consta de 1 o menos elementos // condicion inicial en recursion

  int mid = n/2;

  l.resize(mid);   //crear subarreglo 1
  r.resize(n-mid); //crear subarreglo 2

  for(int i = 0; i < mid ;i++) l.at(i) = v.at(i);  //popular subarreglo 1
  for(int i = mid; i < n;i++) r.at(i-mid) = v.at(i);   //popular subarreglo 2

  comparacion += ordenaMerge(l); // recursivo: separa arreglo a la mitad
  comparacion += ordenaMerge(r); // recursivo: separa arreglo a la mitad
  comparacion += merge(l,r,v); //une subarreglos ordenados
  
  return comparacion;
  
}


//Funcion que busca un elemento en un vector utilizando el algoritmo de busqueda secuencial y retorna la posicion del elemento en el vector. 
//Entrada: vector a buscar, elemento a buscar.
//Salida: posicion del elemento buscado en el vector. 
//Complejidad: O(n)
int busqSecuencial(vector<int> v, int x){

    int size = v.size(); // MODIFICACION 
    for(int i=0; i<size; i++){
        comparacionesSecuencial++;
        if(v.at(i) == x)
            return i;
    }
    return -1;
}

//Funcion que busca un elemento en un vector utilizando el algoritmo recursivo de busqueda binaria y retorna la posicion del elemento en el vector. 
//Entrada: vector a buscar, elemento a buscar.
//Salida: posicion del elemento buscado en el vector. 
// Complejidad: O(logn)
int busqBinaria(vector<int> v, int left, int right, int number){

    int mid = (left+right) / 2;

    if(left>right)
        return -1;

    if(number == v.at(mid))
    {
        comparacionesBinaria++;
        return mid;
    }

    if(number < v.at(mid))
    {
        comparacionesBinaria++;
        return busqBinaria(v, left, mid-1, number);
    }

    else // if(number > arr[mitad])
    {
        comparacionesBinaria++;
        return busqBinaria(v, mid+1, right, number);
    }

}


int main(){

    vector<int> myVector;
    int n;

    cin >> n;
    myVector.resize(n);

    for(int i=0; i<n; i++){
        cin >> myVector.at(i);
    }
    
    vector<int> consultasBusqueda;
    int q;

    cin >> q;
    consultasBusqueda.resize(q);
    
    for(int i=0; i<q; i++){
        cin >> consultasBusqueda.at(i);
    }


    // Aqui mostramos las comparaciones de cada algoritmo
    cout << endl;
    cout << ordenaIntercambio(myVector) << " " ;
    cout << ordenaBurbuja(myVector) << " ";
    cout << ordenaMerge(myVector) << endl;

    // Aqui mostramos las q lineas con / posicion / comparacionesSecuencial / comparacionesBinaria
    for(int i=0; i<q; i++){

        cout << busqBinaria(myVector, 0, n-1, consultasBusqueda.at(i)) << " " ;  // Se imprime la posicion
        busqSecuencial(myVector, consultasBusqueda.at(i));                                   // Se llama para contar las comparacionees
        cout << comparacionesSecuencial << " " ;
        cout << comparacionesBinaria << endl;
        comparacionesSecuencial=0; comparacionesBinaria=0;    // Se reinician los valores
    }

    return 0;
}