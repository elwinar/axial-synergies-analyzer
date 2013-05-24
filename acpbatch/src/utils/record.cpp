#include "record.h"

#include <QtGlobal>
#include <QDebug>

Record::Record()
{
    setMarkersDuration(0);
    setAnalogdatasDuration(0);
}

Record::~Record()
{
}

bool Record::containsMarker(QString label) const
{
    return _markers.contains(label);
}

bool Record::containsAnalogdata(QString label) const
{
    return _analogdatas.contains(label);
}

unsigned int Record::countMarkers() const
{
    return _markers.count();
}

unsigned int Record::countAnalogdatas() const
{
    return _analogdatas.count();
}

unsigned int Record::durationMarkers() const
{
    return _markersDuration;
}

unsigned int Record::durationAnalogdatas() const
{
    return _analogdatasDuration;
}

QString Record::filename() const
{
    return _filename;
}

Marker Record::generate(Point point) const
{
    Marker marker;
    for(unsigned int time = 1; time <= durationMarkers(); time++)
    {
        marker.setPoint(time, point);
    }
    return marker;
}

QList<QString> Record::labelsMarkers() const
{
    return _markers.keys();
}

QList<QString> Record::labelsAnalogdatas() const
{
    return _analogdatas.keys();
}

Marker Record::marker(QString label) const
{
    Q_ASSERT(containsMarker(label));
    return _markers.value(label);
}

AnalogData Record::analogdata(QString label) const
{
    Q_ASSERT(containsAnalogdata(label));
    return _analogdatas.value(label);
}

QString Record::name() const
{
    return _name;
}

void Record::setMarkersDuration(unsigned int duration)
{
    _markersDuration = duration;
    _markers.insert("O", generate(Point(0, 0, 0)));
    _markers.insert("X", generate(Point(1, 0, 0)));
    _markers.insert("Y", generate(Point(0, 1, 0)));
    _markers.insert("Z", generate(Point(0, 0, 1)));
}

void Record::setAnalogdatasDuration(unsigned int duration)
{
    _analogdatasDuration = duration;
}

void Record::setFilename(QString filename)
{
    _filename = filename;
}

void Record::setMarker(QString label, Marker marker)
{
    _markers.insert(label, marker);
}

void Record::setAnalogdata(QString label, AnalogData data)
{
    _analogdatas.insert(label, data);
}

void Record::setName(QString name)
{
    _name = name;
}
