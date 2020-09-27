#ifndef MEETINGSREGISTER_H
#define MEETINGSREGISTER_H

#include "register.h"

class MeetingsRegister : public Register<Meeting>
{
public:
    const Meeting *create(QString name);
    QString name(ID id) const;
    inline void setName(ID id, QString name);
    const Meeting &rename(ID id, QString name);

    bool start(ID id);
    bool pause(ID id);
    bool restart(ID id);
    bool end(ID id);
    void addParticipant(ID meetingId, ID particpantId);
    inline void addParticipant(ID meetingId, const Participant &participant);
    bool removeParticipant(ID meetingId, ID participantId);
    inline bool removeParticipant(ID meetingId, const Participant &participant);
    Duration duration(ID id) const;

    ID find(QString name) const;
    IDs findIncompleteName(QString name) const;
    IDs particpantsList(ID meetingId);

protected:
    using Register<Meeting>::create;
};

#endif // MEETINGSREGISTER_H
