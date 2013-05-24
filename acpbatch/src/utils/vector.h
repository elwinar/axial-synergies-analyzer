#ifndef VECTOR_H
#define VECTOR_H

#include "utils/point.h"

/**
 * Represent an oriented vector composed of two point in a three-dimensionnal space. The origin point is called proximal point, while the directionnal point is called distal.
 */
class Vector
{
public:
    /**
     * Create a null vector
     */
    Vector();
    
    /**
     * Create a direction vector pointing to the given point
     */
    Vector(Point distal);
    
    /**
     * Create a vector starting on the diven proximal point and pointing to the given distal point
     */
    Vector(Point proximal, Point distal);
    
    /**
     * Destroy the vector
     */
    ~Vector();
    
    /**
     * The directionnal point of the vector
     */
    Point distal() const;
    
    /**
     * The length of the vector
     */
    double length() const;
    
    /**
     * The origin point of the vector
     */
    Point proximal() const;
    
    /**
     * Set the directionnal point of the vector
     */
    void setDistal(Point distal);
    
    /**
     * Set the origin point of the vector
     */
    void setProximal(Point proximal);
    
private:
    Point _distal;
    Point _proximal;
};

#endif // VECTOR_H
