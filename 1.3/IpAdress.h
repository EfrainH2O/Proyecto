#pragma once
#include <string>
#include <fstream>
using namespace std;

class IpAdress {
  private:
    int pices[4];
    int puerto;
    string ip ; 
  public:
    IpAdress();
    IpAdress(string);
    void transformtoINT();
    int GetPuerto();
    string GetIp() const;

    friend istream& operator>>(istream&,IpAdress &);
    friend ifstream& operator>>(ifstream&,IpAdress &);
    friend ostream& operator<< (ostream&, const IpAdress&);
    bool operator>(const IpAdress&);
    bool operator<(const IpAdress&);
    bool operator==(const IpAdress&);
    bool operator!=(const IpAdress&);
};