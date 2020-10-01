#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <QDateTime>
#include <QHash>
#include <QVector>

#include <QDebug>

class Participant;
class Meeting;

class ParticipantsRegister;
class MeetingsRegister;

typedef qint16 ID;
extern ID UNDEFINED_ID;

typedef quint64 Duration;

typedef struct {
    QDateTime startTime;
    QDateTime endTime;
} Record;

typedef QVector<ID> IDs;
typedef QVector<Record> Records;

template <typename T>
using RegisterVector = QVector<const T &>;

typedef RegisterVector<const Meeting &> Meetings;
typedef RegisterVector<const Participant &> Participants;


template<typename T>
using RegisterHash = QHash<ID, T>;

typedef RegisterHash<Records> RecordVectorHash;
typedef RegisterHash<Meeting> MeetingHash;
typedef RegisterHash<Participant> ParticipantHash;

#endif // TYPEDEF_H
