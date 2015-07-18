#ifndef STACK_H
#define STACK_H
#include "Node.h"
template<class T>
class Stack
{
private:
	node<T> *object;
public:
	Stack(){
		this->object = 0;
	}
	void Push(T value){
		node<T>*newobject = new node<T>(value, object);
		object = newobject;
	}
	T Pop(){
		T value = object->data;
		node<T>*p = object;
		object = object->next;
		delete p;
		return value;
	}
	//chưa check
	Stack(const Stack<T> &t)
	{
		this->object = 0;
		node<T>* a = t.object;
		while (a != 0) {
			node <T>*q = new node<T>(a->data);
			if (object == 0) object = q;
			else
			{
				node <T>*p = object;
				while (p->next != 0)
				{
					p = p->next;
				}
				p->next = q;
			}
			
			a = a->next;
		}
	}// chưa check
	T getTop(){
		return object->data;
	}
	bool getNULL() const{
		return object == 0;
	}
	void Sout(string k = "") {
		node<T> *a = object;
		while (a != 0) {
			cout << a->data;
			a = a->next;
			if (a != 0) cout << k << " ";
		}
	}

	void Delete(){
		while (object != 0){
			node <T>*address = object;
			object = address->next;
			delete address;
		}
	}
	~Stack(){
		
	}
};
#endif // !STACK_H
