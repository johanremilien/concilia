#ifndef SPEAKINGTIMEBASE_H
#define SPEAKINGTIMEBASE_H

#include <QObject>
#include <memory>

#include "typedef.h"

class SpeakingTimeBase : public QObject
{
    Q_OBJECT

public:
    ParticipantsRegister &participantsRegister();
    MeetingsRegister &meetingsRegister();
    void moveRegistersTo(SpeakingTimeBase &stb);
    void moveRegistersFrom(SpeakingTimeBase &stb);

protected:
    SpeakingTimeBase(QObject *parent = nullptr);
    virtual ~SpeakingTimeBase();
    void initRegisters();

private:
    template<typename T>
    T &getRegister(std::unique_ptr<T> &tr);
    void moveRegisters(SpeakingTimeBase &from, SpeakingTimeBase &to);
    std::unique_ptr<ParticipantsRegister> m_participantsRegister;
    std::unique_ptr<MeetingsRegister> m_meetingsRegister;
};

template<typename T>
T &SpeakingTimeBase::getRegister(std::unique_ptr<T> &tr)
{
    initRegisters();
    T *templateRegister = tr.get();
    if (templateRegister == nullptr)
        throw std::runtime_error("invalid attempt to use an unowned register");
    return *templateRegister;
}

#endif // SPEAKINGTIMEBASE_H
