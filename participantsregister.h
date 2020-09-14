#ifndef PARTICIPANTSREGISTER_H
#define PARTICIPANTSREGISTER_H

#include "register.h"

class ParticipantsRegister : public Register<Participant>
{
public:
    const Participant &create(const QString &firstName, const QString &lastName);
    const QString &getFirstName(ID id) const;
    inline const QString &setFirstName(ID id, const QString &firstName);
    const QString &getLastName(ID id) const;
    inline const QString &setLastName(ID id, const QString &lastName);
    const Participant &rename(ID id, const QString &firstName, const QString &lastName);
    bool toggleSpeakingState(ID id);
    Duration getTotalSpeakingTime(ID participantID,ID meetingID = UNDEFINED_ID) const;

    ID find(const QString &firstName,const QString &lastName) const;
    IDs findByFirstName(const QString &firstName) const;
    IDs findByLastName(const QString &lastName) const;
    IDs findIncompleteNames(const QString &firstName, const QString &lastName) const;

protected:
    using Register<Participant>::create;
};

#endif // PARTICIPANTSREGISTER_H
