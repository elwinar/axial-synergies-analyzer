#ifndef ANGLE_H
#define ANGLE_H

#include "utils/vector.h"

/**
 * Represent an angle composed of two vectors one reference segment (the fixed vector) and one variable segment (the mobile vector).
 */
class Angle
{
public:
    Angle();
    Angle(Vector fixed, Vector mobile);
    
    ~Angle();
    
    Vector fixed() const;
    void setFixed(Vector first);
    
    Vector mobile() const;
    void setMobile(Vector second);
    
    double amplitude() const;
    
private:
    Vector _fixed;
    Vector _mobile;
};

#endif // ANGLE_H
