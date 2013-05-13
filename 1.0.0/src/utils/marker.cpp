#include "marker.h"

#include <QtGlobal>

Marker::Marker()
{
};

Marker::~Marker()
{
}

unsigned int Marker::duration() const
{
    return _points.end().key();
}

bool Marker::exists(unsigned int time) const
{
    return _points.contains(time);
}

Point Marker::point(unsigned int time) const
{
    Q_ASSERT(exists(time));
    return _points.value(time);
}

void Marker::setPoint(unsigned int time, Point point)
{
    _points.insert(time, point);
}
