#include "meetingsregister.h"
#include "meeting.h"

const Meeting &MeetingsRegister::create()
{
    Meeting *meeting = new Meeting(m_counter++);
    return **(m_register.insert(meeting->getId(), meeting));
}

const Meeting &MeetingsRegister::create(const QString &name)
{
    const Meeting *result;
    if (name.isEmpty() || find(name).isEmpty()) {
        result = &create();
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

Meetings MeetingsRegister::find(const QString &name) const
{
    Meetings vector;
    for (auto & meeting : m_register) {
        if (name.isEmpty() || meeting->getName() == name)
            vector.append(meeting);
    }
    return vector;
}
