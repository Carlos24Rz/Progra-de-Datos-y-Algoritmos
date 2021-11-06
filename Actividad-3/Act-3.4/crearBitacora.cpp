#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include <fstream>
using namespace std;

int numAleatorio(int inferior, int superior, int rnd){
  srand(rnd);
  int diferencia = superior - inferior;
  return (rand() % diferencia) + inferior;
}

string addZero(string number){
  return "0" + number;
}


int main(){

    string months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    string messages[] {"Failed password for illegal user test",
                        "Failed password for root",
                        "Illegal user"};

    // Aug 28 23:07:49 897.53.984.6:6710 Failed password for root

    // int lines = 500000; // 25MB
    // int lines = 250000; // 15MB
    // int lines = 120000; // 6MB
    // int lines = 60000; // 3MB
    int lines = 21272; // 2MB
    // int lines = 20000; // 1MB
    // int lines = 10000; // .5MB
    // int lines = 25;

    ofstream myfile;
    myfile.open ("bitacora2MB.txt");

    for(int i=0; i<lines; i++){

        string month = months[numAleatorio(0,11,i)];
        string day = to_string(numAleatorio(1,29,i));
        if(stoi(day)<10)
          day = addZero(day);

        string time1 = to_string(numAleatorio(1,23,i));
        if(stoi(time1)<10)
          time1 = addZero(time1);

        string time2 = to_string(numAleatorio(1,59,i));
        if(stoi(time2)<10)
          time2 = addZero(time2);

        string time3 = to_string(numAleatorio(1,58,i));
        if(stoi(time3)<10)
          time3 = addZero(time3);

        int ip1 = numAleatorio(0,999,i);
        int ip2 = numAleatorio(0,998,i);
        int ip3 = numAleatorio(0,997,i);
        int ip4 = numAleatorio(0,996,i);
        int port = numAleatorio(0,9998,i);
        string msg = messages[numAleatorio(0,3,i)];

        myfile << month << " " << day << " " << time1 << ":" << time2 << ":" << time3 <<
        " " << ip1 << "." << ip2 << "." << ip3 << "." << ip4 << ":" << port << " " << msg << "\n";
    }


    myfile.close();

    return 0;
}
