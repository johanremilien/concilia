#include "participantsregister.h"
#include "participant.h"

const Participant &ParticipantsRegister::create(const QString &firstName, const QString &lastName)
{
    return rename(create().getId(), firstName, lastName);
}

const QString &ParticipantsRegister::getFirstName(ID id) const
{
    Participant *participant = get(id);
    if (participant == nullptr)
        exception(id);
    return participant->getFirstName();
}

const QString &ParticipantsRegister::getLastName(ID id) const
{
    Participant *participant = get(id);
    if (participant == nullptr)
        exception(id);
    return participant->getLastName();
}

ID ParticipantsRegister::find(const QString &firstName, const QString &lastName) const
{
    ID result = UNDEFINED_ID;
    process([&firstName, &lastName, &result](const Participant & participant)
    {
        bool exitLoop = false;
        if (participant.getFirstName() == firstName && participant.getLastName() == lastName) {
            result = participant.getId();
            exitLoop = true;
        }
        return exitLoop;
    });
    return  result;
}

IDs ParticipantsRegister::findByFirstName(const QString &firstName) const
{
    IDs result;
    process([&firstName, &result](const Participant &participant)
    {
        bool exitLoop = false;
        if (participant.getFirstName() == firstName)
            result.append(participant.getId());
        return exitLoop;
    });
    return result;
}

IDs ParticipantsRegister::findByLastName(const QString &lastName) const
{
    IDs result;
    process([&lastName, &result](const Participant &participant)
    {
        bool exitLoop = false;
        if (participant.getLastName() == lastName)
            result.append(participant.getId());
        return exitLoop;
    });
    return result;
}

IDs ParticipantsRegister::findIncompleteNames(const QString &firstName, const QString &lastName) const
{
    IDs result;
    process([&firstName, &lastName, &result](const Participant &participant)
    {
        bool exitLoop = false;
        if (participant.getLastName().contains(firstName) &&
                participant.getLastName().contains(lastName)) {
            result.append(participant.getId());
        }
        return exitLoop;
    });
    return result;
}

const QString &ParticipantsRegister::setFirstName(ID id, const QString &firstName)
{
    Participant *participant = get(id);
    if (participant == nullptr)
        exception(id);
    return participant->setFirstName(firstName);;
}

const QString &ParticipantsRegister::setLastName(ID id, const QString &lastName)
{
    Participant *participant = get(id);
    if (participant == nullptr)
        exception(id);
    return participant->setLastName(lastName);
}

const Participant &ParticipantsRegister::rename(ID id, const QString &firstName, const QString &lastName)
{
    Participant *participant = get(id);
    if (participant == nullptr)
        exception(id);
    (void) participant->setFirstName(firstName);
    (void) participant->setLastName(lastName);
    return *participant;
}

bool ParticipantsRegister::toggleSpeakingState(ID id)
{
    Participant *participant = get(id);
    if (participant == nullptr)
        exception(id);
    return (participant->getIsSpeaking() ? participant->setIsSpeaking(false)
                                         : participant->setIsSpeaking(true));
}

Duration ParticipantsRegister::getTotalSpeakingTime(ID participantID, ID meetingID) const
{
    Participant *participant = get(participantID);
    if (participant == nullptr)
        exception(participantID);
    return participant->getTotalSpeakingTime(meetingID);
}
