#ifndef POINT_H
#define POINT_H

/**
 * Represent a position in a three-dimensionnal space.
 */
class Point
{
public:
    /**
     * Create a point with given x, y and z coordinates
     */
    Point(double x = 0, double y = 0, double z = 0);
    
    /**
     * Destroy the point
     */
    ~Point();
    
    /**
     * Set the x component of the point
     */
    void setX(double x);
    
    /**
     * Set the y component of the point
     */
    void setY(double y);
    
    /**
     * Set the z component of the point
     */
    void setZ(double z);
    
    /**
     * The x component of the point
     */
    double x() const;
    
    /**
     * The y component of the point
     */
    double y() const;
    
    /**
     * The z component of the point
     */
    double z() const;
    
    /**
     * Operator to add a point to another
     */
    Point operator+(Point const & operand) const;
    
    /**
     * Operator to subtract a point to another
     */
    Point operator-(Point const & operand) const;
    
private:
    double _x;
    double _y;
    double _z;
};

#endif // POINT_H
