#include "participant.h"

ID Participant::s_currentMeetingID = UNDEFINED_ID;

Participant::Participant(ID id) :
    RegistrableItem<Participant>(id),
    m_firstName(QString()),
    m_lastName(QString()),
    m_isSpeaking(false)
{

}

Participant::~Participant()
{

}

QString Participant::getFirstName() const
{
    return m_firstName;
}

QString Participant::getLastName() const
{
    return m_lastName;
}

void Participant::takePartInCurrentMeeting()
{
    if (s_currentMeetingID != UNDEFINED_ID) {
        if (!m_records.contains(s_currentMeetingID))
            m_records.insert(s_currentMeetingID, QVector<Record>());
    }
}

Duration Participant::getTotalSpeakingTime(ID meetingID) const
{
    Duration totalSpeakingTime = 0;
    if (meetingID == UNDEFINED_ID) {
        for (const auto & meetingID : m_records.keys())
            totalSpeakingTime += getTotalSpeakingTime(meetingID);
    } else if (m_records.contains(meetingID)) {
        for (const auto &record : m_records.value(meetingID))
            totalSpeakingTime += record.startTime.secsTo(record.endTime);
    }
    return totalSpeakingTime;
}

void Participant::setCurrentMeetingID(ID meetingID)
{
    s_currentMeetingID = meetingID;
}

bool Participant::operator==(const Participant & item)
{
    return (m_firstName == item.m_firstName && m_lastName == item.m_lastName);
};

QString Participant::setFirstName(QString firstName)
{
    return (m_firstName = firstName);
}

QString Participant::setLastName(QString lastName)
{
    return (m_lastName = lastName);
}

bool Participant::getIsSpeaking() const
{
    return m_isSpeaking;
}

bool Participant::setIsSpeaking(bool isSpeaking)
{
    if (s_currentMeetingID != UNDEFINED_ID) {
        static QDateTime startDateTime;
        if ((m_isSpeaking = isSpeaking)) {
            startDateTime = QDateTime::currentDateTime();
        } else {
            takePartInCurrentMeeting();
            m_records[s_currentMeetingID].push_back(Record {startDateTime, QDateTime::currentDateTime()});
        }
    }
    return m_isSpeaking;
}
