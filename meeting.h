#ifndef MEETING_H
#define MEETING_H

#include "register.h"
#include "registrableitem.h"

class Meeting : public RegistrableItem
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit Meeting(ID id = UNDEFINED_ID, QObject *parent = nullptr);
    Meeting(const Meeting &m);
    ~Meeting() = default;

    QDateTime startDate() const;
    QDateTime endDate() const;
    QString name() const;
    void setName(QString name);
    bool isStarted() const;
    bool isSuspended() const;
    bool isEnded() const;
    bool start();
    bool togglePause();
    bool end();
    void addParticipant(ID id);
    bool removeParticipant(ID id);
    IDs participants();
    Duration duration() const;
    Meeting &operator=(const Meeting &m);
    bool operator==(const Meeting &m);

    friend class Register<Meeting>;

signals:
    void nameChanged(QString name);

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
