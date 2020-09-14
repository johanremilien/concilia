#include "speakingtimerecorder.h"
#include "meetingsregister.h"
#include "meeting.h"
#include "participantsregister.h"
#include "participant.h"

SpeakingTimeRecorder::SpeakingTimeRecorder(QObject *parent) :
    QObject(parent),
    m_participantsRegister(new ParticipantsRegister()),
    m_meetingsRegister(new MeetingsRegister()),
    m_currentMeetingId(UNDEFINED_ID),
    m_currentSpeakerID(UNDEFINED_ID)
{

}

SpeakingTimeRecorder::~SpeakingTimeRecorder()
{
    silence();
    endMeeting();
}

ID SpeakingTimeRecorder::addParticipant(const QString& firstName, const QString &lastName)
{
    ID id = m_participantsRegister.get()->find(firstName, lastName);
    if (id == UNDEFINED_ID)
        id = m_participantsRegister.get()->create(firstName,lastName).getId();
    m_meetingsRegister.get()->addParticipant(m_currentMeetingId, id);
    return id;
}

bool SpeakingTimeRecorder::removeParticipant(ID id)
{
    return m_meetingsRegister.get()->removeParticipant(m_currentMeetingId, id);
}

ID SpeakingTimeRecorder::createNewMeeting(const QString &name)
{
    return (m_currentMeetingId = m_meetingsRegister.get()->create(name).getId());
}

bool SpeakingTimeRecorder::startMeeting()
{
    return m_meetingsRegister.get()->start(m_currentMeetingId);
}

bool SpeakingTimeRecorder::pauseMeeting()
{
    return m_meetingsRegister.get()->pause(m_currentMeetingId);
}

bool SpeakingTimeRecorder::restartMeeting()
{
    return m_meetingsRegister.get()->restart(m_currentMeetingId);
}

bool SpeakingTimeRecorder::endMeeting()
{
    return m_meetingsRegister.get()->end(m_currentMeetingId);
}

void SpeakingTimeRecorder::silence()
{
    participantSpeaking(UNDEFINED_ID);
}

void SpeakingTimeRecorder::toggleSpeakingState(ID id)
{
    m_participantsRegister.get()->toggleSpeakingState(id);
}

void SpeakingTimeRecorder::participantSpeaking(ID id)
{
    if (id != m_currentSpeakerID) {
        toggleSpeakingState(m_currentSpeakerID);
        toggleSpeakingState(id);
        m_currentSpeakerID = id;
    }
}
