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
    qDebug() << "[record] initializing axis O";
    _markers.insert("O", generate(Point(0, 0, 0)));
    qDebug() << "[record] initializing axis X";
    _markers.insert("X", generate(Point(1, 0, 0)));
    qDebug() << "[record] initializing axis Y";
    _markers.insert("Y", generate(Point(0, 1, 0)));
    qDebug() << "[record] initializing axis Z";
    _markers.insert("Z", generate(Point(0, 0, 1)));
}

Marker Record::generate(Point point) const
{
    qDebug() << "[record] generating generic marker";
    Marker marker;
    for(unsigned int time = 1; time <= duration(); time++)
    {
        marker.setPoint(time, point);
    }
    return marker;
}
