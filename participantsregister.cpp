#include "participantsregister.h"
#include "participant.h"

const Participant &ParticipantsRegister::create()
{
    const Participant * participant = new Participant(m_counter++);
    return **(m_register.insert(participant->getId(), participant));
}

Participants ParticipantsRegister::get(QString firstName, QString lastName)
{
    Participants list;
    if (firstName.isEmpty() && lastName.isEmpty()) {
        list = m_register.values();
    } else if (firstName.isEmpty() && !lastName.isEmpty()) {
        for (const auto & participant : m_register) {
            if (participant->getFirstName() == firstName)
                list.append(participant);
        }
    } else if (!firstName.isEmpty() && lastName.isEmpty()) {
        for (const auto & participant : m_register) {
            if (participant->getLastName() == lastName)
                list.append(participant);
        }
    } else {
        for (const auto & participant : m_register) {
            if (participant->getFirstName() == firstName && participant->getLastName() == lastName)
                list.append(participant);
        }
    }
    return list;
}
