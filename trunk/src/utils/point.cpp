#include "point.h"

Point::Point(double x, double y, double z)
{
    _x = x;
    _y = y;
    _z = z;
}

Point::~Point()
{
}

double Point::x() const
{
    return _x;
}

double Point::y() const
{
    return _y;
}

double Point::z() const
{
    return _z;
}

void Point::setX(double x)
{
    _x = x;
}

void Point::setY(double y)
{
    _y = y;
}

void Point::setZ(double z)
{
    _z = z;
}

Point Point::operator+(Point const & operand) const
{
    return Point(_x + operand._x, _y + operand._y, _z + operand._z);
}

Point Point::operator-(Point const & operand) const
{
    return Point(_x - operand._x, _y - operand._y, _z - operand._z);
}
