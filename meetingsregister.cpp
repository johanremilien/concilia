#include "meetingsregister.h"
#include "meeting.h"
#include "participant.h"

const Meeting &MeetingsRegister::create(const QString &name)
{
    const Meeting *result;
    if (find(name) == UNDEFINED_ID) {
        result = &create();
        rename(result->getId(), name);
    } else {
        QLatin1Char separartor('_');
        bool isInteger;
        QStringList splitName = name.split(separartor);
        int index = splitName.last().toInt(&isInteger, 10);
        if (isInteger)
            splitName.removeLast();
        QString newName = splitName.join(separartor).append(separartor + QString(index+1));
        result = &create(newName);
    }
    return *result;
}

const QString &MeetingsRegister::getName(ID id)
{
    Meeting *meeting = get(id);
    if (meeting == nullptr)
        exception(id);
    return get(id)->getName();
}

const QString &MeetingsRegister::setName(ID id, const QString &name)
{
    Meeting *meeting = get(id);
    if (meeting == nullptr)
        exception(id);
    return meeting->setName(name);
}

const Meeting &MeetingsRegister::rename(ID id, const QString &name)
{
    Meeting *meeting = get(id);
    if (meeting == nullptr)
        exception(id);
    meeting->setName(name);
    return *meeting;
}

bool MeetingsRegister::start(ID id)
{
    bool result = false;
    Meeting *meeting = get(id);
    if (meeting)
        result = meeting->start();
    return result;
}

bool MeetingsRegister::pause(ID id)
{
    bool result = false;
    Meeting *meeting = get(id);
    if (meeting && !meeting->isSuspended())
        result = meeting->togglePause();
    return result;
}

bool MeetingsRegister::restart(ID id)
{
    bool result = false;
    Meeting *meeting = get(id);
    if (meeting && meeting->isSuspended())
        result = meeting->togglePause();
    return result;
}

bool MeetingsRegister::end(ID id)
{
    bool result = false;
    Meeting *meeting = get(id);
    if (meeting && meeting->getEndDate().isNull())
        result = meeting->end();
    return result;
}

void MeetingsRegister::addParticipant(ID meetingId, ID particpantId)
{
    Meeting *meeting = get(meetingId);
    if (meeting)
        meeting->addParticipant(particpantId);
}

void MeetingsRegister::addParticipant(ID meetingId, const Participant &participant)
{
    addParticipant(meetingId, participant.getId());
}

bool MeetingsRegister::removeParticipant(ID meetingId, ID participantId)
{
    bool result = false;
    Meeting *meeting = get(meetingId);
    if (meeting)
        result = meeting->removeParticipant(participantId);
    return result;
}

bool MeetingsRegister::removeParticipant(ID meetingId, const Participant &participant)
{
    return removeParticipant(meetingId, participant.getId());
}

Duration MeetingsRegister::getDuration(ID id) const
{
    Duration result = 0;
    Meeting *meeting = get(id);
    if (meeting)
        result = meeting->getDuration();
    return result;
}

ID MeetingsRegister::find(const QString &name) const
{
    ID result = UNDEFINED_ID;
    process([&name, &result](const Meeting &meeting)
    {
        bool exitLoop = false;
        if (meeting.getName() == name) {
            result = meeting.getId();
            exitLoop = true;
        }
        return exitLoop;
    });
    return result;
}

IDs MeetingsRegister::findIncompleteName(const QString &name) const
{
    IDs result;
    process([&name, &result](const Meeting &meeting)
    {
        bool exitLoop = false;
        if (meeting.getName().contains(name))
            result.append(meeting.getId());
        return exitLoop;
    });
    return result;
}
