// Programa que trabaja con un grafo dirigido de IPs
// Carlos Daniel Diaz Arrazate - A01734902
// Jose Angel Gonzalez Carrera - A01552274
// Carlos Eduardo Ruiz Lira    - A01735706
// 23/11/21
#include <bits/stdc++.h>
#include "class.h"
using namespace std;

// Descripcion: Obtener red con mayor cantidad de host 
// Entrada: Vector de nodos de red, nodo de red
// Salida: Nada
// Complejidad: O(1)
void getMaxRed(vector<RedNode*> &vectorRed, RedNode* redNode) {
  if(vectorRed.empty()) {
    vectorRed.push_back(redNode);
    return;
  }
  if(vectorRed[0]->m_counter == redNode->m_counter){
    if (vectorRed[0]->m_data == redNode->m_data) return;
    vectorRed.push_back(redNode);
    return;
  }
  if(vectorRed[0]->m_counter < redNode->m_counter) {
    vectorRed.clear();
    vectorRed.push_back(redNode);
  } 
  // En caso de que el counter del redNode sea menor a los del vector no hace nada
}


// Descripcion: Obtener host con mayor cantidad de red 
// Entrada: Vector de nodos de host, nodo de host, nodo de red, vector de nodos de red
// Salida: Nada
// Complejidad: O(1)
void getMaxHost(vector<HostNode*> &vectorHost, HostNode* hostNode, RedNode* tmpRed, vector<RedNode*> &vecRedAux) {
  if(vectorHost.empty()) {
    vectorHost.push_back(hostNode);
    vecRedAux.push_back(tmpRed);
    return;
  }
  if(vectorHost[0]->m_counter == hostNode->m_counter){
    if (vecRedAux[0]->m_data == tmpRed->m_data && vectorHost[0]->m_data == hostNode->m_data) return;
    vectorHost.push_back(hostNode);
    vecRedAux.push_back(tmpRed);
    return;
  }
  if(vectorHost[0]->m_counter < hostNode->m_counter) {
    vectorHost.clear();
    vecRedAux.clear();
    vectorHost.push_back(hostNode);
    vecRedAux.push_back(tmpRed);
  } 
  // En caso de que el counter del hostNode sea menor a los del vector no hace nada
}


// Descripcion: Agregar nodos al grafo evitando las repeticiones del mismo nodo de red, host y registro
// Entrada: Apuntador a la head de la lista de red, informacion para crear los nodos, 
// vector de red que guarda el mas grande, vector de host que guarda el mas grande, vector de red auxiliar al vector host
// Salida: Nada
// Complejidad: O(n^3)
void InsertarNuevo(RedNode* &pthead, string redData, string hostData, string regDate, string regTime, string regPort, string regLog, vector<RedNode*> &vectorRed, vector<HostNode*> &vectorHost, vector<RedNode*> &vecRedAux){

  RedNode* newRedNode = new RedNode(redData);
  HostNode* newHostNode = new HostNode(hostData);
  RegistroNode* newRegistroNode = new RegistroNode(regDate, regTime, regPort, regLog);

  // Si la lista de red nodes esta vacia, se apunta a ella
  if(pthead==NULL){
    pthead = newRedNode;
    pthead->next = newHostNode;
    pthead->next->next = newRegistroNode;
    pthead->addToCounter(); // +1 Red
    pthead->next->addToCounter(); // +1 Host
    getMaxRed(vectorRed,pthead);
    getMaxHost(vectorHost,pthead->next, newRedNode, vecRedAux);
    return;
  }

  // En caso de que no, se busca el ultimo nodo de red
  RedNode* tmpRed = pthead;
  RedNode* lastRed = NULL; // A este nodo, a su down se le agrega el nuevo valor

  // Se recorre la lista de red nodes
  while(tmpRed != NULL){
    lastRed = tmpRed;

    // El red node esta en la lista
    if(tmpRed->m_data == newRedNode->m_data){
      // Eliminar un nodo
      delete newRedNode;

      // Se recorre la lista de hosts de la red encontrada
      HostNode* tmpHost = tmpRed->next;
      HostNode* lastHost = NULL; // A este nodo, a su down se le agrega el nuevo valor
      while(tmpHost != NULL){
        lastHost = tmpHost;

        // El host esta en la lista
        if(tmpHost->m_data == newHostNode->m_data){
          // Eliminamos un nodo
          delete newHostNode;

          // Se recorre la lista de registros
          RegistroNode* tmpRegistro = tmpHost->next;
          RegistroNode* lastRegistro = NULL; // A este nodo, a su down se le agrega el nuevo valor
          while(tmpRegistro != NULL){
            lastRegistro = tmpRegistro;
            // El registro esta en la lista
            if(tmpRegistro->getRegistro() == newRegistroNode->getRegistro()){
              // Eliminar un nodo
              delete newRegistroNode;
              return;
            }
            tmpRegistro = tmpRegistro->down;
          }
          // El registro no esta en la lista
          lastRegistro->down = newRegistroNode;
          // Agregar el addCounter al host
          tmpHost->addToCounter();
          getMaxHost(vectorHost, tmpHost, tmpRed, vecRedAux);
          return;
        }
        tmpHost = tmpHost->down;
      }
      // El host no esta en la lista
      lastHost->down = newHostNode;
      lastHost->down->next = newRegistroNode;
      tmpRed->addToCounter();
      lastHost->down->addToCounter();
      getMaxRed(vectorRed, tmpRed);
      getMaxHost(vectorHost, lastHost->down, tmpRed, vecRedAux);
      return;
    }
    tmpRed = tmpRed->down;
  }
  // El red node no esta en la lista
  lastRed->down = newRedNode;
  lastRed->down->next = newHostNode;
  lastRed->down->next->next = newRegistroNode;
  lastRed->down->addToCounter();        // +1 Red
  lastRed->down->next->addToCounter();  // +1 Host
  getMaxRed(vectorRed,lastRed->down);
  getMaxHost(vectorHost,lastRed->down->next, lastRed->down, vecRedAux);
  return;
}


// Descripcion: Lectura del archivo para la creacion del grafo
// Entrada: Apuntador a la cabeza de la lista de nodos de red, vector de red, vector de host, vector auxiliar
// Salida: Nada
// Complejidad: O(n^3)
void leerArchivo(RedNode* &pthead, vector<RedNode*> &vectorRed, vector<HostNode*> &vectorHost, vector<RedNode*> &vecRedAux) {
  string line;
  ifstream file("bitacora2.txt");
  int n = 0;
  if (file.is_open())
  {
    while (getline(file, line))
    {
      stringstream ss(line); // Renglon individual
      string fecha;
      string ip;
      string red_host;
      string myString[5];
      string ips[2];
      string redes_host[4];

      for (int i = 0; i < 5; i++)
      {
        if (i == 4)
          getline(ss, myString[i]);
        else
          getline(ss, myString[i], ' ');
      }
      
      ip = myString[3];
      stringstream sss(ip);
      sss << ip;

      for (int i = 0; i < 2; i++)
      {
        getline(sss,ips[i],':');
      }

      red_host = ips[0];
      stringstream ssss(red_host);
      ssss << red_host;

       for (int i = 0; i < 4; i++)
       {
        getline(ssss,redes_host[i],'.');
       }

       
       string red = redes_host[0] + "." + redes_host[1];
       string host = redes_host[2] + "." + redes_host[3];
       string port = ips[1];
       fecha = myString[0] + " " + myString[1];
       string hora = myString[2];
       string log = myString[4];

      //  cout << red << "." << host << ":" << port << endl;
        
       InsertarNuevo(pthead, red,host,fecha,hora,port,log,vectorRed, vectorHost, vecRedAux);
    }
  }
}


int main(){

  RedNode* pthead = NULL;
  
  // Vectores
  vector<RedNode*> vecRed;
  vector<HostNode*> vecHost;
  vector<RedNode*> vecRedAux;

  leerArchivo(pthead, vecRed, vecHost, vecRedAux);
  RedNode* tmpRed = pthead;

  // IMPRIMIENDO TO_DO EL ARCHIVO
  // while(tmpRed != NULL){
  //   cout << tmpRed->m_data;
  //   cout << "(" << tmpRed->m_counter << ") → ";
  //   HostNode* tmpHost = tmpRed->next;
  //   while(tmpHost != NULL){
  //     cout << tmpHost->m_data;
  //     cout << "(" << tmpHost->m_counter << ") → ";
  //     tmpHost = tmpHost->down;
  //   }
  //   tmpRed = tmpRed->down;
  //   cout << endl;
  // }
  // cout << "\n********************************" << endl;

  for(auto x : vecRed)
  {
    cout << x->m_data << endl;
  }
  
  cout << endl;

  for(int i=0; i< vecHost.size(); i++){
    cout << vecRedAux.at(i)->m_data << "." << vecHost.at(i)->m_data << endl;
  }



  return 0;
}


