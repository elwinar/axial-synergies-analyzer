#ifndef MOTION_DETECTOR_H
#define MOTION_DETECTOR_H

#include <QMap>
#include <QPair>
#include <QString>

class Record;

/**
 * Detect the motion in a record using angular speed variation of a disjoint angle in the record. It compute peak of velocity, then search for the moment where the velocity goes below a certain proportion of the peak's speed on each side of the peak, exposing begin and end times of the motion.
 */
class MotionDetector
{
public:
    
    /**
     * Create a motion detector for the given record
     */
    MotionDetector(Record const * record = 0);
    
    /**
     * Destroy the motion detector
     */
    ~MotionDetector();
    
    /**
     * The factor used to compute the velocity threshold.
     */
    static double const VELOCITY_THRESHOLD_FACTOR = 0.05;
    
    /**
     * A map containing the amplitudes for every recorded frame (when available)
     */
    QMap<unsigned int, double> amplitudes() const;
    
    /**
     * The begining frame of the motion
     */
    unsigned int begin() const;
    
    /**
     * Run the detection providing marker labels for the fixed and mobile segments of the record.
     * 
     * @return True if a motion has been detected, whether the detection has been run and found nothing or hadn't been run.
     */
    bool run(QPair<QString, QString> fixed, QPair<QString, QString> mobile);
    
    /**
     * Check if a motion has been detected, whether the detection has been run and found nothing or hadn't been run.
     */
    bool detected() const;
    
    /**
     * The end frame of the motion
     */
    unsigned int end() const;
    
    /**
     * The frame where speed is maximum in motion
     */
    unsigned int peak() const;
    
    /**
     * Tell if the detector have already ran
     */
    bool ran() const;
    
    /**
     * The record on which the detector applies
     */
    Record * record() const;
    
    /**
     * Sets the begining frame of the motion
     */
    void setBegin(unsigned int newBegin);
    
    /**
     * Sets the end frame of the motion
     */
    void setEnd(unsigned int newEnd);
    
    /**
     * Sets the frame where speed is maximum in motion
     */
    void setPeak(unsigned int newPeak);
    
    /**
     * Set the record to detect motion from
     */
    void setRecord(Record * record);
    
    /**
     * A map containing the speeds for every recorded frame (when available)
     */
    QMap<unsigned int, double> speeds() const;
    
    /**
     * The threshold value for the detected motion
     */
    double threshold() const;
    
private:
    Record const * _record;
    
    QMap<unsigned int, double> _amplitudes;
    QMap<unsigned int, double> _speeds;
    
    bool _detected;
    bool _ran;
    
    unsigned int _begin;
    unsigned int _peak;
    unsigned int _end;
};

#endif // MOTION_DETECTOR_H
