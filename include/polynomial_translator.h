#include "tlist.h"
#include <iostream>

using std::size_t;

class Monom 
{
protected:
	size_t degree;
	double k;
	const size_t MAX_DEG = 9;
	const size_t MAX_TOTAL_DEG = 999;
public:
	Monom(size_t deg = 0, double kf = 0) : degree(deg), k(kf) 
	{
		if (deg > MAX_TOTAL_DEG) throw std::invalid_argument("Monom constructor: degree is out of range");
	};
	size_t x_deg() const noexcept { return degree / 100; }
	size_t y_deg() const noexcept { return (degree / 10) % 10; }
	size_t z_deg() const noexcept  { return degree % 10; }
	bool is_deg_correct() const noexcept
	{ return (x_deg() <= MAX_DEG && y_deg() <= MAX_DEG && z_deg() <= MAX_DEG); }
	Monom operator+(const Monom& m) 
	{
		if (this->degree == m.degree)
		{
			Monom res(this->degree, this->k + m.k);
			if (res.k == 0) return Monom(0, 0);
			return res;
		}
		else throw std::logic_error("cant apply operator+ with monoms");
	}
	Monom operator-(const Monom& m)
	{
		if (this->degree == m.degree)
		{
			Monom res(this->degree, this->k - m.k);
			if (res.k == 0) return Monom(0, 0);
			return res;
		}
		else throw std::logic_error("cant apply operator- with monoms");
	}
	Monom operator*(const double scal)
	{
		Monom res(this->degree, this->k * scal);
		if (res.k == 0) return Monom(0, 0);
		return res;
	}
	Monom operator*(const Monom& m)
	{
		if (this->degree + m.degree <= MAX_TOTAL_DEG)
		{
			Monom res(this->degree + m.degree, this->k * m.k);
			if (res.k == 0) return Monom(0, 0);
			return res;
		}
		else throw std::runtime_error("operator*: degree is out of range");
	}
};

class Polynom : public List<Monom>
{
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
		iterator it1 = this->begin();
		iterator it2 = p.begin();
		iterator it3 = res.begin();
		while (it1 != this->end() && it2 != p.end()) 
		{
			if ((*it1).degree == (*it2).degree) 
			{
				res.isert(it1.get_current() + it2.get_current(), it3)
					++it1; ++it2; ++it3;
			}
			else if ((*it1).degree > (*it2).degree) 
			{
				res.insert(it1.get_current(), it3);
				++it3; ++it1;
			}
			else if ((*it2).degree > (*it1).degree) 
			{
				res.insert(it2.get_current(), it3);
				++it3; ++it2;
			}
		}
		if (it1 == end()) 
		{
			while (it2 != end())
			{
				res.insert(it2.get_current(), it3)
					++it2; ++it3;
			}
		}
		return res;
	}

};