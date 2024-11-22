#include "Date.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

int monthtoint(string month) {
    string months[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    for (int i = 0; i < 12; i++) {
        if (month == months[i])
            return i + 1;
    }
    return -1;
}
Date::Date(){
    month = "Jan";
    m = 1;
    day = 1;
    hour = 0;
    time = "00:00:00";
}
int timeToHour(string time){
    vector<int> hour;
    stringstream ss(time);
    string fragment;
    while(getline(ss, fragment, ':'))
    {
        hour.push_back(stoi(fragment));
    }
    return hour[0]*3600+hour[1]*60+hour[2];

}

Date::Date(std::string _m,int d,std::string hms) {
    month = _m;
    day = d;
    time = hms;
    m = monthtoint(_m);
    hour = timeToHour(time);
}

ifstream& operator>>(ifstream& file,Date &d) {
    file >> d.month >> d.day >> d.time;
    d.m = monthtoint(d.month);
    d.hour = timeToHour(d.time);
    return file;
}
ostream& operator<< (ostream& stream, Date& d){
    stream<<d.month<<' '<<d.day<<' '<<d.time;
    return stream;
}

Date Date::operator+(const int& k){
    Date temp;
    temp = *this;
    temp.hour += k;
    if(temp.hour > 3600*24){
        temp.hour -= 3600*24;
        temp.day ++;
    }
    if(temp.day > 31){
        temp.day = 1;
        temp.m ++;
        string months[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
        temp.month = months[m-1];
    } 
    return temp;
}

bool Date::operator>(const Date& b){
    if(this->m > b.m){
        return true;
    }
    else if(this->m < b.m){
        return false;
    }
    else if(this->day > b.day){
        return true;
    }
    else if(this->day < b.day){
        return false;
    }
    else if(this->hour > b.hour){
        return true;
    }
    return false;
    

}

bool Date::operator<(const Date& b){
    if(this->m < b.m){
        return true;
    }
    else if(this->m > b.m){
        return false;
    }
    else if(this->day < b.day){
        return true;
    }
    else if(this->day > b.day){
        return false;
    }
    else if(this->hour < b.hour){
        return true;
    }
    return false;
}