#include "emganalyzer.h"

#include <QApplication>

#define RANGE_STEP 5
#define RANGE_MARGIN 10
#define RANGE_WIDTH 20
#define RANGE_WIDTH_MIN 5
#define RANGE_WIDTH_DECREASE_FACTOR 0.5

#define RANGE_RADIUS 10

#include "utils/angle.h"
#include <QVector>
#include <QSettings>
#include <cmath>

void EMGAnalyzer::run(unsigned int begin, unsigned int end, QTextStream & out)
{
    qDebug() << "[emg] start";
    QSettings settings(QApplication::applicationFilePath().append(".ini"), QSettings::IniFormat);
    MotionDetector motionDetector(_record);
    
    begin -= settings.value("T1/before", RANGE_RADIUS * 10).toUInt() / 10;
    end -= settings.value("T2/before", RANGE_RADIUS * 10).toUInt() / 10;
    unsigned int beginWidth = settings.value("T1/before", RANGE_RADIUS * 10).toUInt() / 10 + settings.value("T1/after", RANGE_RADIUS * 10).toUInt() / 10;
    unsigned int endWidth = settings.value("T2/before", RANGE_RADIUS * 10).toUInt() / 10 + settings.value("T2/after", RANGE_RADIUS * 10).toUInt() / 10;
    
    QVector<int> ranges;
    
    unsigned int range_width = RANGE_WIDTH / RANGE_WIDTH_DECREASE_FACTOR;
    unsigned int range_margin = RANGE_MARGIN;
    
    qDebug() << "[emg] computing speeds";
    
    motionDetector.run(QPair<QString, QString>("O", "Z"), QPair<QString, QString>("LTRO", "LSHO"), Angle::SPACE);
    QMap<unsigned int, double> speeds = motionDetector.speeds();
    
    qDebug() << "[emg] computing stable windows";
    while(ranges.empty() && range_width > RANGE_WIDTH_MIN)
    {
        range_width *= RANGE_WIDTH_DECREASE_FACTOR;
        if(begin > range_width + range_margin)
        {
            qDebug() << "[emg] trying with a width of" << range_width;
            for(unsigned int i = 1; i < begin - range_width - range_margin;)
            {
                unsigned int start = i;
                qDebug() << "[emg] starting at index" << start;
                for(; i < begin - range_margin && speeds.contains(i); i++);
                qDebug() << "[emg] went until index" << i;
                if(i >= range_width)
                {
                    for(; start < i - range_width; start += RANGE_STEP)
                    {
                        ranges.push_back(start);
                    }
                }
                qDebug() << "[emg] skiping holes";
                for(; i < begin - range_width - range_margin && !speeds.contains(i); i++);
            }
        }
    }
    
    if(ranges.empty())
    {
        qDebug() << "[emg] none found, trying right side";
        
        range_width = RANGE_WIDTH / RANGE_WIDTH_DECREASE_FACTOR;
        range_margin = RANGE_MARGIN;
        
        motionDetector.run(QPair<QString, QString>("O", "Z"), QPair<QString, QString>("RTRO", "RSHO"), Angle::SPACE);
        speeds = motionDetector.speeds();
        
        while(ranges.empty() && range_width > RANGE_WIDTH_MIN)
        {
            range_width *= RANGE_WIDTH_DECREASE_FACTOR;
            if(begin > range_width + range_margin)
            {
                qDebug() << "[emg] trying with a width of" << range_width;
                for(unsigned int i = 1; i < begin - range_width - range_margin;)
                {
                    unsigned int start = i;
                    qDebug() << "[emg] starting at index" << start;
                    for(; i < begin - range_margin && speeds.contains(i); i++);
                    qDebug() << "[emg] went until index" << i;
                    if(i >= range_width)
                    {
                        for(; start < i - range_width; start += RANGE_STEP)
                        {
                            ranges.push_back(start);
                        }
                    }
                    qDebug() << "[emg] skiping holes";
                    for(; i < begin - range_width - range_margin && !speeds.contains(i); i++);
                }
            }
        }
    }
    
    if(ranges.empty())
    {
        qDebug() << "[emg] none found, logging error";
        out << "," << "error" << "\n";
        qDebug() << "[emg] stop";
        return;
    }
    
    qDebug() << "[emg] computing minimal stable window";
    
    double minMean = computeRangeMean(ranges.front(), range_width, speeds);
    double minIndex = ranges.front();
    for(int i = 1; i < ranges.size(); i++)
    {
        double mean = computeRangeMean(ranges[i], range_width, speeds);
        if(mean < minMean)
        {
            minMean = mean;
            minIndex = ranges[i];
        }
    }
    
    out << "," << minIndex * 10
        << "," << (minIndex + range_width) * 10
        << "," << begin * 10
        << "," << (begin + beginWidth) * 10
        << "," << end * 10
        << "," << (end + endWidth) * 10;
        
    qDebug() << "[emg] begining emg analyzis";
    
    for(unsigned int i = 1; i <= 8; i++)
    {
        if(_record->containsAnalogdata(QString("ZW%1").arg(i)))
        {
            qDebug() << "[emg]" << QString("ZW%1").arg(i) << "found, computing values";
            qDebug() << "[emg] TS";
            out << "," << computeEMGMean(minIndex * 10, range_width * 10, _record->analogdata(QString("ZW%1").arg(i)));
            qDebug() << "[emg] T1";
            out << "," << computeEMGMean(begin * 10, beginWidth * 2 * 10, _record->analogdata(QString("ZW%1").arg(i)));
            qDebug() << "[emg] T2";
            out << "," << computeEMGMean(end * 10, endWidth * 2 * 10, _record->analogdata(QString("ZW%1").arg(i)));
        }
        else
        {
            qDebug() << "[emg]" << QString("ZW%1").arg(i) << "not found";
            out << ",,,";
        }
    }
    out << "\n";
}

double EMGAnalyzer::computeRangeMean(unsigned int start, unsigned int width, QMap<unsigned int, double> data)
{
    double sum = 0;
    for(unsigned int i = start; i < start + width; i++)
    {
        sum += data[i];
    }
    return sum / width;
}

double EMGAnalyzer::computeEMGMean(unsigned int start, unsigned int width, AnalogData data)
{
    double sum = 0;
    qDebug() << "[emgmean] from" << start << "to" << (start + width);
    double missing = 0;
    for(unsigned int i = start; i <= start + width; i++)
    {
        if(data.exists(i))
        {
            if(data.signal(i) < 0)
            {
                sum -= data.signal(i);
            }
            else
            {
                sum += data.signal(i);
            }
        }
        else
        {
            missing++;
        }
    }
    if(missing / (width + 1) > 0.05)
    {
        qDebug() << "[emgmean] not liable";
        return -1;
    }
    return sum / (width + 1);
}
