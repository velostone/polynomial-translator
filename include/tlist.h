#include <iostream>

using std::size_t;

template<typename T>
class Node
{
	T data;
	Node* next;
	Node(T _data, Node* _next) : data(_data), next(_next) { };
};

template<typename T>
class List : public Node<T> 
{
public:
	Node* first;
	size_t size;
	List()
	{
		first = nullptr;
		size = 0;
	}
	List(Node* first_node)
	{
		first = first_node;
		size = 1;
	}
	List(const List<T>& _list)
	{
	}

};