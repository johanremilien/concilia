#include "participantsregister.h"
#include "participant.h"

const Participant &ParticipantsRegister::create(const QString &firstName, const QString &lastName)
{
    return rename(create().getId(), firstName, lastName);
}

Participants ParticipantsRegister::find(const QString &firstName, const QString &lastName) const
{
    Participants result;
    for (auto & participant : m_register) {
        if (firstName.isEmpty() && !lastName.isEmpty()) {
            if (participant->getFirstName() != firstName)
                continue;
        } else if (!firstName.isEmpty() && lastName.isEmpty()) {
            if (participant->getLastName() != lastName)
                continue;
        } else if (!firstName.isEmpty() && !lastName.isEmpty()) {
            if (participant->getFirstName() != firstName || participant->getLastName() != lastName)
                continue;
        }
        result.append(participant);
    }
    return result;
}

const QString &ParticipantsRegister::setFirstName(id id, const QString &firstName)
{
    return const_cast<Participant *>(m_register.value(id))->setFirstName(firstName);
}

const QString &ParticipantsRegister::setLastName(id id, const QString &lastName)
{
    return const_cast<Participant *>(m_register.value(id))->setFirstName(lastName);
}

const Participant &ParticipantsRegister::rename(id id, const QString &firstName, const QString &lastName)
{
    return const_cast<Participant *>(m_register.value(id))->rename(firstName, lastName);
}
