#ifndef SPEAKINGTIMEANALYSER_H
#define SPEAKINGTIMEANALYSER_H

#include <QObject>
#include <memory>

#include "typedef.h"

class SpeakingTimeAnalyser : public QObject
{
    Q_OBJECT
public:
    SpeakingTimeAnalyser(QObject *parent = nullptr);
    ~SpeakingTimeAnalyser();
};

#endif // SPEAKINGTIMEANALYSER_H
