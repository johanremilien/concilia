#include "participant.h"

id Participant::s_currentMeetingID = UNDEFINED_ID;

Participant::Participant(id id) : Participant(QString(), QString(), id)
{

}

Participant::Participant(const QString &firstName, const QString &lastName, id id) :
    RegistrableItem<Participant>(id),
    m_firstName(firstName),
    m_lastName(lastName),
    m_isSpeaking(false)
{

}

Participant::~Participant()
{

}

const QString &Participant::getFirstName() const
{
    return m_firstName;
}

const QString &Participant::getLastName() const
{
    return m_lastName;
}

void Participant::takePartInCurrentMeeting()
{
    if (s_currentMeetingID != UNDEFINED_ID) {
        if (!m_records.contains(s_currentMeetingID))
            m_records.insert(s_currentMeetingID, new QVector<const Record *>());
    }
}

void Participant::toggleSpeakingState()
{
    m_isSpeaking ? setIsSpeaking(false) : setIsSpeaking(true);
}

duration Participant::getTotalSpeakingTime(id meetingID) const
{
    duration totalSpeakingTime = 0;
    if (meetingID == UNDEFINED_ID) {
        for (const auto & meetingID : m_records.keys())
            totalSpeakingTime += getTotalSpeakingTime(meetingID);
    } else if (m_records.contains(meetingID)) {
        for (const auto &record : *m_records.value(meetingID))
            totalSpeakingTime += record->duration;
    }
    return totalSpeakingTime;
}

void Participant::setCurrentMeetingID(id meetingID)
{
    s_currentMeetingID = meetingID;
}

bool Participant::operator==(const Participant & item)
{
    return (m_firstName == item.m_firstName && m_lastName == item.m_lastName);
};

const QString &Participant::setFirstName(const QString &firstName)
{
    return (m_firstName = firstName);
}

const QString &Participant::setLastName(const QString &lastName)
{
    return (m_lastName = lastName);
}

const Participant &Participant::rename(const QString &firstName, const QString &lastName)
{
    (void) setFirstName(firstName);
    (void) setLastName(lastName);
    return *this;
}

void Participant::setIsSpeaking(bool isSpeaking)
{
    if (s_currentMeetingID != UNDEFINED_ID) {
        static QDateTime dateTime;
        if ((m_isSpeaking = isSpeaking)) {
            dateTime = QDateTime::currentDateTime();
        } else {
            takePartInCurrentMeeting();
            Record record;
            record.dateTime = dateTime;
            record.duration = dateTime.secsTo(QDateTime::currentDateTime());
            m_records[s_currentMeetingID]->push_back(&record);
        }
    }
}
