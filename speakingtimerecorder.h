#ifndef SPEAKINGTIMERECORDER_H
#define SPEAKINGTIMERECORDER_H

#include "speakingtimebase.h"

class SpeakingTimeRecorder: public SpeakingTimeBase
{
    Q_OBJECT

public:
    SpeakingTimeRecorder(QObject *parent =  nullptr);
    ~SpeakingTimeRecorder();

    //may be useless
    ID getCurrentMeetingId() const;

    Q_INVOKABLE ID createNewMeeting(const QString &name = QString());
    Q_INVOKABLE ID addParticipant(const QString &firstName, const QString &lastName);
    Q_INVOKABLE bool removeParticipant(ID id);
    Q_INVOKABLE bool startMeeting();
    Q_INVOKABLE bool pauseMeeting();
    Q_INVOKABLE bool restartMeeting();
    Q_INVOKABLE bool endMeeting();
    Q_INVOKABLE void silence();
    Q_INVOKABLE void participantSpeaking(ID id);

signals:
    void isStartedChanged(bool isStarted);
    void isPauseChanged(bool isSuspended);
    void isStoppedChanged(bool isStopped);

protected:
    void toggleSpeakingState(ID id);

private:
    ID m_currentMeetingId;
    ID m_currentSpeakerID;
};

#endif // SPEAKINGTIMERECORDER_H
