#ifndef MEETINGSREGISTER_H
#define MEETINGSREGISTER_H

#include "register.h"

class MeetingsRegister : public Register<Meeting>
{
public:
    const Meeting &create(const QString &name);
    const QString &getName(ID id);
    inline const QString &setName(ID id, const QString &name);
    const Meeting &rename(ID id, const QString &name);

    bool start(ID id);
    bool pause(ID id);
    bool restart(ID id);
    bool end(ID id);
    void addParticipant(ID meetingId, ID particpantId);
    inline void addParticipant(ID meetingId, const Participant &participant);
    bool removeParticipant(ID meetingId, ID participantId);
    inline bool removeParticipant(ID meetingId, const Participant &participant);
    Duration getDuration(ID id) const;

    ID find(const QString &name) const;
    IDs findIncompleteName(const QString &name) const;

protected:
    using Register<Meeting>::create;
};

#endif // MEETINGSREGISTER_H
