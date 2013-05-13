#ifndef ANGLE_H
#define ANGLE_H

#include "utils/vector.h"

/**
 * Represent an angle composed of two vectors one reference segment (the fixed vector) and one variable segment (the mobile vector).
 */
class Angle
{
public:
    /**
     * Create an angle with the given fixed vector as reference vector and the given mobile vector as branch vector
     */
    Angle(Vector fixed = Vector(), Vector mobile = Vector());
    
    /**
     * Destroy the angle
     */
    ~Angle();
    
    /**
     * The amplitude of the angle, in degrees
     */
    double amplitude() const;
    
    /**
     * The fixed vector of the angle
     */
    Vector fixed() const;
    
    /**
     * The mobile vector of the angle
     */
    Vector mobile() const;
    
    /**
     * Set the fixed vector of the angle
     */
    void setFixed(Vector first);
    
    /**
     * Set the mobile vector of the angle
     */
    void setMobile(Vector second);
    
private:
    Vector _fixed;
    Vector _mobile;
};

#endif // ANGLE_H
