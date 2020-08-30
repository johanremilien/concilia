#include "meeting.h"
#include "participant.h"
#include "meetingsregister.h"

Meeting::Meeting(id id) : Meeting(QString(), id)
{
}

Meeting::Meeting(const QString &name, id id) :
    m_id(id),
    m_name(name),
    m_participants(),
    m_startDate(),
    m_endDate(),
    m_duration(0)
{
}

Meeting::~Meeting()
{

}

id Meeting::getId() const
{
    return m_id;
}

const Participant &Meeting::addParticipant(Participant &participant)
{
    return **(m_participants.insert(participant.getId(), &participant));
}

bool Meeting::removeParticipant(id id)
{
    bool result = false;
    if (m_startDate.isNull())
        result = !!m_participants.remove(id);
    return result;
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

duration Meeting::getDuration() const
{
    return m_duration;
}

id Meeting::setId(id id)
{
    return (m_id = id);
}

const QString &Meeting::setName(const QString &name)
{
    return (m_name = name);
}
