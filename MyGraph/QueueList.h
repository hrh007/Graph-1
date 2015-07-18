#ifndef QUEUELIST_H
#define QUEUELIST_H
#include "Node.h"
template <class T>
class QueueList{
private:
	node <T>*object;
public:
	QueueList(){
		this->object = 0;
	}
	bool empty()const{
		if (object == 0)return true;
		return false;
	}
	void ADD(T value){
		node <T>*newobject = new node<T>(value);
		node <int>*p =object;
		if (object == 0){
			object = newobject;
		}
		else {
			while (p->next != 0)
			{
				p = p->next;
			}
			p->next = newobject;
		}
		
	}
	T GET(){
		T value;
		if (object == 0){
			cout << "DA HET";
		}
		else{
			node <T>*p = object;
			value = p->data;
			object = object->next;
			delete p;
		}
		return value;
	}
};


#endif // !QUEUELIST_H
