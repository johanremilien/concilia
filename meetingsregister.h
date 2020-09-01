#ifndef MEETINGSREGISTER_H
#define MEETINGSREGISTER_H

#include "register.h"

class Meeting;

class MeetingsRegister : public Register<Meeting>
{
public:
    const Meeting &create(const QString &name);
    Meetings find(const QString &name) const;

protected:
    using Register<Meeting>::create;
};

#endif // MEETINGSREGISTER_H
