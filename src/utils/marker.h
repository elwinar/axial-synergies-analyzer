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
    Marker();
    ~Marker();
    
    Point point(unsigned int time) const;
    void setPoint(unsigned int time, Point point);
    bool exists(unsigned int time) const;
    
    unsigned int duration() const;
    
private:
    QMap<unsigned int, Point> _points;
};

#endif // MARKER_H
