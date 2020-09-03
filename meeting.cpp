#include "meeting.h"
#include "participant.h"
#include "meetingsregister.h"

Meeting::Meeting(id id) :
    RegistrableItem<Meeting>(id),
    m_name(QString()),
    m_participants(),
    m_startDate(),
    m_endDate(),
    m_duration(0)
{
}

Meeting::~Meeting()
{

}

void Meeting::addParticipant(id id)
{
    if (!m_participants.contains(id))
        m_participants.append(id);
}

bool Meeting::removeParticipant(id id)
{
    return m_participants.removeOne(id);
}

const QDate &Meeting::getStartDate() const
{
    return m_startDate;
}

const QDate &Meeting::getEndDate() const
{
    return m_endDate;
}

const QString &Meeting::getName() const
{
    return m_name;
}

const QString &Meeting::setName(const QString &name)
{
    return (m_name = name);
}

duration Meeting::getDuration() const
{
    return m_duration;
}

bool Meeting::operator==(const Meeting & meeting)
{
    return (m_name == meeting.m_name);
}

void Meeting::setStartDate(const QDate &date)
{
    m_startDate = date;
}

void Meeting::setEndDate(const QDate &date)
{
    m_endDate = date;
}
