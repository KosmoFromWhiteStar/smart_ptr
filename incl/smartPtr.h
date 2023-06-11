#pragma once
#include <iostream>
#include <vector>

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
	int* counter = new int(0);

public:
	int get_count()
	{
		return *counter;
	}

	Shared_ptr_toy() : toy() {};
	Shared_ptr_toy(std::string name)
	{
		if (toy == nullptr) toy = new Toy(name);
	}
	Shared_ptr_toy(const Shared_ptr_toy& oth)
	{
		if (oth.toy == nullptr)return;
		this->counter = oth.counter;
		this->toy = oth.toy;
		
	}
	Shared_ptr_toy& operator= (const Shared_ptr_toy& oth)
	{
		if (&oth == nullptr) return *this;
		if (*(this->counter) > 0) (*(this->counter))--;
		counter = oth.counter;
		(*counter)++;
		toy = oth.toy;
		return *this;
	}

	~Shared_ptr_toy()
	{
		(*counter)--;
		if (*counter == 0) delete toy;
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
		toys = *toy;
	};
	Box& operator= (Shared_ptr_toy& oth)
	{
		toys = oth;
		return *this;
	}

	Box() {};
	~Box()
	{
		//delete toys;
	}
};

void ex1()
{
	//Tests
	Shared_ptr_toy Balls{ "Balls" };
	Box b1, b2, b3;
	b1 = make_shared(Balls);
	b2 = make_shared(Balls);
	b3 = make_shared(Balls);

	std::cout << "3 Balls --------------------------\n";
	std::cout << "Balls: " << Balls.get_count() << std::endl;


	std::cout << "2 Balls, 1 Bone --------------------------\n";
	Shared_ptr_toy Bone{ "Bone" };
	b1 = make_shared(Bone);
	std::cout << "Balls: " << Balls.get_count() << std::endl;
	std::cout << "Bone: " << Bone.get_count() << std::endl;

	std::cout << "3 Bone --------------------------\n";
	b2 = make_shared(Bone);
	b3 = make_shared(Bone);
	std::cout << "Balls: " << Balls.get_count() << std::endl;
	std::cout << "Bone: " << Bone.get_count() << std::endl;

}

void do_ex(void(*ex)() = ex1)
{
	ex();
}
