#include "angle.h"

#include <cmath>
#include <QDebug>

#include "utils/pi.h"
#include "utils/trigonometry.h"
#include "utils/point.h"

Angle::Angle(Vector fixed, Vector mobile, int plan)
{
    _fixed = fixed;
    _mobile = mobile;
	_plan = plan;
}

Angle::~Angle()
{
}

double Angle::amplitude() const
{
	double amplitude = 0;
	
	/*
	 * the angle is analyzed as a 3D angle. This cannot be use to calculate the motion amplitude, 
	 * as angle cannot be oriented in space.
	 */
	if(_plan == Angle::SPACE)
	{
		/*
		 * the formula for the amplitude of an angle is given by Al-Kashi Theorem, aka Law of cosines
		 * see http://en.wikipedia.org/wiki/Law_of_cosines
		 */
		double a = _fixed.length();
		double b = _mobile.length();
		double c = Vector(_fixed.distal(), _mobile.distal() - _mobile.proximal() + _fixed.proximal()).length();
		amplitude = acos((pow(a,2) + pow(b,2) - pow(c,2)) / (2 * a * b));
	}
	else
	{
		/*
		 * translation of the 4 points:
		 * the two proximal points are merge, defining the new center.
		 * the two distal points are translated regarding their respectives proximal points
		 */
		Point fixed = _fixed.distal() - _fixed.proximal();
		Point mobile = _mobile.distal() - _mobile.proximal();
		double fixedArg;
		double mobileArg;
		
		switch(_plan)
		{
	
			/*
			 * the chosen plan is transversal plan (XY) 
			 * orientation X -> Y
			 */
			case Angle::XY:
			{
				/*
				 * Z coordinates is ignored
				 */
				fixed.setZ(0);
				mobile.setZ(0);
				
				/*
				 * calculation of the argument of the given angle, ie the radian value of the angle
				 */
				fixedArg = Trigonometry::toPolar(fixed.x(), fixed.y()).first;
				mobileArg = Trigonometry::toPolar(mobile.x(), mobile.y()).first;
				amplitude = mobileArg - fixedArg;
			}	
			break;
	
			/*
			 * the chosen plan is sagittal plan (YZ) 
			 * orientation Y -> Z
			 */
			case Angle::YZ:
			{
				/*
				 * X coordinates is ignored
				 */
				fixed.setX(0);
				mobile.setX(0);
				
				/*
				 * calculation of the argument of the given angle, ie the radian value of the angle
				 */
				fixedArg = Trigonometry::toPolar(fixed.y(), fixed.z()).first;
				mobileArg = Trigonometry::toPolar(mobile.y(), mobile.z()).first;
				amplitude = mobileArg - fixedArg;
			}
			break;
			
			/*
			 * the chosen plan is sagittal plan (ZX) 
			 * orientation Z -> X
			 */
			case Angle::ZX:
			{
				/*
				 * Y coordinates is ignored
				 */
				fixed.setY(0);
				mobile.setY(0);
				
				/*
				 * calculation of the argument of the given angle, ie the radian value of the angle
				 */
				fixedArg = Trigonometry::toPolar(fixed.z(), fixed.x()).first;
				mobileArg = Trigonometry::toPolar(mobile.z(), mobile.x()).first;
				amplitude = mobileArg - fixedArg;
			}
			break;
			default:
				/*
				 * incorrect plan selected. Alert an error ?
				 */
			break;
		}
	}
		
	/*
	 * convert the amplitude from radians to degrees and return it
	 * values are contained in a [0; 360] interval;
	 */
	 
	if(amplitude < 0)
	{
		amplitude += 2*PI;
	}
	return amplitude / PI * 180;
}

Vector Angle::fixed() const
{
    return _fixed;
}

Vector Angle::mobile() const
{
    return _mobile;
}

void Angle::setFixed(Vector fixed)
{
    _fixed = fixed;
}

void Angle::setMobile(Vector mobile)
{
    _mobile = mobile;
}
