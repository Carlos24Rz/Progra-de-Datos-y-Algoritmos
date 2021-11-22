#include <bits/stdc++.h>
#include "class.h"
using namespace std;


// RegistroNode(string date, string time, string port, string log)
void Insertar(RedNode* &pthead, string redData, string hostData, string regDate, string regTime, string regPort, string regLog){
  RedNode* newRedNode = new RedNode(redData);
  HostNode* newHostNode = new HostNode(hostData);
  RegistroNode* newRegistroNode = new RegistroNode(regDate, regTime, regPort, regLog);
    
  //cout << newRedNode->m_data << "." << newHostNode->m_data << ":" << newRegistroNode->getRegistro() << endl;

 
  // Lista vacia
  if (pthead == NULL) {
    
    pthead = newRedNode;
    newRedNode->next = newHostNode;
    newHostNode->next = newRegistroNode;

    cout << pthead->m_data << endl;

    return;
  }
  
  // Recorrer lista RedNode
  RedNode* tempRed = pthead;
  while (tempRed->down != NULL){

    // Red duplicada
    if (tempRed->m_data == newRedNode->m_data){
        delete newRedNode;
        
        // Recorrer lista HostNode
        HostNode* tempHost = tempRed->next;
        while (tempHost->down != NULL) {
          
          // Host duplicado
          if (tempHost->m_data == newHostNode->m_data){
            delete newHostNode;

            // Recorrer lista RegistroNode
            RegistroNode* tempRegistro = tempHost->next;
            while (tempRegistro->down != NULL) {
                
              // Registro duplicado ¡??¡?¡?¡??¡
              if(tempRegistro->getRegistro() == newRegistroNode->getRegistro()){
                delete newRegistroNode;
                return;
              }
              tempRegistro = tempRegistro->down; // Recorrer ciclo
            }
            
            // Insertar registro
            tempRegistro->down = newRegistroNode;
            tempHost->addToCounter(); // Sumar counter
            return;
          }            

          tempHost = tempHost->down;  // Recorrer ciclo
        }
        // Insertar host
        tempHost->down = newHostNode;
        newHostNode->next = newRegistroNode;
        tempRed->addToCounter(); // Sumar counter
        return;
    }
    tempRed = tempRed->down;
  }

  // Insertar red
  tempRed->down = newRedNode;
  newRedNode->addToCounter();
  newRedNode->next = newHostNode;
  newHostNode->addToCounter();
  newHostNode->next = newRegistroNode;
  return;
}




void leerArchivo(RedNode* pthead) 
{
  string line;
  ifstream file("bitacoraModificado.txt");
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
       string log = redes_host[4];

       //cout << red << "." << host << ":" << port << endl;
       Insertar(pthead, red,host,fecha,hora,port,log);
    }
  }
}


    



    


int main(){
  RedNode* pthead = NULL;

// (pthead, redData, hostData, regDate, regTime, regPort, regLog){
//   Insertar(pthead, "250.320", "226.075", "Jul 04", "02:22:15", "11278","Failed password for admin");
//   Insertar(pthead, "250.320", "226.075", "Jan 08", "01:17:23", "11278", "Failed password for admin");
//   Insertar(pthead, "250.320", "840.621", "Feb 05", "11:11:01", "11278", "Failed password for admin");
  

  leerArchivo(pthead);


  
  cout << "-----" << endl;
  cout << "pthead" << endl;
  cout << "↓" << endl;
  cout << pthead->m_data;
  cout << "↓" << endl;  
  cout << pthead->next->m_data;
  cout << "↓" << endl;  

  
  return 0;
}