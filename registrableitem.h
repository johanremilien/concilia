#ifndef REGISTRABLEITEM_H
#define REGISTRABLEITEM_H

#include "typedef.h"

template <typename T>
class RegistrableItem
{
public:
    inline id getId() const;
    inline id setId(id id);
    virtual inline bool operator==(const T &) = 0;

protected:
    RegistrableItem(id id = UNDEFINED_ID);
    virtual ~RegistrableItem();

private:
    id m_id;
};

template <typename T>
RegistrableItem<T>::RegistrableItem(id id) :
    m_id(id)
{}

template <typename T>
RegistrableItem<T>::~RegistrableItem()
{}

template <typename T>
id RegistrableItem<T>::getId() const
{
    return m_id;
}

template <typename T>
id RegistrableItem<T>::setId(id id)
{
    return (m_id = id);
}

#endif // REGISTRABLEITEM_H
