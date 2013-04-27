#ifndef ANGLE_H
#define ANGLE_H

#include "utils/vector.h"

class Angle
{
public:
    Angle();
    Angle(Vector first, Vector second);
    ~Angle();
    
    Vector first() const;
    void setFirst(Vector first);
    
    Vector second() const;
    void setSecond(Vector second);
    
    double amplitude() const;
    
private:
    Vector _first;
    Vector _second;
};

#endif // ANGLE_H
