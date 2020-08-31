#ifndef MEETING_H
#define MEETING_H

#include <QHash>
#include <QDate>

#include "typedef.h"

class SpeakingTimeRecorder;
class MeetingsRegister;
class Participant;

class Meeting
{
public:
    id getId() const;
    const Participant &addParticipant(Participant &participant);
    bool removeParticipant(id id);
    Participant &getParticipant(id id);
    const QDate &getStartDate() const;
    const QDate &getEndDate() const;
    const QString &getName() const;
    duration getDuration() const;

    friend class MeetingsRegister;
    friend class SpeakingTimeRecorder;

protected:
    explicit Meeting(id id = UNDEFINED_ID);
    Meeting(const QString &name, id id = UNDEFINED_ID);
    ~Meeting();
    id setId(id id);
    const QString &setName(const QString &name);
    void setStartDate(const QDate &date);
    void setEndDate(const QDate &date);

private:
    id m_id;
    QString m_name;
    ParticipantHash m_participants; //QVector<id> should be enough
    QDate m_startDate;
    QDate m_endDate;
    duration m_duration;
};

#endif // MEETING_H
