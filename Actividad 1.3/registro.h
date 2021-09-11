#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class Registro{

    private:
        int m_mes, m_dia, m_hora, m_minuto, m_segundo;
        /// crear objeto fecha 
        string m_ip, m_log;

    public:
        Registro(string mes, int dia, int hora, int minuto, int segundo, string ip, string log)
        {
            if(mes == "Jan") m_mes = 1;
            else if(mes == "Feb") m_mes = 2;
            else if(mes == "Mar") m_mes = 3;
            else if(mes == "Apr") m_mes = 4;
            else if(mes == "May") m_mes = 5;
            else if(mes == "Jun") m_mes = 6;
            else if(mes == "Jul") m_mes = 7;
            else if(mes == "Aug") m_mes = 8;
            else if(mes == "Sep") m_mes = 9;
            else if(mes == "Oct") m_mes = 10;
            else if(mes == "Nov") m_mes = 11;
            else  m_mes = 12;
 
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

        string getRegistro()
        {
            string mes;

            switch (m_mes)
            {
            case 1:
                mes = "Jan";
                break;
            case 2:
                mes = "Feb";
                break;
            case 3:
                mes = "Mar";
                break;
            case 4:
                mes = "Apr";
                break;
            case 5:
                mes = "May";
                break;
            case 6:
                mes = "Jun";
                break;
            case 7:
                mes = "Jul";
                break;
            case 8:
                mes = "Aug";
                break;
            case 9:
                mes = "Sep";
                break;
            case 10:
                mes = "Oct";
                break;
            case 11:
                mes = "Nov";
                break;
            case 12:
                mes = "Dec";
                break;
            }
            
            stringstream ss;

            ss << setfill('0') << setw(2) << to_string(m_dia);

            string str = mes + " " 
            + ss.str() + " " 
            + to_string(m_hora) + ":" 
            + to_string(m_minuto) + ":" 
            + to_string(m_segundo) + " "
            + m_ip + " "
            + m_log;

            return str;
        }
    
};