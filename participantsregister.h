#ifndef PARTICIPANTSREGISTER_H
#define PARTICIPANTSREGISTER_H

#include "register.h"

class Participant;

class ParticipantsRegister : public Register<Participant>
{
public:
    const Participant &create(const QString &firstName, const QString &lastName);
    Participants find(const QString &firstName,const QString &lastName) const;
    inline const QString &setFirstName(id id, const QString &firstName);
    inline const QString &setLastName(id id, const QString &lastName);
    inline const Participant &rename(id id, const QString &firstName, const QString &lastName);

    friend class Register<Participant>;
protected:
    inline const Participant &create();

};

#endif // PARTICIPANTSREGISTER_H
