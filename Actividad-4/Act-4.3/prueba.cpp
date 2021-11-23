#include <bits/stdc++.h>
#include "class.h"
using namespace std;

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


void getMaxHost(vector<HostNode*> &vectorHost, HostNode* hostNode) {
  if(vectorHost.empty()) {
    vectorHost.push_back(hostNode);
    return;
  }
  if(vectorHost[0]->m_counter == hostNode->m_counter){
    if (vectorHost[0]->m_data == hostNode->m_data) return;
    vectorHost.push_back(hostNode);
    return;
  }
  if(vectorHost[0]->m_counter < hostNode->m_counter) {
    vectorHost.clear();
    vectorHost.push_back(hostNode);
  } 
  // En caso de que el counter del hostNode sea menor a los del vector no hace nada
}




void InsertarNuevo(RedNode* &pthead, string redData, string hostData, string regDate, string regTime, string regPort, string regLog, vector<RedNode*> &vectorRed, vector<HostNode*> &vectorHost){

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
    getMaxHost(vectorHost,pthead->next);
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
          getMaxHost(vectorHost, tmpHost);
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
      getMaxHost(vectorHost, lastHost->down);
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
  getMaxHost(vectorHost,lastRed->down->next);
  return;
}


void leerArchivo(RedNode* &pthead, vector<RedNode*> &vectorRed, vector<HostNode*> &vectorHost) {
  string line;
  ifstream file("bitacoraM2.txt");
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
        
       InsertarNuevo(pthead, red,host,fecha,hora,port,log,vectorRed, vectorHost);
    }
  }
}


int main(){

  RedNode* pthead = NULL;
  
  // Vectores
  vector<RedNode*> vecRed;
  vector<HostNode*> vecHost;

  leerArchivo(pthead, vecRed, vecHost);

  cout << "--------------------------------" << endl;
  cout << "\n Imprimiendo todo " << endl << endl;
  RedNode* tmpRed = pthead;
  while(tmpRed != NULL){

    cout << tmpRed->m_data;
    cout << "(" << tmpRed->m_counter << ") → ";
    HostNode* tmpHost = tmpRed->next;
    while(tmpHost != NULL){
      cout << tmpHost->m_data;
      cout << "(" << tmpHost->m_counter << ") → ";
      tmpHost = tmpHost->down;
    }
    tmpRed = tmpRed->down;
    cout << endl;
  }

  cout << "\n********************************" << endl;
  for(auto x : vecRed)
  {
    cout << x->m_data << "(" << x->m_counter << ") - ";
  }
  cout << endl;

  for(auto x : vecHost)
  {
    cout << x->m_data << "(" << x->m_counter << ") - ";
  } 
  cout << endl;




  ofstream myfile;
  myfile.open ("example.txt");
  while(pthead != NULL)
  {
    myfile << pthead->m_data << "\n";
    pthead = pthead->down;
  }
  myfile.close();


  return 0;
}


