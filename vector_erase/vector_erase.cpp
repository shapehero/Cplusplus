#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
	vector<int> v;
	cout << "v.size(): " << v.size() << endl;
	cout << "v.capacity(): " << v.capacity() << endl;
	v.resize(10);
	cout << "v.size(): " << v.size() << endl;
	cout << "v.capacity(): " << v.capacity() << endl;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	cout << "v.size(): " << v.size() << endl;
	cout << "v.capacity(): " << v.capacity() << endl;
	for (vector<int>::iterator iter = v.begin(); iter != v.end(); )
	{
		if ( *iter == 5 )
			iter = v.erase(iter);
		else
			iter++;
	}

	for (vector<int>::const_iterator iter = v.begin(); iter != v.end(); iter++)
		cout << *iter << endl;

	return 0;
}
