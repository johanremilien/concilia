#include "register.h"

template<typename T>
Register<T>::Register() :
    m_register(),
    m_counter(0)
{}

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
