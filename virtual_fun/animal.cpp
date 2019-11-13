#include "animal.h"
#include <list>

int main(int argc, char *argv[])
{
	list<Animal* > animals;
	
	Animal *a = new Dog();
	Animal *b = new Cat();
	Animal *c = new Person();

	animals.push_back(a);
	animals.push_back(b);
	animals.push_back(c);

	for (auto animal: animals)
	{
		animal->say();
	}

	for (auto animal: animals)
	{
		animal->run();
	}

	return 0;
}
