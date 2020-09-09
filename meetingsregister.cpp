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

const QString &MeetingsRegister::getName(id id)
{
    const QString *result = &undefined_name;
    if (get(id))
        result = &(get(id)->getName());
    return *result;
}

const QString &MeetingsRegister::setName(id id, const QString &name)
{
    const QString *result = &undefined_name;
    if (get(id))
        result = &(get(id)->setName(name));
    return *result;
}

const Meeting &MeetingsRegister::rename(id id, const QString &name)
{
    Meeting *meeting = get(id);
    if (meeting)
        meeting->setName(name);
    return *meeting;
}

void MeetingsRegister::start(id id)
{
    Meeting *meeting = get(id);
    if (meeting)
        meeting->setStartDate(QDate::currentDate());
}

void MeetingsRegister::stop(id id)
{
    Meeting *meeting = get(id);
    if (meeting)
        meeting->setEndDate(QDate::currentDate());
}

void MeetingsRegister::addParticipant(id meetingId, id particpantId)
{
    Meeting *meeting = get(meetingId);
    if (meeting)
        meeting->addParticipant(particpantId);
}

void MeetingsRegister::addParticipant(id meetingId, const Participant &participant)
{
    addParticipant(meetingId, participant.getId());
}

bool MeetingsRegister::removeParticipant(id meetingId, id participantId)
{
    bool result = false;
    Meeting *meeting = get(meetingId);
    if (meeting)
        result = meeting->removeParticipant(participantId);
    return result;
}

bool MeetingsRegister::removeParticipant(id meetingId, const Participant &participant)
{
    return removeParticipant(meetingId, participant.getId());
}

duration MeetingsRegister::getDuration(id id) const
{
    duration result = 0;
    Meeting *meeting = get(id);
    if (meeting)
        result = meeting->getDuration();
    return result;
}

id MeetingsRegister::find(const QString &name) const
{
    id result = UNDEFINED_ID;
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
