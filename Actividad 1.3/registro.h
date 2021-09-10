#include <iostream>

using namespace std;

class Registro{

    private:
        int m_mes, m_dia, m_hora, m_minuto, m_segundo;
        /// crear objeto fecha 
        string m_ip, m_log;

    public:
        Registro(int mes, int dia, int hora, int minuto, int segundo, string ip, string log)
        {
            m_mes = mes;
            m_dia = dia;
            m_hora = hora;
            m_minuto = minuto;
            m_segundo = segundo;
            m_log = log;
            m_ip = ip;
        }

        int getMes()
        {
            return m_mes;
        }

        int getDia()
        {
            return m_dia;
        }

        int getHora()
        {
            return m_hora;
        }

        int getMinuto()
        {
            return m_minuto;
        }

        int getSegundo()
        {
            return m_segundo;
        }

        string getIP()
        {
            return m_ip;
        }

        string getLog()
        {
            return m_log;
        }
    
};