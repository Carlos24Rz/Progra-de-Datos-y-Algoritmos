#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

class Registro
{

private:
    int m_mes, m_dia, m_hora, m_minuto, m_segundo;
    string m_log;
    string m_ip;

public:

    // Destructor
    ~Registro(){
    }

    Registro(string mes, int dia, int hora, int minuto, int segundo, string ip, string log)
    {
        if (mes == "Jan")
            m_mes = 1;
        else if (mes == "Feb")
            m_mes = 2;
        else if (mes == "Mar")
            m_mes = 3;
        else if (mes == "Apr")
            m_mes = 4;
        else if (mes == "May")
            m_mes = 5;
        else if (mes == "Jun")
            m_mes = 6;
        else if (mes == "Jul")
            m_mes = 7;
        else if (mes == "Aug")
            m_mes = 8;
        else if (mes == "Sep")
            m_mes = 9;
        else if (mes == "Oct")
            m_mes = 10;
        else if (mes == "Nov")
            m_mes = 11;
        else
            m_mes = 12;

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

        string str = mes + " " + ss.str() + " " + to_string(m_hora) + ":" + to_string(m_minuto) + ":" + to_string(m_segundo) + " " + m_ip + " " + m_log;

        return str;
    }

    bool operator<(const Registro& b)
{
    string ip_1[5];
    string ip_2[5];

    stringstream ss_1(m_ip);

    stringstream ss_2(b.m_ip);

    for (int i = 0; i < 5; i++)
    {
      if(i >= 3)
      {
        getline(ss_1,ip_1[i], ':');
        getline(ss_2,ip_2[i], ':');
      }
      else
      {
        getline(ss_1, ip_1[i], '.');
        getline(ss_2, ip_2[i], '.');
      }
    }

    if(stoi(ip_1[0]) < stoi(ip_2[0]))
    {
      return 1;
    }
    else if(stoi(ip_1[0]) == stoi(ip_2[0]))
    {
      if (stoi(ip_1[1]) < stoi(ip_2[1]))
      {
        return 1;
      }
      else if(stoi(ip_1[1]) == stoi(ip_2[1]))
      {
        if (stoi(ip_1[2]) < stoi(ip_2[2]))
        {
         return 1;
        }
        else if(stoi(ip_1[2]) == stoi(ip_2[2]))
        {
          if (stoi(ip_1[3]) < stoi(ip_2[3]))
          {
            return 1;
          }
          else if(stoi(ip_1[3]) == stoi(ip_2[3]))
          {
            if (stoi(ip_1[4]) < stoi(ip_2[4]))
            {
              return 1;
            }
            else if(stoi(ip_1[4]) == stoi(ip_2[4]))
            {
              if(m_mes < b.m_mes)
              {
                return 1;
              }
              else if(m_mes == b.m_mes)
              {
                if (m_dia < b.m_dia)
                {
                  return 1;
                }
                else if(m_dia == b.m_dia)
                {
                  if (m_hora < b.m_hora)
                  {
                    return 1;
                  }
                  else if(m_hora == b.m_hora)
                  {
                    if(m_minuto < b.m_minuto)
                    {
                      return 1;
                    }
                    else if(m_minuto == b.m_minuto)
                    {
                      if(m_segundo < b.m_segundo)
                      {
                        return 1;
                      }
                      else if(m_segundo == b.m_segundo)
                      {
                        if(m_log < b.m_log)
                        {
                          return 1;
                        }
                        else
                        {
                          return 0;
                        }
                      }
                      else
                      {
                        return 0;
                      }
                    }
                    else
                    {
                      return 0;
                    }
                  }
                  else
                  {
                    return 0;
                  }
                  
                }
                else
                {
                  return 0;
                }
                
              }
              else
              {
                return 0;
              }
            }
            else
            {
              return 0;
            } 
          }
          else
          {
            return 0;
          }
          
        }
        else
        {
          return 0;
        }
        
      }
      else
      {
        return 0;
      }
      
    }
    else
    {
      return 0;
    }
  }
};