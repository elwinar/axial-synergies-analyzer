#ifndef VECTOR_H
#define VECTOR_H

#include "utils/point.h"

/**
 * Represent an oriented vector composed of two point in a three-dimensionnal space. The origin point is called proximal point, while the directionnal point is called distal.
 */
class Vector
{
public:
    Vector();
    Vector(Point distal);
    Vector(Point proximal, Point distal);
    ~Vector();
    
    Point proximal() const;
    void setProximal(Point proximal);
    
    Point distal() const;
    void setDistal(Point distal);
    
    double length() const;
    
private:
    Point _proximal;
    Point _distal;
};

#endif // VECTOR_H
