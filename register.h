#ifndef REGISTER_H
#define REGISTER_H

#include <QHash>

#include "typedef.h"

template <typename T>
class Register
{
    Register();
    ~Register();
public:
    inline T *get(id id);
    RegisterVector<T> getRegisterVector() const;
    static Register<T> &instance();

protected:
    T &create();
    inline void clear();
    void remove(id id);

    RegisterHash<T> m_register;
    id m_counter;
    static Register<T> *s_instance;
};

#endif // REGISTER_H
