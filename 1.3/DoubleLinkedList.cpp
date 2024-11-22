//g++ listaEnlazadaEj.cpp -o listaEnlazadaDoble; ./listaEnlazadaDoble

#include <iostream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;


// class node: un valor y un puntero a otro nodo
template <class T>		//	Esta linea permite que podamos crear listas de cualquier tipo de dato
class Node
{	public:

		T value; 			// valor almacenado

		Node<T> *prev; 	 	
		Node<T> *next;		
		
		Node( T valor )
		{	this->value = valor;
			this->prev = NULL;
			this->next = NULL;
		}
};

//  Clase lista enlazada doble: 
template <class T>
class List
{

	Node<T> *first;		
	Node<T> *last; 
	int size;			

	public:
	
		List() 
		{	this->first = NULL; 
			this->last = NULL; 
			this->size = 0;
		}
		
		int getSize(){ return size; }
		void showList();				

		
		//	Funciones para insertar elementos
		void insertFirst(T);		//C(3)	
		void push_back(T);				//C(3)
		bool insertAtIndex(int, T); 	//C(n/2)

		//	Funciones para eliminar elementos
		void deleteFirst();					//	C(1)
		void deleteLast();					//	C(1)			
		void deleteAtIndex(int); 			//C(n/2)	

		Node<T>* find(T, int*);			//C(n)
		void update(int, T);			//C(n)
		Node<T>* getFirst() {return first;}		//C(1)	
		T& operator[](const int location) ;
};
/**/
// inserta en un indice especifico
template <class T> 
T& List<T>::operator[](const int location){

	Node<T> *actual = this->first; 
    for(int i = 0; i < location; i++){
		actual = actual->next;
	}
	return actual->value;

}


template<class T>
bool List<T>::insertAtIndex(int index, T newValue)
{	Node<T> *nuevo = new Node<T> ( newValue );  
	if(index < 0 || index > this->size){
		cout<<"Index fuera de rango"<<endl;
		return false;
	}
	//	insertar al inicio 
	if (index == 0 )
	{	this->insertFirst(newValue); 
		return true;
	}

	if (index == this->size - 1)
	{	this->push_back(newValue); 
		return true;
	}

	if ( index < size/2 )		
	{	Node<T> *aux = first;
		int i = 0; 

		while( i <= size/2 )
		{	if (i == index-1 )
			{	nuevo->prev = aux;
				nuevo->next = aux->next; 

				nuevo->next->prev = nuevo; 
				aux->next = nuevo;
				this->size++;
				return true;
			}

			aux = aux->next;
			i++;
		}

	}
	else  
	{
		Node<T> *aux = last;
		int i = size;
		
        while( i >= (size/2 )){
			if (i == index ){
                nuevo->prev = aux->prev;
                nuevo->next = aux;
				
				nuevo->prev->next = nuevo;
				aux->prev = nuevo;
				this->size++;
				return true;
		}
		    aux = aux->prev;
			i--;
		}
	}
	return false;
}
 
template<class T>
void List<T>::deleteAtIndex(int index){
	if(index < 0 || index > this->size){
		cout<<"Index fuera de rango"<<endl;
		return;
	}
	if (index == 0){
		this->deleteFirst();
		return;
	}
	if (index == this->size - 1){
		this->deleteLast();
		return;
	}
	if (index < size / 2){
		Node<T> *aux = first;
		int i = 0;
		while (i < index){
			aux = aux->next;
			i++;
		}
		aux->prev->next = aux->next;
		aux->next->prev = aux->prev;
		delete aux;
		this->size--;
	}
	else{
		Node<T> *aux = last;
		int i = size - 1;
		while (i > index){
			aux = aux->prev;
			i--;
		}
		aux->prev->next = aux->next;
		aux->next->prev = aux->prev;
		delete aux;
		this->size--;
	}
}

template<class T>
Node<T>* List<T>::find( T value, int *index){	
	Node<T> *aux = this->first;
	int i = 0;
	while (i < this->size){
		if (aux->value == value){
			if (index != NULL){
				*index = i;
			}
			*index = i;
            return aux;
        }
        aux = aux->next;
        i++;
	}
	return NULL;
}

template<class T>
void List<T>::deleteFirst(){	
	Node<T> *aux = this->first;
	Node<T> *second = aux->next;
	second->prev = last;
	last->next = second;
	delete aux;
	first = second;
	size--;
}


template<class T>
void List<T>::insertFirst(T newValue){	
	Node<T> *nodo = new Node<T>(newValue);
	Node<T> *aux = this->first;
	nodo->next = aux;
	first = nodo;
	if (this->size == 0){
		last = nodo;
	} 
	else{
		aux->prev = nodo; 
	}
	first->prev = last;
	last->next = first;
	size++;
}


// inserta al final
template<class T>
void List<T>::push_back(T newValue)
{
	Node<T> *nodo = new Node<T>(newValue);

	Node<T> *aux = this->last;

	nodo->prev = aux;
	last = nodo;

	if (this->size == 0){
		first = nodo;
	}
	else{ 
		aux->next = nodo;
	}
	first->prev = last;
	last->next = first;
	this->size++;
}

template<class T>
void List<T>::deleteLast(){
    Node<T> *aux = this->last; 
    Node<T> *second = aux->prev;
    second->next = this->first;
    this->first->prev = second;    
    delete aux;
    this->last = second;    
    size--;
}

template <class T>
void List<T>::update(int index, T newValue){
	if (index < 0 || index >= this->size){
		cout << "Error: índice fuera de rango." << endl;
		return;
	}
	Node<T> *aux;
	if (index < size / 2){
		aux = this->first;
		for (int i = 0; i < index; i++){
			aux = aux->next;
		}
	}
	else{
		aux = this->last;
		for (int i = this->size - 1; i > index; i--){
			aux = aux->prev;
		}
	}
	aux->value = newValue;
}

template<class T>
void List<T>::showList( )
{
	Node<T> *aux = this->first;
	int i = 0;
	cout << "El tamagno de la lista es de " << this->size << endl;
	while( i < size)
	{	
		cout << "[" << i << "] = " << aux->value << endl;
		aux = aux->next;
		i++;
	}
	cout << endl;
	
}






