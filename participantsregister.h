#ifndef PARTICIPANTSREGISTER_H
#define PARTICIPANTSREGISTER_H

#include "register.h"

class Participant;

class ParticipantsRegister : public Register<Participant>
{
public:
    const Participant &create();
    Participants get(QString firstName, QString lastName);
};

#endif // PARTICIPANTSREGISTER_H
