#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QString>
#include <QVector>
#include <type_traits>

#include "registrableitem.h"

class Participant : public RegistrableItem<Participant>
{
public:
    const QString &getFirstName() const;
    const QString &setFirstName(const QString &firstName);

    const QString &getLastName() const;
    const QString &setLastName(const QString &lastName);

    bool getIsSpeaking() const;
    bool setIsSpeaking(bool isSpeaking);

    duration getTotalSpeakingTime(id meetingID = UNDEFINED_ID) const;

    inline void takePartInCurrentMeeting();

    virtual inline bool operator==(const Participant &) override;
    static void setCurrentMeetingID(id meetingID);

    friend class Register<Participant>;

protected:
    explicit Participant(id id);
    ~Participant();

private:
    QString m_firstName;
    QString m_lastName;
    bool m_isSpeaking;
    RecordVectorHash m_records;
    static id s_currentMeetingID;
};

#endif // PARTICIPANT_H