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
    static bool trigger = true;
    if (trigger) {
        m_participantsRegister = make_unique<ParticipantsRegister>();
        m_meetingsRegister = make_unique<MeetingsRegister>();
        trigger ^= true;
    }
}

void SpeakingTimeBase::moveRegistersTo(SpeakingTimeBase & stb)
{
    moveRegisters(*this, stb);
}

void SpeakingTimeBase::moveRegistersFrom(SpeakingTimeBase &stb)
{
    moveRegisters(stb, *this);
}

ParticipantsRegister &SpeakingTimeBase::participantsRegister()
{
    return getRegister<ParticipantsRegister>(m_participantsRegister);
}

MeetingsRegister &SpeakingTimeBase::meetingsRegister()
{
    return getRegister<MeetingsRegister>(m_meetingsRegister);
}

void SpeakingTimeBase::moveRegisters(SpeakingTimeBase &from, SpeakingTimeBase &to)
{
    if (from.m_participantsRegister == nullptr || from.m_meetingsRegister == nullptr)
        throw std::runtime_error("invalid attempt to move an unowned register");
    to.m_participantsRegister = move(from.m_participantsRegister);
    to.m_meetingsRegister = move(from.m_meetingsRegister);
}
