#include "participant.h"

Participant::Participant(id id) : Participant(QString(), QString(), id)
{

}

Participant::Participant(const QString &firstName, const QString &lastName, id id) :
    m_id(id),
    m_meetingID(-1),
    m_firstName(firstName),
    m_lastName(lastName),
    m_isSpeaking(false)
{

}

Participant::~Participant()
{

}

id Participant::getId() const
{
    return m_id;
}

const QString &Participant::getFirstName() const
{
    return m_firstName;
}

const QString &Participant::getLastName() const
{
    return m_lastName;
}

void Participant::takePartInMeeting(id meetingID)
{
//    if (!m_records.contains(meetingID)) {
//        m_records.insert(meetingID, new QVector<const Record &>());
//    }
}

void Participant::toggleSpeakingState()
{
    m_isSpeaking ? setIsSpeaking(false) : setIsSpeaking(true);
}

duration Participant::getTotalSpeakingTime() const
{
    duration totalSpeakingTime = 0;
//    if (m_records.contains(m_meetingID)) {
//        for (const auto &record : m_records[m_meetingID])
//            totalSpeakingTime += record.duration;
//    }
    return totalSpeakingTime;
}

id Participant::setId(id id)
{
    return  (m_id = id);
}

const QString &Participant::setFirstName(const QString &firstName)
{
    return (m_firstName = firstName);
}

const QString &Participant::setLastName(const QString &lastName)
{
    return (m_lastName = lastName);
}

void Participant::setIsSpeaking(bool isSpeaking)
{
    static QDateTime dateTime;
    if ((m_isSpeaking = isSpeaking)) {
        dateTime = QDateTime::currentDateTime();
    } else {
        takePartInMeeting(m_meetingID);
        Record record;
        record.dateTime = dateTime;
        record.duration = dateTime.secsTo(QDateTime::currentDateTime());
        //m_records[m_meetingID].push_back(record);
    }
}
