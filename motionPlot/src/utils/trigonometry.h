#ifndef TRIGONOMETRY_H
#define TRIGONOMETRY_H

#include <cmath>
#include <QPair>

class Trigonometry
{
public:
	/**
	 * @return the polar coordinates of the given point(x,y).
	 * the first item is argument, the second is modulus.
	 * formulas and details from http://en.wikipedia.org/wiki/Polar_coordinate_system
	 */
	static QPair<double, double> toPolar(double x, double y);
};

#endif // TRIGONOMETRY_H
