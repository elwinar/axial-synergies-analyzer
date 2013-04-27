#include "record.h"

#include <QtGlobal>

Record::Record()
{
    _markers.insert("O", generate(Point(0, 0, 0)));
    _markers.insert("X", generate(Point(1, 0, 0)));
    _markers.insert("Y", generate(Point(0, 1, 0)));
    _markers.insert("Z", generate(Point(0, 0, 1)));
}

Record::~Record()
{
}

Marker Record::marker(QString label) const
{
    Q_ASSERT(contains(label));
    return _markers.value(label);
}

void Record::setMarker(QString label, Marker marker)
{
    _markers.insert(label, marker);
}

bool Record::contains(QString label) const
{
    return _markers.contains(label);
}

unsigned int Record::count() const
{
    return _markers.count();
}

QList<QString> Record::labels() const
{
    return _markers.keys();
}

unsigned int Record::duration() const
{
    return _duration;
}

void Record::setDuration(unsigned int duration)
{
    _duration = duration;
}

Marker Record::generate(Point point) const
{
    Marker marker;
    for(unsigned int time; time <= duration; time++)
    {
        marker.setPoint(time, point);
    }
    return marker;
}
