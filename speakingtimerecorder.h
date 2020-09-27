#ifndef SPEAKINGTIMERECORDER_H
#define SPEAKINGTIMERECORDER_H

#include "speakingtimebase.h"

class SpeakingTimeRecorder: public SpeakingTimeBase
{
    Q_OBJECT

public:
    SpeakingTimeRecorder(QObject *parent =  nullptr);
    ~SpeakingTimeRecorder();

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
    ID m_currentMeetingID;
    ID m_currentSpeakerID;
};

#endif // SPEAKINGTIMERECORDER_H
