#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class Resumen {

    private:
        float m_red;
        int m_countReg;
        int m_countHost;
        vector<float> m_vecHost;

    

    public:

        float getRed(){
            return m_red;
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
    
