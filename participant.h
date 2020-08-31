#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QString>
#include <QVector>

#include "typedef.h"

class ParticipantsRegister;
class SpeakingTimeRecorder;

class Participant
{
public:
    id getId() const;
    const QString &getFirstName() const;
    const QString &getLastName() const;
    void toggleSpeakingState();
    duration getTotalSpeakingTime(id meetingID = m_currentMeetingID) const;
    static void setCurrentMeetingID(id meetingID);

    friend class ParticipantsRegister;
    friend class SpeakingTimeRecorder;

protected:
    explicit Participant(id id = UNDEFINED_ID);
    Participant(const QString &firstName, const QString &lastName, id id = UNDEFINED_ID);
    ~Participant();
    id setId(id id);
    const QString &setFirstName(const QString &firstName);
    const QString &setLastName(const QString &lastName);
    const Participant &rename(const QString &firstName, const QString &lastName);
    inline void takePartInCurrentMeeting();
    void setIsSpeaking(bool isSpeaking);

private:
    id m_id;
    QString m_firstName;
    QString m_lastName;
    bool m_isSpeaking;
    RecordVectorHash m_records;
    static id m_currentMeetingID;
};

#endif // PARTICIPANT_H
