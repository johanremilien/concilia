#ifndef SPEAKINGTIMERECORDER_H
#define SPEAKINGTIMERECORDER_H

#include <QObject>

#include "meeting.h"

class SpeakingTimeRecorder: public QObject
{
    Q_OBJECT
public:
    SpeakingTimeRecorder();
    ~SpeakingTimeRecorder();

    void addParticipant(Participant * participant = nullptr);
    bool removeParticipant(id id);

    void setCurrentMeeting(id id);

    bool startMeeting();
    id getCurrentMeetingId() const;
    bool pauseMeeting();
    bool restartMeeting();
    bool endMeeting();

    void silence();
    void participantSpeaking(id id);

private:
    id m_currentMettingId;
};

#endif // SPEAKINGTIMERECORDER_H
