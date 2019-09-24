#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	vector<int> v;
	for (int i = 0; i < 5; i++)
	{
		v.push_back(i);
	}

	vector<int>::iterator it;
	cout << "sizeof(it): " << sizeof(it) << endl;
	for (it = v.begin(); it != v.end();)
	{
		if ( *it > 2)
			it = v.erase(it);
		else
			it++;
	}
	
	for (it = v.begin(); it != v.end(); it++)
		cout << *it << "  ";
	cout << endl;

	return 0;
}
