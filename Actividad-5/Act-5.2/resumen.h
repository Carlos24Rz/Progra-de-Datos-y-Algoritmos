#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Resumen {

    private:
        

    public:
        string m_red;
        int m_countReg = 1;
        int m_countHost = 1;
        vector<string> m_vecHost;

        Resumen(){};

        Resumen(string red, string host){
            m_red = red;
            m_vecHost[0] = host;
        }

        string getRed(){
            return m_red;
        }

        void setRed(string red){
            m_red = red;
        }

        void setHost(string host){
            m_vecHost[0] = host;
        }

        bool isLess(const string data){

            float red1 = stof(m_red);
            float red2 = stof(data);

            if(red1 < red2) {
                return true;
            }
            return false;
        }

        bool isGreater(const string data){

            float red1 = stof(m_red);
            float red2 = stof(data);

            if(red1 > red2) {
                return true;
            }
            return false;
        }

        void printResumen(){
            cout << m_red << endl;
            cout << m_countReg << endl;
            cout << m_countHost << endl;
        }

};
    
