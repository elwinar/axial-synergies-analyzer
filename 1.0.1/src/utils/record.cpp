#include "record.h"

#include <QtGlobal>
#include <QDebug>

Record::Record()
{
    setDuration(0);
}

Record::~Record()
{
}

bool Record::contains(QString label) const
{
    return _markers.contains(label);
}

unsigned int Record::count() const
{
    return _markers.count();
}

unsigned int Record::duration() const
{
    return _duration;
}

QString Record::filename() const
{
    return _filename;
}

Marker Record::generate(Point point) const
{
    Marker marker;
    for(unsigned int time = 1; time <= duration(); time++)
    {
        marker.setPoint(time, point);
    }
    return marker;
}

QList<QString> Record::labels() const
{
    return _markers.keys();
}

Marker Record::marker(QString label) const
{
    Q_ASSERT(contains(label));
    return _markers.value(label);
}

QString Record::name() const
{
    return _name;
}

void Record::setDuration(unsigned int duration)
{
    _duration = duration;
    _markers.insert("O", generate(Point(0, 0, 0)));
    _markers.insert("X", generate(Point(1, 0, 0)));
    _markers.insert("Y", generate(Point(0, 1, 0)));
    _markers.insert("Z", generate(Point(0, 0, 1)));
}

void Record::setFilename(QString filename)
{
    _filename = filename;
}

void Record::setMarker(QString label, Marker marker)
{
    _markers.insert(label, marker);
}

void Record::setName(QString name)
{
    _name = name;
}
