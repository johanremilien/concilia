#include "meetingsregister.h"
#include "meeting.h"
#include "participant.h"

const Meeting *MeetingsRegister::create(QString name)
{
    const Meeting *result;
    if (find(name) == UNDEFINED_ID) {
        result = &create();
        qDebug() << result->id();
        rename(result->id(), name);
    } else {
        QLatin1Char separartor('_');
        bool isInteger;
        QStringList splitName = name.split(separartor);
        int index = splitName.last().toInt(&isInteger, 10);
        if (isInteger) {
            splitName.removeLast();
        }
        QString newName = splitName.join(separartor).append(separartor + QString(index+1));
        result = create(newName);
    }
    return result;
}

QString MeetingsRegister::name(ID id) const
{
    return value(id).name();
}

void MeetingsRegister::setName(ID id, QString name)
{
    operator[](id).setName(name);
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
    if (meeting.startDate().isNull()) {
        result = meeting.start();
        Participant::setCurrentMeetingID(id);
    }
    return result;
}

bool MeetingsRegister::pause(ID id)
{
    bool result = false;
    Meeting &meeting = operator[](id);
    if (!meeting.isSuspended()) {
        result = meeting.togglePause();
    }
    return result;
}

bool MeetingsRegister::restart(ID id)
{
    bool result = false;
    Meeting &meeting = operator[](id);
    if (meeting.isSuspended()) {
        result = meeting.togglePause();
    }
    return result;
}

bool MeetingsRegister::end(ID id)
{
    bool result = false;
    Meeting &meeting = operator[](id);
    if (meeting.endDate().isNull()) {
        result = meeting.end();
    }
    return result;
}

void MeetingsRegister::addParticipant(ID meetingId, ID particpantId)
{
    operator[](meetingId).addParticipant(particpantId);
}

void MeetingsRegister::addParticipant(ID meetingId, const Participant &participant)
{
    addParticipant(meetingId, participant.id());
}

bool MeetingsRegister::removeParticipant(ID meetingId, ID participantId)
{
    return operator[](meetingId).removeParticipant(participantId);
}

bool MeetingsRegister::removeParticipant(ID meetingId, const Participant &participant)
{
    return removeParticipant(meetingId, participant.id());
}

Duration MeetingsRegister::duration(ID id) const
{
    return value(id).duration();
}

ID MeetingsRegister::find(QString name) const
{
    ID result = UNDEFINED_ID;
    process([&name, &result](const Meeting &meeting)
    {
        bool exitLoop = false;
        if (meeting.name() == name) {
            result = meeting.id();
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
        if (meeting.name().contains(name)) {
            result.append(meeting.id());
        }
        return exitLoop;
    });
    return result;
}

IDs MeetingsRegister::particpantsList(ID meetingId)
{
    return operator[](meetingId).participants();
}
