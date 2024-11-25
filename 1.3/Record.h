#pragma once
#include "Date.cpp"
#include "IpAdress.cpp"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

class Record {
    Date d;
    IpAdress ip;
    string message;
    int msgType;
  public:
    Record();
    Record(string,int,string,string,string);
    Date GetDate();
    IpAdress GetIp();
    int GetMsg();
    friend ifstream& operator>>(ifstream&,Record &);
    bool operator>(const Record&);
    bool operator==(Record&);
    bool operator!=(Record&);
    friend ostream& operator<< (ostream& stream, Record&); 
};