/*
这是一个线程不安全的单例类
*/

class Singleton {
private:
    Singleton() { }
    static Singleton *m_pInstance;

public:
    static Singleton* GetInstance();
};
Singleton* Singleton::m_pInstance = NULL;

Singleton* Singleton::GetInstance()
{
    if (m_pInstance == NULL)
        m_pInstance = new Singleton();

    return m_pInstance;
}
