#include "vector.h"

#include <cmath>

Vector::Vector()
{
    Vector(Point(), Point());
}

Vector::Vector(Point distal)
{
    Vector(Point(), distal);
}

Vector::Vector(Point proximal, Point distal)
{
    _proximal = proximal;
    _distal = distal;
}

Vector::~Vector()
{
}

Point Vector::proximal() const
{
    return _proximal;
}

void Vector::setProximal(Point proximal)
{
    _proximal = proximal;
}

Point Vector::distal() const
{
    return _distal;
}

void Vector::setDistal(Point distal)
{
    _distal = distal;
}

double Vector::length() const
{
    return sqrt(pow(_distal.x() - _proximal.x(), 2) + pow(_distal.y() - _proximal.y(), 2) + pow(_distal.z() - _proximal.z(), 2));
}
