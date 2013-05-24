#ifndef EMG_ANALYZER_H
#define EMG_ANALYZER_H

#include "utils/record.h"
#include "tools/motiondetector.h"

#include <QMap>
#include <QTextStream>

class EMGAnalyzer
{
public:
    EMGAnalyzer(Record * record): _record(record)
    {
    }
    
    void run(unsigned int begin, unsigned int end, QTextStream & out);
    
    double computeRangeMean(unsigned int start, unsigned int width, QMap<unsigned int, double> data);
    
    double computeEMGMean(unsigned int start, unsigned int width, AnalogData data);
    
private:
    Record * _record;
};

#endif // EMG_ANALYZER_H
