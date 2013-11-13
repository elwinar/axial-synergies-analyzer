#include "trigonometry.h"
#include "pi.h"

#include <cmath>
#include <QDebug>

QPair<double, double> Trigonometry::toPolar(double x, double y)
{
	/*
	 * calculation of modulus: the distance between point(x,y) and origin.
	 */
	double modulus = sqrt(pow(x, 2) + pow(y, 2));
	double cos = x / modulus;
	double sin = y / modulus;
	double argument = acos(cos);
	/*
	 * if the angle is negative, switch the angle
	 */
	if(sin < 0)
	{
		argument = - argument;
	}
		
	return QPair<double, double>(argument, modulus);
}