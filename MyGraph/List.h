#ifndef LIST_H
#define LIST_H
#include <string>
#include<iostream>
using namespace std;
#include "Node.h"
#include "Stack.h"
template <class S>
class List
{

private:
	node <S>*object;
	node <S>*getAddress(int pos){
		node <S>*address=object;
		for (int i = 1; i <= pos; i++){
			address = address->next;
		}
		return address;
	}
public:
	List(){
		this->object = 0;
	}
	List(const List<S> &t){
		this->object = 0;
		node<S>* a = t.object;
		while (a != 0){
			AddL(a->data);
				a = a->next;
		}
	}
	
	void operator = (const List<S> t){
		this->object = 0;
		node<S>* a = t.object;
		while (a != 0){
			AddL(a->data);
			a = a->next;
		}
	}
	
	void AddF(S value){
		node <S>*q = new node<S>(value, object);
		object = q;
	}
	void AddL(S value){
		node <S>*q = new node<S>(value);
		node <S>*p = object;
		if (object == 0){
			object = q;
		}
		else
		{
			while (p->next != 0)
			{
				p = p->next;
			}
			p->next = q;
		}
		
	}
	
	void Add(int pos,S value){
		if (pos == 0) AddF(value);
		else
		{
			node <S>*address = getAddress(pos - 1);
			node <S>*q = new node<S>(value, address->next);
			address->next = q;
		}
	}
	void Delete(int pos){
		if (pos == 0){
			node <S>*address = object;
			object = address->next;
			delete address;
		}
		else{
			node <S>*address = getAddress(pos-1);
			node <S>*add = address->next;
			address->next = address->next->next;
			delete add;
		}
	}
	/*0 2 5 6 8*/
	void Delete(){
		while (object!=0){
			node <S>*address = object;
			object = address->next;
			delete address;
		}
	}
	void Fix(int pos, S value){
		node <S>*address = getAddress(pos);
		address->data = value;
	}
	S Value(int pos){
		node <S>*address = getAddress(pos);
		return address->data;
	}
	void Lout(string k=""){
		node<S> *a = object;
		while (a != 0){
			cout << a->data;
			a = a->next;
			if (a != 0) cout<< k << " ";
		}
	}
	void LoutPHI(string k = " - ",string h="") {
		node<S> *a = object;
		while (a != 0) {
			PHI<int> ka = a->data;
			cout << ka.one+1<<k<<ka.two+1;
			a = a->next;
			if (a != 0) cout << h << " ";
		}
	}
	int Length(){
		int count = 0;
		node<S> *a = object;
		while (a != 0){
			count++;
			a = a->next;
		}
		return count;
	}

	bool empty()const {
		if (object == 0)return true;
		return false;
	}

	~List(){
		Delete();
	}
};


#endif // !LIST_H

