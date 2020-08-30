#ifndef SPEAKINGTIMEANALYSER_H
#define SPEAKINGTIMEANALYSER_H

#include <QObject>

#include "typedef.h"


class SpeakingTimeAnalyser
{
public:
    SpeakingTimeAnalyser();

   RegisterHash<Meeting> getMeetings();
   RegisterHash<Participant> getParticipants();
};

#endif // SPEAKINGTIMEANALYSER_H
