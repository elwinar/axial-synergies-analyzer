#include "record.h"

#include <QtGlobal>

Record::Record()
{
}

Record::~Record()
{
}

Marker Record::marker(QString label) const
{
    Q_ASSERT(containsMarker(label));
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
