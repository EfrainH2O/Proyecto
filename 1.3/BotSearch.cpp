#include <iostream>
#include <fstream>
#include "Record.cpp"
//#include "DoubleLinkedvector.cpp"
#include <vector>
#include "Graph.h"
#include "AVL.h"
using namespace std;
void SetConnections(vector<Record>& , Graph<IpAdress>& );
void EmptyUp(vector<Record>& data, AVL<Record>& organized);
void readData(string , vector<Record> &, Graph<IpAdress> &);
void writeData(string, vector<Record> &);
void MergeSort(vector<Record> &info, int low, int high);
Date askDate();
void findDatabyIP(IpAdress,IpAdress,vector<Record>&,vector<Record>&);

int main(int argc, char *argv[]){
    string l;
    string filename = "bitacora.txt";
    if(argc>1){
        filename = string(argv[1]);
    }
    vector<Record> records;
    Graph<IpAdress> conexions(false);
    readData(filename, records, conexions);
    cout<<"#List of Records: "<<records.size()<<endl;
    MergeSort(records, 0, records.size()-1);
    SetConnections(records, conexions);
    conexions.depthFirst();
  //  EmptyUp(Searchvector, ReORG);
    

}



void SetConnections(vector<Record>& records, Graph<IpAdress>& conexions){
    for(int i = 0; i < records.size(); i++){
        int j = i+1;
        while(records[i].GetDate()+(25*3600)  > records[j].GetDate() && j < records.size()){
            if(records[i].GetIp().GetPuerto() + 1 > records[j].GetIp().GetPuerto() &&
                   records[j].GetIp().GetPuerto() > records[i].GetIp().GetPuerto() - 1
                        && records[i].GetMsg() == records[j].GetMsg()){
                    conexions.addAdyacency(records[j].GetIp(), records[i].GetIp());
                   }
            j++;
        }
        //cout<<i<<endl;
    }
    return;
}

void readData(string filename, vector<Record>& Records, Graph<IpAdress> &Conect){
    ifstream s;
    Record r;
    s.open(filename);

    while(!s.eof() && s.is_open()){
        s>>r;
        //temp = Conect.addNode(r.GetIp(), temp);
        Records.push_back(r);
    }
    s.close();
    cout<<"Last Record: ";
}


void writeData(string filename, vector<Record> &Data){
    ofstream s(filename);
    int limit = Data.size();
    if(s.is_open()){
        for(int i = 0; i < limit; i++ ){
            s<<Data[i];
        }
    }
    else{
        cout<<"Error Writing"<<endl;
        return;
    }
}

void MergeSort(vector<Record> &info, int low, int high){
    if(low >= high){
        return;
    }
    int mid = (high-low)/2 + low;
    MergeSort(info, low, mid);
    MergeSort(info, mid+1, high);
    Record* aux = new Record[ high-low+1];

    int left = low;
    int right = mid+1;
    int i = 0;
    while( right<= high && left <= mid){
        if(info[left]>info[right]){
            aux[i]= info[right];
            right++;
        }
        else{
            aux[i]= info[left];
            left++;
        }
        i++;
    }
    while(right <= high){
        aux[i]= info[right];
        right++;
        i++;
    }
    while(left <= mid){
        aux[i]= info[left];
        left++;
        i++;
    }
        
    for(int j = low; j < high + 1; j++){
        info[j] = aux[j-low];
    }
    delete[] aux;
    return;
    // nlog(n)
}

Date askDate(){
    vector<string> v;
    string info;
    string dataFragment;
    cout<<"Ingrese Datos: "<<endl;
    getline(cin,info);
    stringstream data(info);
    while(data>>dataFragment){
        v.push_back(dataFragment);
    }
    Date temp(v[0],stoi(v[1]), v[2]);
    return temp;
}

void findData(Date start,Date end,vector<Record>& data,vector<Record>&result){
    int size = data.size();

    for(int i = 0; i < size; i++){
        if(data[i].GetDate() > start && data[i].GetDate() < end){
            result.push_back(data[i]);
        }
        if(data[i].GetDate() >end){
            return;
        }
        //O(n)
    }

}

void findDatabyIP(IpAdress start,IpAdress end,vector<Record>& data,vector<Record>&result){
    int size = data.size();
    for(int i = 0; i < size; i++){
        if(data[i].GetIp() > start && data[i].GetIp() < end){
            result.push_back(data[i]);
        }
        if(data[i].GetIp() >end){
            return;
        }
        //O(n)
    }

}

void EmptyUp(vector<Record>& data, AVL<Record>& organized){
    //Con maps o hashmaps seria mas sencillo
    Record empty;
    vector<Record> Max (5,empty);
    vector<int> Number(5,0);
    int amount = 1;
    for(int i = 0; i < data.size(); i++){
        //cout<<i<<data[i]<<endl;
        if(data[i] == data[i+1]){
            amount++;
            continue;
        }
        organized.add(data[i]); //
        auto it = Max.begin();
        for(auto j = Number.begin(); j != Number.end(); j++){
            
            if(*j < amount){
                Number.insert(j,amount);
                Number.pop_back();
                Max.insert(it,data[i]);
                Max.pop_back();
                break;
            }
            it++;
        }
        amount = 1;
    }
    cout<<"Mas Repetidos"<<endl;
    for(int i = 0; i < 5; i ++){
        cout<< i+1<<": "<<Max[i]<<" Cantidad: "<<Number[i]<<endl;
    }
}