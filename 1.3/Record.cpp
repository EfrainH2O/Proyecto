#include "Record.h"


int msgToInt(string a){
    if(a == "Failed password for root"){
        return 1;
    }else if(a == "Failed password for admin"){
        return 2;
    }else if(a== "Failed password for illegal user guest"){
        return 3;
    }else if(a == "Failed password for illegal user test"){
        return 4;
    }else if(a == "Illegal user"){
        return 5;
    }else{
        return 0;
    }
}
Record::Record(string month, int day, string hour, string ip, string msg)
:d(month,day,hour), ip(ip)
{
    message = msg;
    msgType = msgToInt(message);
}
Record::Record():d("Jan", 1,"00:00:01"),ip("000.00.000.00")
{
    message = "Null";
    msgType = -1;
}
Date Record::GetDate(){
    return d;
}

IpAdress Record::GetIp(){
    return ip;
}

int Record::GetMsg(){
    return msgType;
}

ifstream& operator>>(ifstream& file,  Record&r){
    file>>r.d>>r.ip;  
    getline(file,r.message);
    r.msgType = msgToInt(r.message);
    return file;

}

bool Record::operator>(const Record& b){
    return this->d > b.d;
}

bool Record::operator==(Record& b){
    return this->ip == b.ip;
}

bool Record::operator!=(Record& b){
    return this->ip != b.ip;
}

ostream& operator<< (ostream& stream, Record&r){
    stream <<r.d<<' '<<r.ip<<' '<<r.message<<'\n';
    return stream;
}