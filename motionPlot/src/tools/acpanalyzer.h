#ifndef ACP_ANALYZER_H
#define ACP_ANALYZER_H

#include <QSettings>
#include <QTextStream>
#include "utils/record.h"

class ACPAnalyzer
{
public:
    ACPAnalyzer(Record * record): _record(record)
    {
    }
    
    void run(unsigned int begin, unsigned int end, QTextStream & out);
    void print(QVector<QVector<double> > matrix);
    void eigen(QVector<QVector<double> > covariance, QVector<double> & values, QVector<QVector<double> > & vectors);
    
private:
    Record * _record;
};

#endif // ACP_ANALYZER_H
