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

ID SpeakingTimeRecorder::addParticipant(QString  firstName, QString lastName)
{
    ID id = participantsRegister()->find(firstName, lastName);
    if (id == UNDEFINED_ID) {
        id = participantsRegister()->create(firstName,lastName).getId();
    }
    meetingsRegister()->addParticipant(m_currentMeetingId, id);
    return id;
}

ID SpeakingTimeRecorder::renameParticipant(ID id, QString firstName, QString lastName)
{
    return participantsRegister()->rename(id, firstName, lastName).getId();
}

bool SpeakingTimeRecorder::removeParticipant(ID id)
{
    bool result = false;
    try {
        result = meetingsRegister()->removeParticipant(m_currentMeetingId, id);
    } catch (...) {

    }
    return result;
}

ID SpeakingTimeRecorder::createNewMeeting(QString name)
{
    return (m_currentMeetingId = meetingsRegister()->create(name)->getId());
}

QString SpeakingTimeRecorder::renameMeeting(ID meetingID, QString name)
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
    bool result = false;
    try {
        result = meetingsRegister()->end(m_currentMeetingId);
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
