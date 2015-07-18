#ifndef NODE_H
#define NODE_H
#include <string>
template<class T>
class node
{

public:
	T data;
	node* next;
	node(){
		this->next = 0;
	}
	node(T value, node* _next = 0){
		this->data = value;
		this->next = _next;
	}
};

#endif // !NODE_H
