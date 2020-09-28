#include "speakingtimeregister.h"
#include "meetingsregister.h"
#include "meeting.h"
#include "participantsregister.h"
#include "participant.h"

SpeakingTimeRegister::SpeakingTimeRegister(QObject *parent) :
    SpeakingTimeBase(parent),
    m_currentMeetingId(UNDEFINED_ID)
{
    initRegisters();
}

ID SpeakingTimeRegister::addParticipant(QString  firstName, QString lastName)
{
    ID id = participantsRegister().find(firstName, lastName);
    if (id == UNDEFINED_ID) {
        id = participantsRegister().create(firstName,lastName).id();
    }
    meetingsRegister().addParticipant(m_currentMeetingId, id);
    return id;
}

ID SpeakingTimeRegister::renameParticipant(ID id, QString firstName, QString lastName)
{
    return participantsRegister().rename(id, firstName, lastName).id();
}

bool SpeakingTimeRegister::removeParticipant(ID id)
{
    bool result = false;
    try {
        result = meetingsRegister().removeParticipant(m_currentMeetingId, id);
    } catch (...) {

    }
    return result;
}

QVariant SpeakingTimeRegister::participantsList()
{
    QVariant participantList;
    try {
        participantList = QVariant::fromValue(meetingsRegister().particpantsList(m_currentMeetingId));
    } catch(...) {

    }
    return participantList;
}

ID SpeakingTimeRegister::createNewMeeting(QString name)
{
    return (m_currentMeetingId = meetingsRegister().create(name)->id());
}

QString SpeakingTimeRegister::renameMeeting(ID meetingID, QString name)
{
    return meetingsRegister().rename(meetingID, name).name();
}
