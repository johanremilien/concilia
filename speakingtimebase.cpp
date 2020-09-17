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

void SpeakingTimeBase::moveRegisters(std::unique_ptr<ParticipantsRegister> p, std::unique_ptr<MeetingsRegister> m)
{
    m_participantsRegister = move(p);
    m_meetingsRegister = move(m);
}

ParticipantsRegister *SpeakingTimeBase::participantsRegister()
{
    initRegisters();
    return m_participantsRegister.get();
}

MeetingsRegister *SpeakingTimeBase::meetingsRegister()
{
    initRegisters();
    return m_meetingsRegister.get();
}