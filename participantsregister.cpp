#include "participantsregister.h"
#include "participant.h"

const Participant &ParticipantsRegister::create(QString firstName, QString lastName)
{
    return rename(create().id(), firstName, lastName);
}

QString ParticipantsRegister::firstName(ID id) const
{
    return value(id).firstName();
}

QString ParticipantsRegister::lastName(ID id) const
{
    return value(id).lastName();
}

ID ParticipantsRegister::find(QString firstName, QString lastName) const noexcept
{
    ID result = UNDEFINED_ID;
    process([&firstName, &lastName, &result](const Participant & participant)
    {
        bool exitLoop = false;
        if (participant.firstName() == firstName && participant.lastName() == lastName) {
            result = participant.id();
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
        if (participant.firstName() == firstName) {
            result.append(participant.id());
        }
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
        if (participant.lastName() == lastName) {
            result.append(participant.id());
        }
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
        if (participant.lastName().contains(firstName) &&
                participant.lastName().contains(lastName)) {
            result.append(participant.id());
        }
        return exitLoop;
    });
    return result;
}

void ParticipantsRegister::setFirstName(ID id, QString firstName)
{
    operator[](id).setFirstName(firstName);
}

void ParticipantsRegister::setLastName(ID id, QString lastName)
{
    operator[](id).setLastName(lastName);
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

void ParticipantsRegister::toggleSpeakingState(ID id)
{
    Participant &participant = operator[](id);
    participant.setIsSpeaking(!participant.isSpeaking());
}

Duration ParticipantsRegister::totalSpeakingTime(ID participantID, ID meetingID) const
{
    return value(participantID).totalSpeakingTime(meetingID);
}
