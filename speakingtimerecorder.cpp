#include "speakingtimerecorder.h"
#include "meetingsregister.h"
#include "meeting.h"
#include "participantsregister.h"
#include "participant.h"

//TODO: Create null object Meeting

SpeakingTimeRecorder::SpeakingTimeRecorder(Meeting &meeting, QObject *parent) :
    QObject(parent),
    m_meeting(meeting),
    m_isStarted(false),
    m_isSuspended(false),
    m_isStopped(false),
    m_pauses(),
    m_speakerID(UNDEFINED_ID)
{

}

SpeakingTimeRecorder::~SpeakingTimeRecorder()
{

}

const Participant &SpeakingTimeRecorder::addParticipant(const QString& firstName, const QString &lastName)
{
    //ParticipantRegister::find if empty create
}

bool SpeakingTimeRecorder::removeParticipant(id id)
{
    bool result = false;
    if (!m_isStarted) {
        m_meeting.removeParticipant(id);
        result = true;
    }
    return result;
}

bool SpeakingTimeRecorder::continueMeeting(id meetingID)
{
    //    if (meetingID != m_meeting.getId()) {
    //        endMeeting();
    //        m_meeting = *MeetingsRegister::instance().get(meetingID);
    //        //updateParticipantList
    //        startMeeting();
    //    }
}

const Meeting &createNewMeeting(const QString &name)
{
    //return MeetingsRegister::instance().create(name);
}

bool SpeakingTimeRecorder::startMeeting()
{
    bool result = false;
    if (!m_isStarted) {
        Participant::setCurrentMeetingID(m_meeting.getId());
        m_meeting.setStartDate(QDate::currentDate());
        m_isStarted = true;
        result = true;
    }
    return result;
}

bool SpeakingTimeRecorder::pauseMeeting()
{
    bool result = false;
    if (m_isStarted && !m_isStopped && !m_isSuspended) {
        m_pauses.append(new Pause{QDateTime::currentDateTime(), QDateTime()});
        m_isSuspended = true;
        result = true;
    }
    return result;
}

bool SpeakingTimeRecorder::restartMeeting()
{
    bool result = false;
    if (m_isStarted && (m_isStopped || m_isSuspended)) {
        const_cast<Pause *>(m_pauses.last())->endTime = QDateTime::currentDateTime();
        m_isStopped = false;
        m_isSuspended = false;
        result = true;
    }
    return result;
}

bool SpeakingTimeRecorder::endMeeting()
{
    bool result = false;
    if (m_isStarted && !m_isStopped) {
        m_isStopped = true;
        result = true;
    }
    return result;
}

void SpeakingTimeRecorder::silence()
{
    participantSpeaking(UNDEFINED_ID);
}

void SpeakingTimeRecorder::toggleSpeakingState(id id)
{
    if (id != UNDEFINED_ID)
        m_meeting.getParticipant(id).toggleSpeakingState();
}

void SpeakingTimeRecorder::participantSpeaking(id id)
{
    if (id == m_speakerID)
        goto exit;

    toggleSpeakingState(m_speakerID);
    toggleSpeakingState(id);
    m_speakerID = id;

exit:
    return;
}
