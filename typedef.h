#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QDateTime>
#include <QHash>
#include <QVector>

#include <QDebug>

#define UNDEFINED_ID -1

class Participant;
class Meeting;

class ParticipantsRegister;
class MeetingsRegister;

typedef qint16 ID;
typedef quint64 Duration;

/*
struct DistinctID{
    DistinctID() : id() {}
    DistinctID(ID id) : id(id) { }
    DistinctID(DistinctID &mid) : id(mid.id) { }
    operator ID&() { return id; }
    operator ID () { return id; };
private:
    ID id;
};
*/

typedef struct {
    QDateTime startTime;
    QDateTime endTime;
} Record;

template <typename T>
using RegisterVector = QVector<const T *>;

typedef QVector<ID> IDs;
typedef RegisterVector<Record> Records;
typedef RegisterVector<Meeting> Meetings;
typedef RegisterVector<Participant> Participants;


template<typename T>
using RegisterHash = QHash<ID, T *>;

typedef RegisterHash<Records> RecordVectorHash;

typedef RegisterHash<Meeting> MeetingHash;
typedef RegisterHash<Participant> ParticipantHash;

#endif // TYPEDEF_H
