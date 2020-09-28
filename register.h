#ifndef REGISTER_H
#define REGISTER_H

#include <QHash>
#include <type_traits>
#include <typeinfo>
#include <stdexcept>
#include <sstream>

#include "typedef.h"

class RegistrableItem;

template <typename T>
class Register
{
public:
    Register();
    virtual ~Register();
    inline T &operator[](ID id);

protected:
    const T &create();
    inline void clear();
    inline void remove(ID id);
    inline const T &value(ID id) const;
    inline void exception(ID id) const;
    void process(std::function<bool(T &)> f) const;

private:
    RegisterHash<T> m_register;
    ID m_counter;
    const char *m_typeinfo;
};

template<typename T>
Register<T>::Register() :
    m_register(),
    m_counter(-1),
    m_typeinfo(typeid(T).name())
{
    //static_assert(std::is_base_of<RegistrableItem, T>::value, "must derive from RegistrableItem");
}

template<typename T>
Register<T>::~Register()
{
    clear();
}

template<typename T>
const T &Register<T>::value(ID id) const
{
    if (!m_register.contains(id))
        exception(id);
    return m_register.value(id);
}

template<typename T>
void Register<T>::exception(ID id) const
{
    std::ostringstream oss;
    oss << m_typeinfo << " no corresponding index: " << id;
    throw std::runtime_error(oss.str());
}

template<typename T>
void Register<T>::process(std::function<bool(T &)> func) const
{
    for (auto &item : m_register.values()) {
        if (func(item))
            break;
    }
}

template<typename T>
T &Register<T>::operator[](ID id)
{
    if (!m_register.contains(id))
        exception(id);
    return m_register[id];
}

template<typename T>
const T &Register<T>::create()
{
    m_counter++;
    return *(m_register.insert(m_counter, T(m_counter)));
}

template<typename T>
void Register<T>::clear() {
    m_register.clear();
    m_counter = 0;
}

template<typename T>
void Register<T>::remove(ID id) {
    m_register.take(id);
}

#endif // REGISTER_H
