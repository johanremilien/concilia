#ifndef REGISTER_H
#define REGISTER_H

#include <QHash>
#include <type_traits>
#include <typeinfo>

#include "typedef.h"

template <typename>
class RegistrableItem;

template <typename T>
class Register
{
public:
    Register();
    ~Register();
    inline RegisterVector<T> getRegisterVector() const;

protected:
    const T &create();
    inline void clear();
    inline void remove(id id);
    inline T *get(id id) const;
    inline void itemNotFound(id id);

protected:
    RegisterHash<T> m_register;

private:
    id m_counter;
    QString m_typeinfo;
};

template<typename T>
Register<T>::Register() :
    m_register(),
    m_counter(0)
{
    static_assert (std::is_base_of<RegistrableItem<T>, T>::value, "Register<T> :T must derive from RegistrableItem");
    m_typeinfo = typeid(T).name();
}

template<typename T>
Register<T>::~Register()
{
    clear();
}

template<typename T>
T *Register<T>::get(id id) const
{
    return m_register.value(id, nullptr);
}

template<typename T>
void Register<T>::itemNotFound(id id)
{
    qWarning("%s index: %d not found.", qUtf8Printable(m_typeinfo), id);
}

template<typename T>
RegisterVector<T> Register<T>::getRegisterVector() const
{
    RegisterVector<T> result;
    for (auto & item : m_register.values())
        result.append(item);
    return result;
}

template<typename T>
const T &Register<T>::create()
{
    T *item = new T(m_counter++);
    return **(m_register.insert(item->getId(), item));
}

template<typename T>
void Register<T>::clear() {
    for (auto & item : m_register.values())
        delete item;
    m_register.clear();
    m_counter = 0;
}

template<typename T>
void Register<T>::remove(id id) {
    if (m_register.contains(id))
        delete m_register.take(id);
}

#endif // REGISTER_H
