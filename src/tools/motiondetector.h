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
    
    /**
     * Create a motion detector for the given record
     */
    MotionDetector(Record const * record);
    
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
    
    unsigned int begining() const;
    unsigned int peak() const;
    unsigned int end() const;
    
    QMap<unsigned int, double> amplitudes() const;
    QMap<unsigned int, double> speeds() const;
    
    /**
     * The factor used to compute the velocity threshold.
     */
    static double const VELOCITY_THRESHOLD_FACTOR = 0.05;
    
private:
    Record const * _record;
    
    QMap<unsigned int, double> _amplitudes;
    QMap<unsigned int, double> _speeds;
    
    bool _detected;
    
    unsigned int _begining;
    unsigned int _peak;
    unsigned int _end;
};

#endif // MOTION_DETECTOR_H
