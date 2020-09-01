#ifndef SPEAKINGTIMEANALYSER_H
#define SPEAKINGTIMEANALYSER_H

#include <QObject>

#include "typedef.h"

class SpeakingTimeAnalyser : public QObject
{
    Q_OBJECT
public:
    SpeakingTimeAnalyser(QObject * parent = nullptr);

   RegisterVector<Meeting> getMeetings();
   RegisterVector<Participant> getParticipants();
};

#endif // SPEAKINGTIMEANALYSER_H
