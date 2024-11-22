#include "IpAdress.h"
#include <vector>
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

IpAdress::IpAdress(){
    ip = "0.0.0.0:0";
    for(int i = 0; i < 4; i++){
        pices[i] = 0;
    }
    puerto = 0;
}

void IpAdress::transformtoINT(){
    string fragment;
    vector<int> data;
    stringstream ss(ip);
    while(getline(ss, fragment, '.'))
    {
        data.push_back(stoi(fragment));
    }
    ss = stringstream(fragment);
    getline(ss, fragment, ':');
    getline(ss, fragment, ':');
    data.push_back(stoi(fragment));
    
    for(int i = 0; i < 4; i ++){
        pices[i] = data[i];
    }
    puerto = data[4];
}

IpAdress::IpAdress(string full){
    this->ip = full;
    transformtoINT();
}

int IpAdress::GetPuerto(){
    return puerto;
}

string IpAdress::GetIp()const{
    return ip;
}
istream& operator>>(istream& file, IpAdress &v) {
    file>>v.ip;
    v.transformtoINT();
    return file;
}

ifstream& operator>>(ifstream& file,IpAdress &v) {
    file>>v.ip;
    v.transformtoINT();
    return file;
}

ostream& operator<< (ostream& stream, const IpAdress&v){
    stream<<v.GetIp();
    return stream;
}

bool IpAdress::operator>(const IpAdress&other){
    for(int i = 0; i < 4; i++){
        if(this->pices[i] == other.pices[i]){
            continue;
        }else if(this->pices[i] > other.pices[i]){
            return true;
        }
        return false;
    }
    return false;
}
bool IpAdress::operator<(const IpAdress&other){
    for(int i = 0; i < 4; i++){
        if(this->pices[i] == other.pices[i]){
            continue;
        }else if(this->pices[i] < other.pices[i]){
            return true;
        }
        return false;
    }
    return false;
}

bool IpAdress::operator==(const IpAdress&other){
    for(int i = 0; i < 4; i++){
        if(pices[i] != other.pices[i]){
            return false;
        }
    }
    return true;
}

bool IpAdress::operator!=(const IpAdress&other){
    for(int i = 0; i < 4; i++){
        if(pices[i] != other.pices[i]){
            return true;
        }
    }
    return false;
}
