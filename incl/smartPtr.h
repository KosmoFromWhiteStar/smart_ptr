#pragma once
#include <iostream>

class Toy
{
private:
	std::string name;

public:
	Toy(std::string in_name) : name(in_name) {};
	Toy() : Toy("Some Toy") {};
	Toy(Toy* toy) : name(toy->name) {};
};

class Shared_ptr_toy
{
private:
	Toy* toy = nullptr;
	mutable int count = 0;
	const int* count_this_toy = &count;
public:
	Shared_ptr_toy() :toy(new Toy()) {};
	Shared_ptr_toy(std::string in_name) :toy(new Toy(in_name)) {};
	Shared_ptr_toy& operator= (const Shared_ptr_toy& oth)
	{
		if (this == &oth)
			return *this;
		if (toy != nullptr) delete toy;
		toy = new Toy( oth.toy );
		oth.count += 1;
	}

	int get_count()
	{
		return count;
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

Shared_ptr_toy make_shared_ptr(std::string in_name) {
	Shared_ptr_toy temp (in_name);
	return temp;
}

Shared_ptr_toy make_shared_ptr(Shared_ptr_toy* toy) {
	Shared_ptr_toy temp(*toy);
	return temp;
}

Shared_ptr_toy make_shared_ptr() {
	Shared_ptr_toy temp;
	return temp;
}

class Box
{
public:
	Shared_ptr_toy toys;
	Box(Shared_ptr_toy* toy) {
		toys = *toy;
	};
	Box() {};
};

void ex1()
{
	Shared_ptr_toy Ball = { "Ball" };
	Box box[2] = { &Ball, &Ball };

	std::cout << Ball.get_count() << std::endl;
}

void do_ex(void(*ex)() = ex1)
{
	ex();
}
