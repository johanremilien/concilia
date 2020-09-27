#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <QVector>

#include <register.h>
#include "registrableitem.h"

class Participant : public RegistrableItem
{
    Q_OBJECT

    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName NOTIFY firstNameChanged)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName NOTIFY lastNameChanged)
    Q_PROPERTY(bool isSpeaking READ isSpeaking WRITE setIsSpeaking NOTIFY isSpeakingChanged)

public:
    explicit Participant(ID id = UNDEFINED_ID, QObject *parent = nullptr);
    Participant(const Participant &p);
    ~Participant() = default;

    QString firstName() const;
    void setFirstName(QString firstName);

    QString lastName() const;
    void setLastName(QString lastName);

    bool isSpeaking() const;
    void setIsSpeaking(bool isSpeaking);

    Duration totalSpeakingTime(ID meetingID) const;

    inline void takePartInCurrentMeeting();

    Participant &operator=(const Participant &p);
    bool operator==(const Participant &p);
    static void setCurrentMeetingID(ID meetingID);

    friend class Register<Participant>;

signals:
    void firstNameChanged(QString firstName);
    void lastNameChanged(QString lastName);
    void isSpeakingChanged(bool isSpeaking);

private:
    QString m_firstName;
    QString m_lastName;
    bool m_isSpeaking;
    RecordVectorHash m_records;
    static ID s_currentMeetingID;
};

#endif // PARTICIPANT_H
