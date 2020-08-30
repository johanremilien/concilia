#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QString>
#include <QVector>

#include "typedef.h"
#include "participantsregister.h"

class Participant
{
public:
    id getId() const;
    const QString &getFirstName() const;
    const QString &getLastName() const;
    void toggleSpeakingState();
    duration getTotalSpeakingTime() const;

    friend const Participant &ParticipantsRegister::create();

protected:
    Participant(id id = UNDEFINED_ID);
    Participant(const QString &firstName, const QString &lastName, id id = UNDEFINED_ID);
    ~Participant();
    id setId(id id);
    const QString &setFirstName(const QString &firstName);
    const QString &setLastName(const QString &lastName);
    void takePartInMeeting(id meetingID);
    void setIsSpeaking(bool isSpeaking);

private:
    id m_id;
    id m_meetingID;
    QString m_firstName;
    QString m_lastName;
    bool m_isSpeaking;
    //Records m_records;
};

#endif // PARTICIPANT_H
