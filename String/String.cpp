#include <iostream>
#include <cstring>

class String {
public:
	inline explicit String(const char *str)
	{
		std::cout << "default constructor" << std::endl;
		if (!str)
		{
			m_data = nullptr;
			return;
		}
		m_data = new char[strlen(str)+1];
		strcpy(m_data, str);
	}

	inline String(const String &other)
	{
		std::cout << "copy constructor" << std::endl;
		if (!other.m_data)
		{
			m_data = nullptr;
		}
		m_data = new char[strlen(other.m_data)+1];
		strcpy(m_data, other.m_data);
	}
	
	inline String(String &&other)
	{
		std::cout << "Move constructor" << std::endl;
		m_data = other.m_data;
		other.m_data = nullptr;
	}

	inline String& operator=(const String &other)
	{
		std::cout << "copy operator=" << std::endl;
		if (this == &other)
			return *this;
		delete [] m_data;
		if (!other.m_data)
			m_data = nullptr;
		else
		{
			m_data = new char[strlen(other.m_data) +  1];
			strcpy(m_data, other.m_data);
		}
		return *this;	
	}

	inline String& operator=(String &&other)
	{
		std::cout << "Move operator" << std::endl;
		m_data = other.m_data;
		other.m_data = nullptr;
		return *this;
	}

	inline bool operator==(String &other)
	{
		std::cout << "operaotr==" << std::endl;
		if (strlen(m_data) != strlen(other.m_data))
			return false;
		return strcmp(m_data, other.m_data) ? false : true;
	}

	inline String& operator+(String &other)
	{
		std::cout << "operator+" << std::endl;
		if (!m_data)
			return other;
		if (!other.m_data)
			return *this;
		strcat(m_data, other.m_data);
		return *this;
	}

	inline char& operator[](const unsigned int e) const
	{
		std::cout << "operator[]" << std::endl;
		if ( e < 0 || e > strlen(m_data) - 1)
			throw("out of bound");

		return m_data[e];
	}

	inline ~String()
	{
		std::cout << "deconstructor" << std::endl;
		delete [] m_data;
	}

	inline char* get_data() const { return m_data; }

private:
	char *m_data;
};

int main()
{
	String s1("xing");
	std::cout << "s1: " << s1.get_data() << std::endl;

	String s2("zhuang");
	std::cout << "s2: " << s2.get_data() << std::endl;

	String s3 = s2 + s1;
	std::cout << "s3: " << s3.get_data() << std::endl;

	std::cout << "s1: " << s1.get_data() << std::endl;
	std::cout << "s2: " << s2.get_data() << std::endl;
	String s4 = std::move(s1 + s2);
	std::cout << "s4: " << s4.get_data() << std::endl;
	std::cout << "s4[4]: " << s4[4] << std::endl;
	return 0;
}
