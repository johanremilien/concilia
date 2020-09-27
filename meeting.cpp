#include "meeting.h"

Meeting::Meeting(ID id, QObject *parent) :
    RegistrableItem(id, parent),
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

Meeting::Meeting(const Meeting &m) :
    RegistrableItem(m.id(), m.parent()),
    m_name(m.m_name),
    m_participants(m.m_participants),
    m_isStarted(m.m_isStarted),
    m_isSuspended(m.m_isSuspended),
    m_isEnded(m.m_isEnded),
    m_startDate(m.m_startDate),
    m_endDate(m.m_endDate),
    m_duration(m.m_duration)
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

IDs Meeting::participants()
{
    return m_participants;
}

QDateTime Meeting::startDate() const
{
    return m_startDate;
}

QDateTime Meeting::endDate() const
{
    return m_endDate;
}

QString Meeting::name() const
{
    return m_name;
}

void Meeting::setName(QString name)
{
    if (name != m_name) {
        emit nameChanged(m_name = name);
    }
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

Duration Meeting::duration() const
{
    return m_duration;
}

Meeting &Meeting::operator=(const Meeting &m)
{
    setId(m.id());
    setName(m.m_name);
    m_participants = m.m_participants;
    m_isStarted = m.m_isStarted;
    m_isSuspended = m.m_isSuspended;
    m_isEnded = m.m_isEnded;
    m_startDate = m.m_startDate;
    m_endDate = m.m_endDate;
    m_duration = m.m_duration;
    m_pauses = m.m_pauses;
    return *this;
}

bool Meeting::operator==(const Meeting &m)
{
    return (m_name == m.m_name);
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
