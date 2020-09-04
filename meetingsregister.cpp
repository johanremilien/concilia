#include "meetingsregister.h"
#include "meeting.h"

const Meeting &MeetingsRegister::create(const QString &name)
{
    const Meeting *result;
    if (find(name) == UNDEFINED_ID) {
        result = &create();
        rename(result->getId(), name);
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

const QString &MeetingsRegister::getName(id id)
{
    const QString *result = &undefined_name;
    if (get(id))
        result = &(get(id)->getName());
    return *result;
}

const QString &MeetingsRegister::setName(id id, const QString &name)
{
    const QString *result = &undefined_name;
    if (get(id))
        result = &(get(id)->setName(name));
    return *result;
}

const Meeting &MeetingsRegister::rename(id id, const QString &name)
{
    Meeting *meeting = get(id);
    if (meeting)
        meeting->setName(name);
    else
        itemNotFound(id);
    return *meeting;
}

id MeetingsRegister::find(const QString &name) const
{
    id result = UNDEFINED_ID;
    process([&name, &result](const Meeting &meeting)
    {
        bool exitLoop = false;
        if (meeting.getName() == name) {
            result = meeting.getId();
            exitLoop = true;
        }
        return exitLoop;
    });
    return result;
}

IDs MeetingsRegister::findIncompleteName(const QString &name) const
{
    IDs result;
    process([&name, &result](const Meeting &meeting)
    {
        bool exitLoop = false;
        if (meeting.getName().contains(name))
            result.append(meeting.getId());
        return exitLoop;
    });
    return result;
}
