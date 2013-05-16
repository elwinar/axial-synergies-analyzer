#ifndef ANALOGDATA_H
#define ANALOGDATA_H

#include <QMap>

/**
 * Represent the electric signal (in mV) over time.
 */
class AnalogData
{
public:
    /**
     * Create an empty analogData, ie with no recorded data
     */
    AnalogData();
    
    /**
     * Destroy the data
     */
    ~AnalogData();
    
    /**
     * The duration of the data, ie the lastest recorded frame
     */
    unsigned int duration() const;
    
    /**
     * Tells wheter the data has a recorded signal for a given frame
     */
    bool exists(unsigned int time) const;
    
    /**
     * Return the recorded signal of the data for the given frame
     */
    double signal(unsigned int time) const;
    
    /**
     * Set the recorded signal of the data for the given frame
     */
    void setSignal(unsigned int time, double);
    
private:
    QMap<unsigned int, double> _signals;
};

#endif // ANALOGDATA_H
