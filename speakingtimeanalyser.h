#ifndef SPEAKINGTIMEANALYSER_H
#define SPEAKINGTIMEANALYSER_H

#include "speakingtimebase.h"

class SpeakingTimeAnalyser : public SpeakingTimeBase
{
    Q_OBJECT
public:
    SpeakingTimeAnalyser(QObject *parent = nullptr);
    ~SpeakingTimeAnalyser() = default;
};

#endif // SPEAKINGTIMEANALYSER_H
