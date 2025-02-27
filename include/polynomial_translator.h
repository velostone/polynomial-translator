#include "tlist.h"
#include <iostream>

using std::size_t;

class Monom 
{
protected:
	size_t degree;
	double k;
public:
	const size_t MAX_DEG = 9;
	Monom(size_t deg = 0, double kf = 0) : degree(deg), k(kf) 
	{
		if (deg > 999) throw std::invalid_argument("Monom constructor: degree is out of range");
	};
	size_t x_deg() const noexcept { return degree / 100; }
	size_t y_deg() const noexcept { return (degree / 10) % 10; }
	size_t z_deg() const noexcept  { return degree % 10; }
	size_t get_deg() const noexcept { return degree; }
	double get_k() const noexcept  { return k; }
	void set_k(const double _k) noexcept  { k = _k; }
	bool is_deg_correct() const noexcept
	{ return (x_deg() <= MAX_DEG && y_deg() <= MAX_DEG && z_deg() <= MAX_DEG); }
	Monom operator+(const Monom& m) 
	{
		if (this->degree == m.get_deg())
		{
			Monom res(this->degree, this->k + m.get_k());
			if (res.get_k() == 0) return Monom(0, 0);
			return res;
		}
		else throw std::logic_error("cant apply operator+ with monoms");
	}
	Monom operator-(const Monom& m)
	{
		if (this->degree == m.get_deg())
		{
			Monom res(this->degree, this->k - m.get_k());
			if (res.get_k() == 0) return Monom(0, 0);
			return res;
		}
		else throw std::logic_error("cant apply operator- with monoms");
	}
	Monom operator*(const double scal)
	{
		Monom res(this->degree, this->k * scal);
		if (res.get_k() == 0) return Monom(0, 0);
		return res;
	}
	Monom operator*(const Monom& m)
	{
		if (this->x_deg() + m.x_deg() <= MAX_DEG && this->y_deg() + m.y_deg() <= MAX_DEG 
			&& this->z_deg() + m.z_deg() <= MAX_DEG)
		{
			Monom res(this->degree + m.get_deg(), this->k * m.get_k());
			if (res.get_k() == 0) return Monom(0, 0);
			return res;
		}
		else throw std::runtime_error("operator*: degree is out of range");
	}
};

class Polynom : public List<Monom>
{
public:
	Polynom()
	{
		try
		{
			Node<Monom>* p = new Node<Monom>;
			first = p;
			p->next = p;
		}
		catch (const std::bad_alloc& e) { std::cerr << e.what() << std::endl; }
	}
	~Polynom()
	{
		if (first == nullptr) return;
		Node<Monom>* temp = first;
		Node<Monom>* temp_next = nullptr;
		do
		{
			temp_next = temp->next;
			delete temp;
			temp = temp_next;
		} while (temp != first && temp != nullptr);
		first = nullptr;
		size = 0;
	}
	Polynom operator+ (const Polynom& p)
	{
		Polynom res;
		iterator it1 = this->begin()->next;
		iterator it2 = p.begin()->next;
		while (it1 != this->end() && it2 != p.end())
		{
			if ((*it1).get_deg() == (*it2).get_deg())
			{
				res.push_back(*(it1)+*(it2));
				++it1;
				++it2;
			}
			else if ((*it1).get_deg() > (*it2).get_deg())
			{
				res.push_back(*it1);
				++it1;
			}
			else
			{
				res.push_back(*it2);
				++it2;
			}
		}
		if (it1 == this->end())
		{
			while (it2 != p.end())
			{
				res.push_back(*it2);
				++it2;
			}
		}
		if (it2 == p.end())
		{
			while (it1 != this->end())
			{
				res.push_back(*it1);
				++it1;
			}
		}
		return res;
	}
	Polynom operator* (const double scal)
	{
		Polynom res;
		for (iterator it = this->begin()->next; it != this->end(); ++it)
			res.push_back((*it) * scal);
		return res;
	}
	Polynom operator* (const Polynom& p)
	{
		Polynom res;
		iterator it1 = this->begin()->next;
		for (; it1 != this->end(); ++it1) 
		{
			iterator it2 = p.begin()->next;
			for (; it2 != p.end(); ++it2) {
				res.push_back(*(it1) * *(it2));
			}
		}
		return res;
	}
};