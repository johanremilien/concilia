#include "register.h"

template<typename T>
Register<T> *Register<T>::s_instance = nullptr;

template<typename T>
Register<T>::Register() :
    m_register(),
    m_counter(0)
{
    s_instance = this;
}

template<typename T>
Register<T>::~Register()
{
    clear();
}

template<typename T>
T *Register<T>::get(id id)
{
    return m_register.value(id, nullptr);
}

template<typename T>
RegisterVector<T> Register<T>::getRegisterVector() const
{
    return m_register.values().toVector();
}

template<typename T>
Register<T> &Register<T>::instance()
{
    return *(s_instance ? s_instance : new Register());
}

template<typename T>
void Register<T>::clear()
{
    for (auto & item : m_register)
        delete *item;
    m_register.clear();
    m_counter = 0;
}

template<typename T>
void Register<T>::remove(id id)
{
    if (m_register.contains(id))
        delete m_register.take(id);
}
