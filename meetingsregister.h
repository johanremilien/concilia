#ifndef MEETINGSREGISTER_H
#define MEETINGSREGISTER_H

#include "register.h"

class Meeting;

class MeetingsRegister : public Register<Meeting>
{
public:
    MeetingsRegister();
    const Meeting &create(const QString &name = QString());
    Meetings get(const QString &name);
};


#endif // MEETINGSREGISTER_H
