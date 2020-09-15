#include "speakingtimerecorder.h"
#include "meetingsregister.h"
#include "meeting.h"
#include "participantsregister.h"
#include "participant.h"

SpeakingTimeRecorder::SpeakingTimeRecorder(QObject *parent) :
    SpeakingTimeBase(parent),
    m_currentMeetingId(UNDEFINED_ID),
    m_currentSpeakerID(UNDEFINED_ID)
{
    initRegisters();
}

SpeakingTimeRecorder::~SpeakingTimeRecorder()
{
    silence();
    endMeeting();
}

ID SpeakingTimeRecorder::addParticipant(const QString& firstName, const QString &lastName)
{
    ID id = participantsRegister()->find(firstName, lastName);
    if (id == UNDEFINED_ID)
        id = participantsRegister()->create(firstName,lastName).getId();
    meetingsRegister()->addParticipant(m_currentMeetingId, id);
    return id;
}

ID SpeakingTimeRecorder::renameParticipant(ID id, const QString &firstName, const QString &lastName)
{
    return participantsRegister()->rename(id, firstName, lastName).getId();
}

bool SpeakingTimeRecorder::removeParticipant(ID id)
{
    return meetingsRegister()->removeParticipant(m_currentMeetingId, id);
}

ID SpeakingTimeRecorder::createNewMeeting(const QString &name)
{
    return (m_currentMeetingId = meetingsRegister()->create(name).getId());
}

const QString &SpeakingTimeRecorder::renameMeeting(ID meetingID, const QString &name)
{
    return meetingsRegister()->rename(meetingID, name).getName();
}

bool SpeakingTimeRecorder::startMeeting()
{
    return meetingsRegister()->start(m_currentMeetingId);
}

bool SpeakingTimeRecorder::pauseMeeting()
{
    return meetingsRegister()->pause(m_currentMeetingId);
}

bool SpeakingTimeRecorder::restartMeeting()
{
    return meetingsRegister()->restart(m_currentMeetingId);
}

bool SpeakingTimeRecorder::endMeeting()
{
    return meetingsRegister()->end(m_currentMeetingId);
}

void SpeakingTimeRecorder::silence()
{
    participantSpeaking(UNDEFINED_ID);
}

void SpeakingTimeRecorder::toggleSpeakingState(ID id)
{
    participantsRegister()->toggleSpeakingState(id);
}

void SpeakingTimeRecorder::participantSpeaking(ID id)
{
    if (id != m_currentSpeakerID) {
        toggleSpeakingState(m_currentSpeakerID);
        toggleSpeakingState(id);
        m_currentSpeakerID = id;
    }
}
