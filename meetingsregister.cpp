#include "meetingsregister.h"
#include "meeting.h"
#include "participant.h"

const Meeting *MeetingsRegister::create(QString name)
{
    const Meeting *result;
    if (find(name) == UNDEFINED_ID) {
        result = create();
        rename(result->getId(), name);
    } else {
        QLatin1Char separartor('_');
        bool isInteger;
        QStringList splitName = name.split(separartor);
        int index = splitName.last().toInt(&isInteger, 10);
        if (isInteger)
            splitName.removeLast();
        QString newName = splitName.join(separartor).append(separartor + QString(index+1));
        result = create(newName);
    }
    return result;
}

QString MeetingsRegister::getName(ID id) const
{
    return value(id).getName();
}

QString MeetingsRegister::setName(ID id, QString name)
{
    return operator[](id).setName(name);
}

const Meeting &MeetingsRegister::rename(ID id, QString name)
{
    Meeting &meeting = operator[](id);
    (void) meeting.setName(name);
    return meeting;
}

bool MeetingsRegister::start(ID id)
{
    bool result = false;
    Meeting &meeting = operator[](id);
    if (meeting.getStartDate().isNull()) {
        result = meeting.start();
        Participant::setCurrentMeetingID(id);
    }
    return result;
}

bool MeetingsRegister::pause(ID id)
{
    bool result = false;
    Meeting &meeting = operator[](id);
    if (!meeting.isSuspended())
        result = meeting.togglePause();
    return result;
}

bool MeetingsRegister::restart(ID id)
{
    bool result = false;
    Meeting &meeting = operator[](id);
    if (meeting.isSuspended())
        result = meeting.togglePause();
    return result;
}

bool MeetingsRegister::end(ID id)
{
    bool result = false;
    Meeting &meeting = operator[](id);
    if (meeting.getEndDate().isNull())
        result = meeting.end();
    return result;
}

void MeetingsRegister::addParticipant(ID meetingId, ID particpantId)
{
    operator[](meetingId).addParticipant(particpantId);
}

void MeetingsRegister::addParticipant(ID meetingId, const Participant &participant)
{
    addParticipant(meetingId, participant.getId());
}

bool MeetingsRegister::removeParticipant(ID meetingId, ID participantId)
{
    return operator[](meetingId).removeParticipant(participantId);
}

bool MeetingsRegister::removeParticipant(ID meetingId, const Participant &participant)
{
    return removeParticipant(meetingId, participant.getId());
}

Duration MeetingsRegister::getDuration(ID id) const
{
    return value(id).getDuration();
}

ID MeetingsRegister::find(QString name) const
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

IDs MeetingsRegister::findIncompleteName(QString name) const
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
