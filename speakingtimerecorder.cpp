#include "speakingtimerecorder.h"
#include "meetingsregister.h"
#include "meeting.h"
#include "participantsregister.h"
#include "participant.h"

SpeakingTimeRecorder::SpeakingTimeRecorder(QObject *parent) :
    SpeakingTimeBase(parent),
    m_currentMeetingID(UNDEFINED_ID),
    m_currentSpeakerID(UNDEFINED_ID)
{
}

SpeakingTimeRecorder::~SpeakingTimeRecorder()
{
    silence();
    endMeeting();
}

bool SpeakingTimeRecorder::startMeeting()
{
    return meetingsRegister()->start(m_currentMeetingID);
}

bool SpeakingTimeRecorder::pauseMeeting()
{
    return meetingsRegister()->pause(m_currentMeetingID);
}

bool SpeakingTimeRecorder::restartMeeting()
{
    return meetingsRegister()->restart(m_currentMeetingID);
}

bool SpeakingTimeRecorder::endMeeting()
{
    bool result = false;
    try {
        result = meetingsRegister()->end(m_currentMeetingID);
    } catch (...) {

    }
    return result;
}

void SpeakingTimeRecorder::silence()
{
    participantSpeaking(UNDEFINED_ID);
}

void SpeakingTimeRecorder::toggleSpeakingState(ID id)
{
    if (id != UNDEFINED_ID) {
        participantsRegister()->toggleSpeakingState(id);
    }
}

void SpeakingTimeRecorder::participantSpeaking(ID id)
{
    if (id != m_currentSpeakerID) {
        toggleSpeakingState(m_currentSpeakerID);
        toggleSpeakingState(id);
        m_currentSpeakerID = id;
    }
}
