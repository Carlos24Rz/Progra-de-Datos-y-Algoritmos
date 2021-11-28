#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Resumen {

    private:
        

    

    public:
        float m_red;
        int m_countReg = 1;
        int m_countHost = 1;
        vector<float> m_vecHost;

        Resumen(){};

        Resumen(float red, float host){
            m_red = red;
            m_vecHost[0] = host;
        }

        float getRed(){
            return m_red;
        }

        void setRed(float red){
            m_red = red;
        }

        void setHost(float host){
            m_vecHost[0] = host;
        }
        

        bool operator==(const Resumen &incomingResumen){
            
            float red = incomingResumen.m_red;
            float host = incomingResumen.m_vecHost[0];
            
            // Misma red
            if(m_red == red) {
                // Comparar host con vector de host
                for (int i = 0; i < m_vecHost.size(); i++) {
                    // Mismo host
                    if (m_vecHost[i] == host) {
                        m_countReg += 1;
                        return true;
                    }
                }
                // Distinto host
                m_vecHost.push_back(host);
                return true;
            }

            // Diferente red
            else {
                return false;
            }
        }

        // 0 = izquierda
        // 1 = derecha
        // objetoInicial < objetoEntrante
        // 99            < 0
        bool operator<(const Resumen &incomingResumen) {
            float red = incomingResumen.m_red;
            
            if(m_red < red) {
                return false;
            }
            return true;
        }
};
    
