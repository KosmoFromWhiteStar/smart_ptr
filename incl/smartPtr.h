#pragma once
#include <iostream>

class Toy
{
private:
	std::string name;

public:
	Toy(std::string in_name) : name(in_name) {};
	Toy() : Toy("Some Toy") {};
	//Yavno ukazal
	Toy(Toy* oth): name(oth->name){};

	
};

class Shared_ptr_toy
{
private:
	Toy* toy = nullptr;
	int count = 0;
	const int* count_this_toy = &count;
	
public:
	Shared_ptr_toy() :toy(new Toy()) { count++; };
	Shared_ptr_toy(std::string in_name) :toy(new Toy(in_name)) { count++; };
	Shared_ptr_toy& operator= (const Shared_ptr_toy& oth)
	{
		if (this == &oth)
			return *this;
		if (toy != nullptr) delete toy;
		toy = new Toy(oth.toy);
	}

	void reset()
	{
		delete this->toy;
		count = 0;
	}
	Toy* get()
	{
		if (toy == nullptr) return nullptr;
		return toy;
	}

	~Shared_ptr_toy()
	{
		count--;
		delete this->toy;
	}
};

Shared_ptr_toy* make_shared_ptr(std::string in_name) {
	return new Shared_ptr_toy(in_name);
}

Shared_ptr_toy* make_shared_ptr(Shared_ptr_toy* toy) {
	return new Shared_ptr_toy(*toy);
}

class Box
{
	Shared_ptr_toy toys;
public:
	Box(Shared_ptr_toy* toy) : toys(*toy) {};
	Box() : toys(nullptr) {};
};

void ex1()
{
	Box box[2];


}

void do_ex(void(*ex)() = ex1)
{
	ex();
}
