#include "angle.h"

#include <cmath>
#include "utils/pi.h"

Angle::Angle()
{
    Angle(Vector(), Vector());
}

Angle::Angle(Vector fixed, Vector mobile)
{
    _fixed = fixed;
    _mobile = mobile;
}

Angle::~Angle()
{
}

Vector Angle::fixed() const
{
    return _fixed;
}

void Angle::setFixed(Vector fixed)
{
    _fixed = fixed;
}

Vector Angle::mobile() const
{
    return _mobile;
}

void Angle::setMobile(Vector mobile)
{
    _mobile = mobile;
}

double Angle::amplitude() const
{
    /*
     * the formula for the amplitude of an angle is given by Al-Kashi Theorem, aka Law of cosines
     * see http://en.wikipedia.org/wiki/Law_of_cosines
     */
    double a = _fixed.length();
    double b = _mobile.length();
    double c = Vector(_fixed.distal(), _mobile.distal() - _mobile.proximal() + _fixed.proximal()).length();
    double amplitude = acos((pow(a,2) + pow(b,2) - pow(c,2)) / (2 * a * b));
    
    /*
     * convert the amplitude from radians to degrees and return it
     */
    return amplitude / PI * 180;
}
