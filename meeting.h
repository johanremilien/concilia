#ifndef MEETING_H
#define MEETING_H

#include <QHash>
#include <QDate>

#include "register.h"
#include "registrableitem.h"

class Meeting : public RegistrableItem<Meeting>
{
public:
    const QDate &getStartDate() const;
    const QDate &getEndDate() const;
    const QString &getName() const;
    const QString &setName(const QString &name);
    void setStartDate(const QDate &date);
    void setEndDate(const QDate &date);
    void addParticipant(id id);
    bool removeParticipant(id id);
    duration getDuration() const;
    virtual inline bool operator==(const Meeting &) override;

    friend class Register<Meeting>;

protected:
    explicit Meeting(id id);
    ~Meeting();

private:
    QString m_name;
    IDs m_participants;
    QDate m_startDate;
    QDate m_endDate;
    duration m_duration;
};

#endif // MEETING_H
