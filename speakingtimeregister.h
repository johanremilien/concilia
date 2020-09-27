#ifndef SPEAKINGTIMEREGISTER_H
#define SPEAKINGTIMEREGISTER_H

#include "speakingtimebase.h"

class SpeakingTimeRegister : public SpeakingTimeBase
{
    Q_OBJECT

public:
    SpeakingTimeRegister(QObject *parent =  nullptr);
    ~SpeakingTimeRegister() = default;

    Q_INVOKABLE ID createNewMeeting(QString name = QString());
    Q_INVOKABLE QString renameMeeting(ID meetingID, QString name);
    Q_INVOKABLE ID addParticipant(QString firstName = QString(), QString lastName = QString());
    Q_INVOKABLE ID renameParticipant(ID id, QString firstName, QString lastName);
    Q_INVOKABLE bool removeParticipant(ID id);
    Q_INVOKABLE QVariant participantsList();

private:
    ID m_currentMeetingId;
};

#endif // SPEAKINGTIMEREGISTER_H
