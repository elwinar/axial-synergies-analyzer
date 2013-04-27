#ifndef POINT_H
#define POINT_H

class Point
{
public:
    Point();
    Point(double x, double y, double z);
    ~Point();
    
    double x() const;
    void setX(double x);
    
    double y() const;
    void setY(double y);
    
    double z() const;
    void setZ(double z);
    
    Point operator+(Point const & operand) const;
    Point operator-(Point const & operand) const;
    
private:
    double _x;
    double _y;
    double _z;
};

#endif // POINT_H
