#ifndef REGISTRABLEITEM_H
#define REGISTRABLEITEM_H

#include "typedef.h"

template <typename T>
class RegistrableItem
{
public:
    inline ID getId() const;
    inline ID setId(ID id);
    virtual inline bool operator==(const T &) = 0;

protected:
    RegistrableItem(ID id = UNDEFINED_ID);
    virtual ~RegistrableItem();

private:
    ID m_id;
};

template <typename T>
RegistrableItem<T>::RegistrableItem(ID id) :
    m_id(id)
{}

template <typename T>
RegistrableItem<T>::~RegistrableItem()
{}

template <typename T>
ID RegistrableItem<T>::getId() const
{
    return m_id;
}

template <typename T>
ID RegistrableItem<T>::setId(ID id)
{
    return (m_id = id);
}

#endif // REGISTRABLEITEM_H
