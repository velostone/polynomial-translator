#include <iostream>

using std::size_t;

template<typename T>
class Node
{
public:
	T data;
	Node* next;
	Node(T _data = NULL, Node* _next = nullptr) : data(_data), next(_next) { }
};

template<typename T>
class List
{
protected:
	Node<T>* first;
	size_t size;
public:
	List()
	{
		first = nullptr;
		size = 0;
	}
	List(Node<T>* first_node)
	{
		first = first_node;
		size = 1;
	}
	List(const List<T>& _list)
	{
		first = nullptr;
		size = 0;
		for (iterator it = _list.begin(); it != _list.end(); it++)
			push_back(*it);
	}
	~List()
	{
		while (first != nullptr)
		{
			Node<T>* temp = first;
			first = first->next;
			delete temp;
		}
		size = 0;
	}
	List<T>& operator=(const List<T>& _list)
	{
		if (this != &_list)
		{
			while (first != nullptr)
			{
				Node<T>* temp = first;
				first = first->next;
				delete temp;
			}
			size = 0;
			for (iterator it = _list.begin(); it != _list.end(); it++)
				push_back(*it);
		}
		return *this;
	}
	Node<T>* get_first() const noexcept { return first; }
	Node<T>* begin() noexcept
	{
		return first;
	}
	Node<T>* end() noexcept
	{
		return nullptr;
	}
	const Node<T>* begin() const noexcept
	{
		return first;
	}
	const Node<T>* end() const noexcept
	{
		return nullptr;
	}
	void push_front(T elem)
	{
		Node<T>* new_node = new Node<T>(elem, first);
		this->first = new_node;
		size++;
	}
	void pop_front()
	{
		if (first == nullptr)
			throw std::logic_error("list is already empty");
		Node<T>* temp = first;
		first = temp->next;
		delete temp;
		size--;
	}
	void insert(T elem, Node<T>* node)
	{
		if (node == nullptr)
			push_front(elem);
		else
		{
			try 
			{
				Node<T>* new_node = new Node<T>(elem, node->next);
				node->next = new_node;
				size++;
			}
			catch (const std::bad_alloc& e) { std::cerr << e.what() << std::endl; }
		}
	}
	void erase(Node<T>* node)
	{
		if (node == nullptr)
			pop_front();
		else
		{
			Node<T>* temp = node->next;
			if (temp != nullptr)
			{
				node->next = temp->next;
				delete temp;
				size--;
			}
			else
				node->next = nullptr;
		}
	}
	Node<T>* get_last()
	{
		if (first == nullptr)
			return nullptr;
		Node<T>* current = first;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		return current;
	}
	void push_back(T elem)
	{
		try
		{
			Node<T>* new_node = new Node<T>(elem, nullptr);
			Node<T>* last_node = this->get_last();
			if (last_node != nullptr) last_node->next = new_node;
			else first = new_node;
			size++;
		}
		catch (const std::bad_alloc& e) { std::cerr << e.what() << std::endl; }
	}
	class iterator
	{
		Node<T>* current;
	public:
		iterator(Node<T>* node) : current(node) {}
		iterator(const Node<T>* node) : current(const_cast<Node<T>*>(node)) {}
		iterator(const iterator& it) { current = it.current; }
		Node<T>* get_current() const noexcept { return current; }
		iterator& operator++()
		{
			current = current->next;
			return *this;
		}
		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this);
			return tmp;
		}
		T& operator*()
		{
			return current->data;	
		}
		const T& operator*() const
		{
			return current->data;
		}
		bool operator==(const iterator& it)
		{
			return this->current == it.current;
		}
		const bool operator==(const iterator& it) const
		{
			return this->current == it.current;
		}
		bool operator!=(const iterator& it)
		{
			return !(*this == it);
		}
	};
};