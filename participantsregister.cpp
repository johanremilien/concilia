#include "participantsregister.h"
#include "participant.h"

const Participant &ParticipantsRegister::create(const QString &firstName, const QString &lastName)
{
    return rename(create().getId(), firstName, lastName);
}

const QString &ParticipantsRegister::getFirstName(id id) const
{
    const QString *result = &undefined_name;
    if (get(id))
        result = &(get(id)->getFirstName());
    else
        qWarning("Participant not found");
    return *result;
}

const QString &ParticipantsRegister::getLastName(id id) const
{
    const QString *result = &undefined_name;
    if (get(id))
        result = &(get(id)->getLastName());
    else
        qWarning("Participant not found");
    return *result;
}

id ParticipantsRegister::find(const QString &firstName, const QString &lastName) const
{
    id result = UNDEFINED_ID;
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

const QString &ParticipantsRegister::setFirstName(id id, const QString &firstName)
{
    const QString *result = &undefined_name;
    Participant *participant = get(id);
    if (participant)
        result = &(participant->setFirstName(firstName));
    else
        qWarning("Participant not found");
    return *result;
}

const QString &ParticipantsRegister::setLastName(id id, const QString &lastName)
{
    const QString *result = &undefined_name;
    Participant *participant = get(id);
    if (participant)
        result = &(participant->setLastName(lastName));
    else
        qWarning("Participant not found");
    return *result;
}

const Participant &ParticipantsRegister::rename(id id, const QString &firstName, const QString &lastName)
{
    Participant *participant = get(id);
    if (participant) {
        (void) participant->setFirstName(firstName);
        (void) participant->setLastName(lastName);
    } else {
        qWarning("Participant not found");
    }
    return *participant;
}

bool ParticipantsRegister::toggleSpeakingState(id id)
{
    bool result = false;
    Participant *participant = get(id);
    if (participant) {
        result = (participant->getIsSpeaking() ? participant->setIsSpeaking(false)
                                               : participant->setIsSpeaking(true));
    } else {
        qWarning("Participant not found");
    }
    return result;
}

duration ParticipantsRegister::getTotalSpeakingTime(id participantID, id meetingID) const
{
    duration result = 0;
    Participant *participant = get(participantID);
    if (participant) {
        result = participant->getTotalSpeakingTime(meetingID);
    } else {
        qWarning("Participant not found");
    }
    return result;
}
