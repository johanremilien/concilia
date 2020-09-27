#include "participant.h"

ID Participant::s_currentMeetingID = UNDEFINED_ID;

Participant::Participant(ID id, QObject *parent) :
    RegistrableItem(id, parent),
    m_firstName(QString()),
    m_lastName(QString()),
    m_isSpeaking(false)
{
}

Participant::Participant(const Participant &p) :
    RegistrableItem(p.id(), p.parent()),
    m_firstName(p.m_firstName),
    m_lastName(p.m_lastName),
    m_isSpeaking(p.m_isSpeaking)
{
}

QString Participant::firstName() const
{
    return m_firstName;
}

QString Participant::lastName() const
{
    return m_lastName;
}

void Participant::takePartInCurrentMeeting()
{
    if (!m_records.contains(s_currentMeetingID)) {
        m_records.insert(s_currentMeetingID, QVector<Record>());
    }
}

Participant &Participant::operator=(const Participant &p)
{
    setId(p.id());
    setFirstName(p.m_firstName);
    setLastName(p.m_lastName);
    setIsSpeaking(p.m_isSpeaking);
    return *this;
}

Duration Participant::totalSpeakingTime(ID meetingID) const
{
    Duration duration = 0;
    if (meetingID == UNDEFINED_ID) {
        for (const auto & meetingID : m_records.keys())
            duration += totalSpeakingTime(meetingID);
    } else if (m_records.contains(meetingID)) {
        for (const auto &record : m_records.value(meetingID))
            duration += record.startTime.secsTo(record.endTime);
    }
    return duration;
}

void Participant::setCurrentMeetingID(ID meetingID)
{
    s_currentMeetingID = meetingID;
}

bool Participant::operator==(const Participant &p)
{
    return (m_firstName == p.m_firstName && m_lastName == p.m_lastName);
};

void Participant::setFirstName(QString firstName)
{
    if (firstName != m_firstName) {
        emit firstNameChanged(m_firstName = firstName);
    }
}

void Participant::setLastName(QString lastName)
{
    if (lastName != m_lastName) {
        emit lastNameChanged( m_lastName = lastName);
    }
}

bool Participant::isSpeaking() const
{
    return m_isSpeaking;
}

void Participant::setIsSpeaking(bool isSpeaking)
{
    if (s_currentMeetingID != UNDEFINED_ID) {
        static QDateTime startDateTime;
        if ((m_isSpeaking = isSpeaking)) {
            startDateTime = QDateTime::currentDateTime();
        } else {
            takePartInCurrentMeeting();
            m_records[s_currentMeetingID].push_back(Record {startDateTime, QDateTime::currentDateTime()});
        }
        emit isSpeakingChanged(m_isSpeaking);
    }
}
