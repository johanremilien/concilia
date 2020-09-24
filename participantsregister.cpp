#include "participantsregister.h"
#include "participant.h"

const Participant &ParticipantsRegister::create(QString firstName, QString lastName)
{
    return rename(create()->getId(), firstName, lastName);
}

QString ParticipantsRegister::getFirstName(ID id) const
{
    return value(id).getFirstName();
}

QString ParticipantsRegister::getLastName(ID id) const
{
    return value(id).getLastName();
}

ID ParticipantsRegister::find(QString firstName, QString lastName) const noexcept
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

IDs ParticipantsRegister::findByFirstName(QString firstName) const noexcept
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

IDs ParticipantsRegister::findByLastName(QString lastName) const noexcept
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

IDs ParticipantsRegister::findIncompleteNames(QString firstName, QString lastName) const noexcept
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

QString ParticipantsRegister::setFirstName(ID id, QString firstName)
{
    return operator[](id).setFirstName(firstName);
}

QString ParticipantsRegister::setLastName(ID id, QString lastName)
{
    return operator[](id).setLastName(lastName);
}

const Participant &ParticipantsRegister::rename(ID id, QString firstName, QString lastName) noexcept
{
    Participant *participant = nullptr;
    ID foundID = find(firstName, lastName);
    if (foundID == UNDEFINED_ID) {
        participant = &operator[](id);
        (void) participant->setFirstName(firstName);
        (void) participant->setLastName(lastName);
    } else {
        participant = &operator[](foundID);
    }
    return *participant;
}

bool ParticipantsRegister::toggleSpeakingState(ID id)
{
    Participant &participant = operator[](id);
    return participant.setIsSpeaking(!participant.getIsSpeaking());
}

Duration ParticipantsRegister::getTotalSpeakingTime(ID participantID, ID meetingID) const
{
    return value(participantID).getTotalSpeakingTime(meetingID);
}
