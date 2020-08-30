#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QDateTime>
#include <QHash>
#include <QVector>

#define UNDEFINED_ID -1

class Participant;
class Meeting;

typedef qint16 id;
typedef quint64 duration;

typedef struct {
    QDateTime dateTime;
    duration duration; //seconds
} Record;

template<typename T>
using RegisterHash = QHash<id, const T *>;

typedef RegisterHash<QVector<const Record *>> Records;
typedef QList<const Meeting *> Meetings;
typedef QList<const Participant *> Participants;

#endif // TYPEDEF_H
