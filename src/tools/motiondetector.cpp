#include "motiondetector.h"

#include <QtGlobal>

MotionDetector::MotionDetector(Record const * record)
{
    _record = record;
    _detected = false;
}

bool MotionDetector::detect(QPair<QString, QString> fixed, QPair<QString, QString> mobile)
{
    Marker fixedProximal = _record.marker(fixed.first);
    Marker fixedDistal = _record.marker(fixed.second);
    Marker mobileProximal = _record.marker(mobile.first);
    Marker mobileDistal = _record.marker(mobile.second);
    
    QMap<unsigned int, double> amplitudes;
    for(unsigned int time = 1; time < record.duration(); time++)
    {
        if(fixedProximal.exists(time) && fixedDistal.exists(time) && mobileProximal.exists(time) && mobileDistal.exists(time))
        {
            amplitudes.insert(time, Angle(Vector(fixedProximal.point(time), fixedDistal.point(time)), Vector(mobileProximal.point(time), mobileDistal.point(time))).amplitude());
        }
    }
    
    QMap<unsigned int, double> speeds;
    speeds.insert(1, 0);
    unsigned int peak = 1;
    for(unsigned int time = 2; time < record.duration(); time++)
    {
        if(!amplitudes.contains(time))
        {
            continue;
        }
        if(amplitudes.contains(time - 1))
        {
            double delta = amplitudes.value(time) - amplitudes.value(time - 1);
            if(delta < 0)
            {
                delta = -delta;
            }
            speeds.insert(time, delta);
            if(delta > speeds.value(peak))
            {
                peak = time;
            }
        }
    }
    
    unsigned int start = 0;
    unsigned int stop = 0;
    double threshold = speeds.value(peak) * VELOCITY_THRESHOLD_FACTOR;
    
    for(unsigned int time = peak; time >= 1; time--)
    {
        if(speeds.contains(time) && speeds.value(time) < threshold)
        {
            start = time;
            break;
        }
    }
    
    for(unsigned int time = peak; time <= record.duration(); time++)
    {
        if(speeds.contains(time) && speeds.value(time) < threshold)
        {
            stop = time;
            break;
        }
    }
    
    _detected = true;
    
    return detected();
}

bool MotionDetector::detected() const
{
    return _detected;
}

Instant MotionDetector::begin() const
{
    Q_ASSERT(detected() == true);
    return _begin;
}

Instant MotionDetector::peak() const
{
    Q_ASSERT(detected() == true);
    return _peak;
}

Instant MotionDetector::end() const
{
    Q_ASSERT(detected() == true);
    return _end;
}
