#include <iostream>

using namespace std;

class Animal
{
private: 
	int height;

public:
	virtual void say()//
	{
		cout << "I am animal. " << endl;
	}

	virtual void run() = 0;//

};

class Cat : public Animal
{
private:
	int color;
public:
	void say()//重写虚函数
	{
		cout << "I am a cat" << endl;
	}
	void run()//必须重写纯虚函数
	{
		cout << "cat run " << endl;
	}
};

class Dog : public Animal
{
private:
	int weight;
public:
	void say()
	{
		cout << "I am a dog" <<endl;
	}
	void run()
	{
		cout << "dog run" << endl;
	}
};

class Person: public Animal
{
private:
	int id;
public:
	void run()//可以不重载虚函数，但是必须重载纯虚函数
	{
		cout << "person run" << endl;
	}
	
};
