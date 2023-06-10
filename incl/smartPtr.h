#pragma once
#include <iostream>
#include <vector>

class Toy
{
private:
	std::string name;
	int count = 0;

public:
	int get_count()
	{
		return count;
	}
	void count_p()
	{
		count++;
	}
	void count_m()
	{
		count--;
	}
	Toy(std::string in_name) : name(in_name) {};
	Toy() : Toy("Some Toy") {};
	Toy(Toy* toy) : name(toy->name) {};
};

class Shared_ptr_toy
{
private:
	Toy* toy = nullptr;

public:
	Shared_ptr_toy() : toy() {};
	Shared_ptr_toy(std::string name)
	{
		if (toy == nullptr) toy = new Toy(name);
		toy->count_p();
	}
	Shared_ptr_toy(const Shared_ptr_toy& oth)
	{
		if (oth.toy == nullptr)return;
		this->toy = oth.toy;
		toy->count_p();
	}
	Shared_ptr_toy operator= (Shared_ptr_toy* oth)
	{
		if (oth == nullptr) return *this;
		if(toy != nullptr) 
			toy->count_m();
		toy = oth->toy;
		toy->count_p();
		return *this;
	}

	int get_count()
	{
		return (toy->get_count());
	}
	~Shared_ptr_toy()
	{
		toy->count_m();
		if (toy->get_count() == 0) delete toy;
		toy = nullptr;
	}
};

Shared_ptr_toy* make_shared(std::string name)
{
	return new Shared_ptr_toy(name);
}

Shared_ptr_toy* make_shared(Shared_ptr_toy& oth)
{
	return new Shared_ptr_toy(oth);
}

class Box
{
	Shared_ptr_toy toys;
public:

	Box(Shared_ptr_toy* toy) {
		toys = toy;
	};
	void operator= (Shared_ptr_toy* toy)
	{
		toys = toy;
	}
	Box() {};
};

void ex1()
{
	/// HERE





	///HERE END
}

void do_ex(void(*ex)() = ex1)
{
	ex();
}
