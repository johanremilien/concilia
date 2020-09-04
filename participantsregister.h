#ifndef PARTICIPANTSREGISTER_H
#define PARTICIPANTSREGISTER_H

#include "register.h"

class ParticipantsRegister : public Register<Participant>
{
public:
    const Participant &create(const QString &firstName, const QString &lastName);
    const QString &getFirstName(id id) const;
    inline const QString &setFirstName(id id, const QString &firstName);
    const QString &getLastName(id id) const;
    inline const QString &setLastName(id id, const QString &lastName);
    const Participant &rename(id id, const QString &firstName, const QString &lastName);
    bool toggleSpeakingState(id id);
    duration getTotalSpeakingTime(id participantID,id meetingID = UNDEFINED_ID) const;

    id find(const QString &firstName,const QString &lastName) const;
    IDs findByFirstName(const QString &firstName) const;
    IDs findByLastName(const QString &lastName) const;
    IDs findIncompleteNames(const QString &firstName, const QString &lastName) const;

protected:
    using Register<Participant>::create;
};

#endif // PARTICIPANTSREGISTER_H
