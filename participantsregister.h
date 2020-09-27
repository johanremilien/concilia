#ifndef PARTICIPANTSREGISTER_H
#define PARTICIPANTSREGISTER_H

#include "register.h"

class ParticipantsRegister : public Register<Participant>
{
public:
    const Participant &create(QString firstName, QString lastName);
    QString firstName(ID id) const;
    void setFirstName(ID id, QString firstName);
    QString lastName(ID id) const;
    inline void setLastName(ID id, QString lastName);
    const Participant &rename(ID id, QString firstName, QString lastName) noexcept;
    void toggleSpeakingState(ID id);
    Duration totalSpeakingTime(ID participantID,ID meetingID = UNDEFINED_ID) const;

    ID find(QString firstName,QString lastName) const noexcept;
    IDs findByFirstName(QString firstName) const noexcept;
    IDs findByLastName(QString lastName) const noexcept;
    IDs findIncompleteNames(QString firstName, QString lastName) const noexcept;

protected:
    using Register<Participant>::create;
};

#endif // PARTICIPANTSREGISTER_H
