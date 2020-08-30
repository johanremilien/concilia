#ifndef REGISTER_H
#define REGISTER_H

#include <QHash>

#include "typedef.h"

template <typename T>
class Register
{
public:
    Register();
    ~Register();
    T &create();
    inline T *get(id id);

protected:
    inline void clear();
    void remove(id id);

    RegisterHash<T> m_register;
    id m_counter;
};

#endif // REGISTER_H
