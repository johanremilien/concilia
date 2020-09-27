#ifndef SPEAKINGTIMEBASE_H
#define SPEAKINGTIMEBASE_H

#include <QObject>
#include <memory>

#include "typedef.h"

class SpeakingTimeBase : public QObject
{
    Q_OBJECT

protected:
    SpeakingTimeBase(QObject *parent = nullptr);
    virtual ~SpeakingTimeBase();
    void initRegisters();
    void moveRegisters(std::unique_ptr<ParticipantsRegister>, std::unique_ptr<MeetingsRegister>);
    ParticipantsRegister *participantsRegister();
    MeetingsRegister *meetingsRegister();

private:
    std::unique_ptr<ParticipantsRegister> m_participantsRegister;
    std::unique_ptr<MeetingsRegister> m_meetingsRegister;
};

#endif // SPEAKINGTIMEBASE_H
