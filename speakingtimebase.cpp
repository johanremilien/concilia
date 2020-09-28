#include "speakingtimebase.h"
#include "participant.h"
#include "participantsregister.h"
#include "meeting.h"
#include "meetingsregister.h"

using namespace std;

SpeakingTimeBase::SpeakingTimeBase(QObject *parent) :
    QObject(parent)
{}

SpeakingTimeBase::~SpeakingTimeBase()
{
    m_participantsRegister.reset();
    m_meetingsRegister.reset();
}

void SpeakingTimeBase::initRegisters()
{
    static bool trigger = false;
    if (!trigger) {
        m_participantsRegister = make_unique<ParticipantsRegister>();
        m_meetingsRegister = make_unique<MeetingsRegister>();
        trigger ^= true;
    }
}

void SpeakingTimeBase::moveRegisters(std::unique_ptr<ParticipantsRegister> participantsRegister,
                                     std::unique_ptr<MeetingsRegister> meetingsRegister)
{
    m_participantsRegister = move(participantsRegister);
    m_meetingsRegister = move(meetingsRegister);
}

ParticipantsRegister &SpeakingTimeBase::participantsRegister()
{
    return getRegister<ParticipantsRegister>(m_participantsRegister);
}

MeetingsRegister &SpeakingTimeBase::meetingsRegister()
{
    return getRegister<MeetingsRegister>(m_meetingsRegister);
}
