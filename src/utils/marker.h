#ifndef MARKER_H
#define MARKER_H

#include <QMap>
#include "utils/point.h"

/**
 * Represent the position of a point in a three-dimensionnal space over time.
 */
class Marker
{
public:
    /**
     * Create an empty marker, ie with no recorded frame
     */
    Marker();
    
    /**
     * Destroy the marker
     */
    ~Marker();
    
    /**
     * The duration of the marker, ie the lastest recorded frame
     */
    unsigned int duration() const;
    
    /**
     * Tells wheter the marker has a recorded position for a given frame
     */
    bool exists(unsigned int time) const;
    
    /**
     * Return the recorded point of the marker for the given frame
     */
    Point point(unsigned int time) const;
    
    /**
     * Set the recorded point of the marker for the given frame
     */
    void setPoint(unsigned int time, Point point);
    
private:
    QMap<unsigned int, Point> _points;
};

#endif // MARKER_H
