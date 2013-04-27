#ifndef RECORD_H
#define RECORD_H

#include <QList>
#include <QMap>
#include <QString>
#include "utils/marker.h"
#include "utils/point.h"

/**
 * Represent a set of markers identified by labels.
 */
class Record
{
public:
    /**
     * Create a record with only the standard marker for axis O, X, Y and Z
     */
    Record();
    ~Record();
    
    Marker marker(QString label) const;
    void setMarker(QString label, Marker marker);
    
    bool contains(QString label) const;
    unsigned int count() const;
    QList<QString> labels() const;
    
    unsigned int duration() const;
    void setDuration(unsigned int duration);
    
protected:
    Marker generate(Point point) const;
    
private:
    QMap<QString, Marker> _markers;
    unsigned int _duration;
};

#endif // RECORD_H
