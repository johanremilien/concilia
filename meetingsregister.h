#ifndef MEETINGSREGISTER_H
#define MEETINGSREGISTER_H

#include "register.h"

class MeetingsRegister : public Register<Meeting>
{
public:
    const Meeting &create(const QString &name);
    const QString &getName(id id);
    inline const QString &setName(id id, const QString &name);
    inline const Meeting &rename(id id, const QString &name);

    inline void start(id id);
    inline void stop(id id);
    inline void addParticipant(id meetingId, id particpantId);
    inline void addParticipant(id meetingId, const Participant &participant);
    inline bool removeParticipant(id meetingId, id participantId);
    inline bool removeParticipant(id meetingId, const Participant &participant);
    duration getDuration(id id) const;

    id find(const QString &name) const;
    IDs findIncompleteName(const QString &name) const;

protected:
    using Register<Meeting>::create;
};

#endif // MEETINGSREGISTER_H
