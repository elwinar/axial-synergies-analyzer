#ifndef RECORD_H
#define RECORD_H

#include <QList>
#include <QMap>
#include <QString>
#include "utils/marker.h"

class Record
{
public:
    Record();
    ~Record();
    
    Marker marker(QString label) const;
    void setMarker(QString label, Marker marker);
    bool contains(QString label) const;
    unsigned int count() const;
    QList<QString> labels() const;
    
    unsigned int duration() const;
    void setDuration(unsigned int duration);
    
private:
    QMap<QString, Marker> _markers;
    unsigned int _duration;
};

#endif // RECORD_H
