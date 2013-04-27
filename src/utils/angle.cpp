#include "angle.h"

#include <cmath>
#include "utils/pi.h"

Angle::Angle()
{
    Angle(Vector());
}

Angle::Angle(Vector first, Vector second)
{
    _first = first;
    _second = second;
}

Angle::~Angle()
{
}

Vector Angle::first() const
{
    return _first;
}

void Angle::setFirst(Vector first)
{
    _first = first;
}

Vector Angle::second() const
{
    return _second;
}

void Angle::setSecond(Vector second)
{
    _second = second;
}

double Angle::amplitude() const
{
    /*
     * the formula for the amplitude of an angle is given by Al-Kashi Theorem, aka Law of cosines
     * see http://en.wikipedia.org/wiki/Law_of_cosines
     */
    double a = _first.length();
    double b = _second.length();
    double c = Vector(_first.distal(), _second.distal() - _second.proximal() + _first.proximal()).length();
    double amplitude = acos((pow(a,2) + pow(b,2) - pow(c,2)) / (2 * a * b));
    
    /*
     * convert the amplitude from radians to degrees and return it
     */
    return amplitude / PI * 180;
}
