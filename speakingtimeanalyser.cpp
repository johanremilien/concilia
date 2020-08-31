#include "speakingtimeanalyser.h"

#include "meetingsregister.h"
#include "participantsregister.h"

SpeakingTimeAnalyser::SpeakingTimeAnalyser(QObject *parent) :
    QObject(parent)
{

}

RegisterVector<Meeting> SpeakingTimeAnalyser::getMeetings()
{
    //return MeetingsRegister::instance().getRegisterVector();
}

RegisterVector<Participant> SpeakingTimeAnalyser::getParticipants()
{
    //return ParticipantsRegister::instance().getRegisterVector();
}
