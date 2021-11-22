#include <bits/stdc++.h>

using namespace std;

class RedNode;
class HostNode;
class RegistroNode;


class RedNode{
    public:
        string m_data;
        RedNode* down = NULL;
        HostNode* next = NULL;
        int m_counter = 0;

        RedNode(){};

        RedNode(string data){
            m_data = data;
        };

        void addToCounter(){
            m_counter += 1;
        }
};


class HostNode{
    public:
        string m_data;
        HostNode* down = NULL;
        RegistroNode* next = NULL;
        int m_counter = 0;

        HostNode(){};

        HostNode(string data){
            m_data = data;
        };

        void addToCounter(){
            m_counter += 1;
        }
};


class RegistroNode{
    public:
      string m_date;
      string m_time;
      string m_port;
      string m_log;
      RegistroNode* down = NULL;


    RegistroNode(){};

    RegistroNode(string date, string time, string port, string log){
        m_date = date;
        m_time = time;
        m_port = port;   
        m_log = log;
    }

    string getRegistro()
    {
        string registro = m_date + " " + m_time + " " + m_port + " " + m_log;
        return registro;  
    }
};

