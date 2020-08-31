#ifndef SPEAKINGTIMERECORDER_H
#define SPEAKINGTIMERECORDER_H

#include <QObject>

#include "typedef.h"

class Meeting;
class Participant;

class SpeakingTimeRecorder: public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool isStarted MEMBER m_isStarted NOTIFY isStartedChanged)
    Q_PROPERTY(bool isSuspended MEMBER m_isSuspended NOTIFY isPauseChanged)
    Q_PROPERTY(bool isStopped MEMBER m_isStopped NOTIFY isStoppedChanged)
public:
    //SpeakingTimeRecorder(QObject *parent = nullptr);
    SpeakingTimeRecorder(Meeting &meeting, QObject *parent =  nullptr);
    ~SpeakingTimeRecorder();

    bool continueMeeting(id meetingID);
    void createNewMeeting(const QString name = QString());;
    const Participant &addParticipant(const QString& firstName, const QString &lastName);
    bool removeParticipant(id id);

    id getCurrentMeetingId() const;

    Q_INVOKABLE bool startMeeting();
    Q_INVOKABLE bool pauseMeeting();
    Q_INVOKABLE bool restartMeeting();
    Q_INVOKABLE bool endMeeting();
    Q_INVOKABLE void silence();
    Q_INVOKABLE void participantSpeaking(id id);

signals:
    void isStartedChanged(bool isStarted);
    void isPauseChanged(bool isSuspended);
    void isStoppedChanged(bool isStopped);

protected:
    void toggleSpeakingState(id id);

private:
    Meeting &m_meeting;
    bool m_isStarted;
    bool m_isSuspended;
    bool m_isStopped;
    Pauses m_pauses;
    id m_speakerID;
};

#endif // SPEAKINGTIMERECORDER_H
