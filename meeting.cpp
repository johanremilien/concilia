#include "meeting.h"

Meeting::Meeting(ID id) :
    RegistrableItem<Meeting>(id),
    m_name(QString()),
    m_participants(),
    m_isSuspended(false),
    m_startDate(),
    m_endDate(),
    m_duration(0)
{
    //access to database here;
    m_isStarted = !m_startDate.isNull();
    m_isEnded = !m_endDate.isNull();
}

Meeting::~Meeting()
{

}

void Meeting::addParticipant(ID id)
{
    if (!m_participants.contains(id)) {
        m_participants.append(id);
    }
}

bool Meeting::removeParticipant(ID id)
{
    return m_participants.removeOne(id);
}

QDateTime Meeting::getStartDate() const
{
    return m_startDate;
}

QDateTime Meeting::getEndDate() const
{
    return m_endDate;
}

QString Meeting::getName() const
{
    return m_name;
}

QString Meeting::setName(QString name)
{
    return (m_name = name);
}

bool Meeting::isStarted() const
{
    return m_isStarted;
}

bool Meeting::isSuspended() const
{
    return m_isSuspended;
}
bool Meeting::isEnded() const
{
    return m_isEnded;
}

Duration Meeting::getDuration() const
{
    return m_duration;
}

bool Meeting::operator==(const Meeting & meeting)
{
    return (m_name == meeting.m_name);
}

bool Meeting::start()
{
    if (!m_isStarted) {
        m_startDate = QDateTime::currentDateTime();
        m_isStarted = true;
    }
    return m_isStarted;
}

bool Meeting::togglePause()
{
    static QDateTime startDateTime;
    if (m_isSuspended) {
        m_pauses.push_back(Record {startDateTime, QDateTime::currentDateTime()});
    } else {
        startDateTime = QDateTime::currentDateTime();
    }
    return (m_isSuspended ^= true);
}

bool Meeting::end()
{
    if (!m_isEnded) {
        m_endDate = QDateTime::currentDateTime();
        m_isEnded = true;
    }
    return m_isEnded;
}
