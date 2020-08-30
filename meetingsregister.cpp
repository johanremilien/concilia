#include "meetingsregister.h"
#include "meeting.h"

const Meeting &MeetingsRegister::create(const QString &name)
{
    const Meeting *result;
    if (name.isEmpty() || get(name).isEmpty()) {
        Meeting * meeting = new Meeting(name, m_counter++);
        result = *(m_register.insert(meeting->getId(), meeting));
    } else {
        QLatin1Char separartor('_');
        bool isInteger;
        QStringList splitName = name.split(separartor);
        int index = splitName.last().toInt(&isInteger, 10);
        if (isInteger)
            splitName.removeLast();
        QString newName = splitName.join(separartor).append(separartor + QString(index+1));
        result = &create(newName);
    }
    return *result;
}

Meetings MeetingsRegister::get(const QString &name)
{
    Meetings list;
    if (name.isEmpty()) {
        list = m_register.values();
    } else {
        for (const auto & meeting : m_register) {
            if (meeting->getName() == name)
                list.append(meeting);
        }
    }
    return list;
}
