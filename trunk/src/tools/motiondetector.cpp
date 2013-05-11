#include "motiondetector.h"

#include <QtGlobal>
#include <QtDebug>

#include "utils/angle.h"
#include "utils/point.h"
#include "utils/record.h"
#include "utils/vector.h"

MotionDetector::MotionDetector(Record const * record)
{
    _record = record;
    _detected = false;
}

MotionDetector::~MotionDetector()
{
}

QMap<unsigned int, double> MotionDetector::amplitudes() const
{
    Q_ASSERT(detected() == true);
    return _amplitudes;
}

unsigned int MotionDetector::begin() const
{
    Q_ASSERT(detected() == true);
    return _begin;
}

bool MotionDetector::detect(QPair<QString, QString> fixed, QPair<QString, QString> mobile)
{
    Q_ASSERT(_record != 0);
    
    /**
     * Clean eventually existing data
     */
    _amplitudes.clear();
    _speeds.clear();
    _detected = false;
    
    /**
     * Retrieve the markers
     * TODO Check if there is an unknown marker
     */
    Marker fixedProximal = _record->marker(fixed.first);
    Marker fixedDistal = _record->marker(fixed.second);
    Marker mobileProximal = _record->marker(mobile.first);
    Marker mobileDistal = _record->marker(mobile.second);
    
    /**
     * Compute amplitudes of the angle at every recorded frame
     */
    for(unsigned int time = 1; time < _record->duration(); time++)
    {
        if(fixedProximal.exists(time) && fixedDistal.exists(time) && mobileProximal.exists(time) && mobileDistal.exists(time))
        {
            _amplitudes.insert(time, Angle(Vector(fixedProximal.point(time), fixedDistal.point(time)), Vector(mobileProximal.point(time), mobileDistal.point(time))).amplitude());
        }
    }
    
    /**
     * Compute angular speeds at every recorded frame, and remember peak time
     */
    _speeds.insert(1, 0);
    _peak = 1;
    for(unsigned int time = 2; time < _record->duration(); time++)
    {
        if(!_amplitudes.contains(time))
        {
            continue;
        }
        if(_amplitudes.contains(time - 1))
        {
            double delta = _amplitudes.value(time) - _amplitudes.value(time - 1);
            if(delta < 0)
            {
                delta = -delta;
            }
            _speeds.insert(time, delta);
            if(delta > _speeds.value(_peak))
            {
                _peak = time;
            }
        }
    }
    
    /**
     * Begining of motion is computed from peak time and backward-tracking
     */
    _begin = 0;
    for(unsigned int time = _peak; time >= 1; time--)
    {
        if(_speeds.contains(time) && _speeds.value(time) < threshold())
        {
            _begin = time;
            break;
        }
    }
    
    /**
     * End of the motion is computed from peak time and forward-tracking
     */
    _end = 0;
    for(unsigned int time = _peak; time <= _record->duration(); time++)
    {
        if(_speeds.contains(time) && _speeds.value(time) < threshold())
        {
            _end = time;
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

unsigned int MotionDetector::end() const
{
    Q_ASSERT(detected() == true);
    return _end;
}

unsigned int MotionDetector::peak() const
{
    Q_ASSERT(detected() == true);
    return _peak;
}

void MotionDetector::setBegin(unsigned int newBegin)
{
        _begin = newBegin;
}

void MotionDetector::setEnd(unsigned int newEnd)
{
        _end = newEnd;
}

void MotionDetector::setPeak(unsigned int newPeak)
{
        _peak = newPeak;
}

void MotionDetector::setRecord(Record * record)
{
    _record = record;
}

QMap<unsigned int, double> MotionDetector::speeds() const
{
    Q_ASSERT(detected() == true);
    return _speeds;
}

double MotionDetector::threshold() const
{
    return _speeds.value(_peak) * VELOCITY_THRESHOLD_FACTOR;
}
