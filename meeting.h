#ifndef MEETING_H
#define MEETING_H

#include <QHash>
#include <QDate>

#include "typedef.h"
#include "meetingsregister.h"

class Participant;

class Meeting
{
public:
    id getId() const;
    const Participant &addParticipant(Participant &participant);
    bool removeParticipant(id id);
    const QDate &getStartDate() const;
    const QDate &getEndDate() const;
    const QString &getName() const;
    duration getDuration() const;

    friend const Meeting &MeetingsRegister::create(const QString &);

protected:
    Meeting(id id = UNDEFINED_ID);
    Meeting(const QString &name = QString(), id id = UNDEFINED_ID);
    ~Meeting();
    id setId(id id);
    const QString &setName(const QString &name);

private:
    id m_id;
    QString m_name;
    RegisterHash<Participant> m_participants;
    QDate m_startDate;
    QDate m_endDate;
    duration m_duration;
};

#endif // MEETING_H
