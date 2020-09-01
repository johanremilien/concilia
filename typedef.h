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
    QDateTime startTime;
    QDateTime endTime;
} Pause;

typedef struct {
    QDateTime dateTime;
    duration duration; //seconds
} Record;


template <typename T>
using RegisterVector = QVector<const T *>;

typedef RegisterVector<Record> Records;
typedef RegisterVector<Pause> Pauses;
typedef RegisterVector<Meeting> Meetings;
typedef RegisterVector<Participant> Participants;

template<typename T>
using RegisterHash = QHash<id, T *>;

typedef RegisterHash<Records> RecordVectorHash;

typedef RegisterHash<Meeting> MeetingHash;
typedef RegisterHash<Participant> ParticipantHash;

#endif // TYPEDEF_H
