#pragma once
#include <string>
#include <fstream>
#include <fstream>
using namespace std;

class Date {
    string month;
    string time;
    int m;
    int day;
    int hour;
    
  public:
    Date(string,int,string);
    Date();
    Date operator+(const int&);
    friend ifstream& operator>>(ifstream&,Date &);
    friend ostream& operator<< (ostream& , Date&); 
    bool operator>(const Date&);
    bool operator<(const Date&);
};