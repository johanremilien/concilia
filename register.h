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
    inline T &operator[](id id);

protected:
    const T &create();
    inline void clear();
    inline void remove(id id);
    inline T *get(id id) const;
    inline T *itemNotFoundWarning(id id) const;
    inline void itemNotFoundFatal(id id) const;
    void process(std::function<bool(T &)> f) const;

private:
    RegisterHash<T> m_register;
    id m_counter;
    const char *m_typeinfo;
};

template<typename T>
Register<T>::Register() :
    m_register(),
    m_counter(0),
    m_typeinfo(typeid(T).name())
{
    static_assert(std::is_base_of<RegistrableItem<T>, T>::value, "must derive from RegistrableItem");
}

template<typename T>
Register<T>::~Register()
{
    clear();
}

template<typename T>
T *Register<T>::get(id id) const
{
    return m_register.value(id, itemNotFoundWarning(id));
}

template<typename T>
T *Register<T>::itemNotFoundWarning(id id) const
{
    qWarning("%s index: %d not found.", m_typeinfo, id);
    return nullptr;
}

template<typename T>
void Register<T>::itemNotFoundFatal(id id) const
{
    qFatal("%s index: %d not found.", m_typeinfo, id);
}

template<typename T>
void Register<T>::process(std::function<bool(T &)> func) const
{
    for (const auto &item : m_register.values()) {
        if (func(*item))
            break;
    }
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
T &Register<T>::operator[](id id)
{
    if (m_register.contains(id))
        return m_register[id];
    else
        itemNotFoundFatal(id);
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
