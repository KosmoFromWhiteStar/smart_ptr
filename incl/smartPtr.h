#pragma once
#include <iostream>

class Toy
{
private:
	std::string name;

public:
	Toy(std::string in_name) : name(in_name) {};
	Toy() : Toy("Some Toy") {};
};



class Smart_ptr_toy
{
private:
	
	Toy* obj;
public:

	Smart_ptr_toy() : obj(new Toy()) {};
	Smart_ptr_toy(std::string in_name) : obj(new Toy(in_name)) {}
	Smart_ptr_toy(const Smart_ptr_toy& other) : obj(new Toy(*other.obj)) {};
	Smart_ptr_toy& operator= (const Smart_ptr_toy& other)
	{
		if (this == &other) { return *this; }
		if (obj != nullptr) delete obj;
		obj = new Toy(*other.obj);
		return *this;
	}
	~Smart_ptr_toy() { delete obj;}
};

// ??? if have on class constructors, why 
//   this is need
//     |
//    \ /
//     V

Smart_ptr_toy* make_shared_toy(std::string in_name)
{
	return new Smart_ptr_toy{ in_name };
}

Smart_ptr_toy* make_shared_toy(Smart_ptr_toy& other)
{
	return new Smart_ptr_toy{ other };
}

//There are have steal memory 


void ex1()
{
	Smart_ptr_toy toys[10];
	for (int i = 0; i < 10; i++)
	{
		toys[i] = *make_shared_toy("Balls #");
	}
	
	std::cout << count << std::endl;
}

void do_ex(void(*ex)() = ex1)
{
	ex();
}
