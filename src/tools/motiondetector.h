#ifndef MOTION_DETECTOR_H
#define MOTION_DETECTOR_H

#include <QPair>
#include <QString>

#include "utils/record.h"

/**
 * Detect the motion in a record using angular speed variation of a disjoint angle in the record. It compute peak of velocity, then search for the moment where the velocity goes below a certain proportion of the peak's speed on each side of the peak, exposing begin and end times of the motion.
 */
class MotionDetector
{
public:
    
    MotionDetector(Record const & record);
    
    /**
     * Holds the data associated with an angle at a particular instant.
     */
    struct Instant
    {
        int time;
        double speed;
        double amplitude;
    };
    
    /**
     * Run the detection providing marker labels for the fixed and mobile segments of the record.
     * 
     * @return True if a motion has been detected, whether the detection has been run and found nothing or hadn't been run.
     */
    bool detect(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    
    /**
     * Check if a motion has been detected, whether the detection has been run and found nothing or hadn't been run.
     */
    bool detected() const;
    
    Instant begin() const;
    Instant peak() const;
    Instant end() const;
    
    /**
     * The factor used to compute the velocity threshold.
     */
    static double const VELOCITY_THRESHOLD_FACTOR = 0.05;

protected:
    
private:
    Record const & _record;
    bool _detected;
    Instant _begin;
    Instant _peak;
    Instant _end;
};

#endif // MOTION_DETECTOR_H
