#ifndef __SHARED_PTR__
#define __SHARED_PTR__
//https://blog.csdn.net/u013611405/article/details/88047741
#include <iostream>

using namespace std;

template <typename T>
class Shared_ptr {
public:
    Shared_ptr(): count(0), _ptr((T *)0) {}
    Shared_ptr(T *ptr): count(new int(1)), _ptr(ptr) {}

    Shared_ptr(Shared_ptr<T>& other)
    {
        count = &(++*other.count);
        _ptr = other._ptr;
    }

    T* operator->() { return _ptr; }
    T& operator*() { return *_ptr; }

    Shared_ptr<T>& operator=(Shared_ptr<T>& other)
    {
        if(this == &other)
        {
            return *this;
        }
        ++*other.count;
        if ( _ptr && --*count == 0 )
        {
            delete count;
            delete _ptr;
            cout << "delete ptr int operator=" << endl;
        }
        
        count = other.count;
        _ptr = other._ptr;

        return *this;
    }

    ~Shared_ptr()
    {
        if (_ptr && --*count == 0 )
        {
            delete count;
            delete _ptr;
        }
    }

    int getRef()    { return *count;   }

private:
    int* count;
    T* _ptr;
};

int main(int argc, char *argv[])
{
    Shared_ptr<string> pstr(new string("abc"));
    cout << "pstr:" << pstr.getRef() << " " << *pstr << endl;

    Shared_ptr<string> pstr2(pstr);
	cout << "pstr:"  << pstr.getRef()  << " " << *pstr  << endl;
	cout << "pstr2:" << pstr2.getRef() << " " << *pstr2 << endl;

	Shared_ptr<string> pstr3(new string("hao"));
	cout << "pstr3:" << pstr3.getRef() << " " << *pstr3 << endl;

	pstr3 = pstr2;
	cout << "pstr:"  << pstr.getRef()  << " " << *pstr  << endl;
	cout << "pstr2:" << pstr2.getRef() << " " << *pstr2 <<  endl;
	cout << "pstr3:" << pstr3.getRef() << " " << *pstr3 << endl;

    return 0;
}


#endif
