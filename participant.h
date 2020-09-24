#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QVector>

#include <register.h>
#include "registrableitem.h"

class Participant : public RegistrableItem<Participant>
{
public:
    explicit Participant(ID id = UNDEFINED_ID);
    ~Participant();

    QString getFirstName() const;
    QString setFirstName(QString firstName);

    QString getLastName() const;
    QString setLastName(QString lastName);

    bool getIsSpeaking() const;
    bool setIsSpeaking(bool isSpeaking);

    Duration getTotalSpeakingTime(ID meetingID) const;

    inline void takePartInCurrentMeeting();

    virtual inline bool operator==(const Participant &) override;
    static void setCurrentMeetingID(ID meetingID);

    friend class Register<Participant>;

private:
    QString m_firstName;
    QString m_lastName;
    bool m_isSpeaking;
    RecordVectorHash m_records;
    static ID s_currentMeetingID;
};

#endif // PARTICIPANT_H
