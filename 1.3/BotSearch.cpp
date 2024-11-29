#include <iostream>
#include <fstream>
#include "Record.cpp"
//#include "DoubleLinkedvector.cpp"
#include <vector>
#include "Graph.h"
#include "Hash.h"
using namespace std;
void SetConnections(vector<Record>& , Graph<IpAdress>& );
void readData(string , vector<Record> &, Graph<IpAdress> &);
void MergeSort(vector<Record> &info, int low, int high);

int asciiMod(int max, IpAdress key ){
    int sum;
    for(int i = 0; i < key.GetIp().size() && key.GetIp()[i] != ':'; i++){
        if(key.GetIp()[i]!= '.'){
            sum += key.GetIp()[i]*(10^i);
        }
    }
    return sum%max;
}

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
    Hash_Collisions<IpAdress, Node<IpAdress>*> tabla(records.size(), asciiMod);
    //conexions.depthFirst();
    Node<IpAdress> * q = conexions.getFirst();
    Node<IpAdress> *max = q;
    while(q  != nullptr){
        int iter;
        max = max->getAdy() < q->getAdy() ? q: max;
        iter = tabla.add(q->getTag(), q);
        cout<<"Colisiones al insertar: "<< iter<< " Ip: "<< q->getTag()<<" Adyacencias: "<<q->getAdy()<<endl;
        q = q->getNext();
        

    }
    cout<<"Ip con mas adyacencias: "<< max->getTag() <<endl;
    cout<<"Ingrese su Ip a inspeccionar: ";
    IpAdress temp;
    cin>>temp;
    if(tabla.isIn(temp)){
        q = tabla.findValue(temp);
        cout<<"\nCantidad de veces repetida: "<<q->getCount()
        <<"\nTotal de Adyacencias: "<< q->getAdy()<<endl;
        q->getAdyacencies();
    }else{
        cout<<"\nIp no dentro del grafo"<<endl;
    }


}



void SetConnections(vector<Record>& records, Graph<IpAdress>& conexions){
    for(int i = 0; i < records.size(); i++){
        int j = i+1;
        while(records[i].GetDate()+(25*3600)  > records[j].GetDate() && j < records.size()){
            if(records[i].GetIp().GetPuerto() + 1 > records[j].GetIp().GetPuerto() &&
                   records[j].GetIp().GetPuerto() > records[i].GetIp().GetPuerto() - 1){
                    conexions.addAdyacency(records[j].GetIp(), records[i].GetIp());
                   }
            j++;
        }
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
