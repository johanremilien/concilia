#ifndef MEETING_H
#define MEETING_H

#include <QHash>
#include <QDateTime>

#include "register.h"
#include "registrableitem.h"

class Meeting : public RegistrableItem<Meeting>
{
public:
    explicit Meeting(ID id = UNDEFINED_ID);
    ~Meeting();

    QDateTime getStartDate() const;
    QDateTime getEndDate() const;
    QString getName() const;
    QString setName(QString name);
    bool isStarted() const;
    bool isSuspended() const;
    bool isEnded() const;
    bool start();
    bool togglePause();
    bool end();
    void addParticipant(ID id);
    bool removeParticipant(ID id);
    Duration getDuration() const;
    virtual inline bool operator==(const Meeting &meeting) override;

    friend class Register<Meeting>;

private:
    QString m_name;
    IDs m_participants;
    bool m_isStarted;
    bool m_isSuspended;
    bool m_isEnded;
    QDateTime m_startDate;
    QDateTime m_endDate;
    Duration m_duration;
    Records m_pauses;
};

#endif // MEETING_H
