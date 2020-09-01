#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QString>
#include <QVector>
#include <type_traits>

#include "registrableitem.h"

template <typename>
class Register;

class ParticipantsRegister;
class SpeakingTimeRecorder;

class Participant : public RegistrableItem<Participant>
{
public:
    const QString &getFirstName() const;
    const QString &getLastName() const;
    void toggleSpeakingState();
    duration getTotalSpeakingTime(id meetingID = UNDEFINED_ID) const;
    static void setCurrentMeetingID(id meetingID);
    virtual inline bool operator==(const Participant &) override;

    friend class Register<Participant>;
    friend class ParticipantsRegister;
    friend class SpeakingTimeRecorder;

protected:
    explicit Participant(id id = UNDEFINED_ID);
    Participant(const QString &firstName, const QString &lastName, id id = UNDEFINED_ID);
    ~Participant();
    const QString &setFirstName(const QString &firstName);
    const QString &setLastName(const QString &lastName);
    const Participant &rename(const QString &firstName, const QString &lastName);
    inline void takePartInCurrentMeeting();
    void setIsSpeaking(bool isSpeaking);

private:
    QString m_firstName;
    QString m_lastName;
    bool m_isSpeaking;
    RecordVectorHash m_records;
    static id s_currentMeetingID;
};

#endif // PARTICIPANT_H
