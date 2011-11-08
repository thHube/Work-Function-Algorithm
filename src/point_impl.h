/** 
 * @author Alberto Franco
 * @file   point_impl.h 
 * @brief  Contains the definition of the Point3 and Point2 classes. 
 * 
 */
#ifndef POINT_IMPL_H
#define POINT_IMPL_H

#include "point.h"

class Point2: virtual public Point
{
public:
    
    //! Default constructor + 2 overloads
    Point2(range_t x = 0.0, range_t y = 0.0);
    
    //! Move current point to the given one. 
    virtual void moveTo(const Point& other);
    
    //! Calculate the distance between two points. 
    virtual range_t distance(const Point& other);
    
    //! Tells if the points are the same. 
    virtual bool operator==(const Point& other) const; 
    
    //! Return point in a printable fromat.
    virtual std::string toString();
    
protected:
    
    //! Method for late initialization. Used instead of constructor for memory 
    //! optimization. 
    virtual void init();
    
    //! Copy constructor for late initialization. 
    virtual void copy(const Point& other);
    
private:
    range_t _x, _y;
};


class Point3: virtual public Point
{
public:
    
    //! Default constructor + 3 overloads
    Point3(range_t x = 0.0, range_t y = 0.0, range_t z = 0.0);
    
    //! Move current point to the given one. 
    virtual void moveTo(const Point& other);
    
    //! Calculate the distance between two points. 
    virtual range_t distance(const Point& other);
    
    //! Tells if the points are the same. 
    virtual bool operator==(const Point& other) const; 
    
    //! Return point in a printable fromat.
    virtual std::string toString();
    
protected:
    
    //! Method for late initialization. Used instead of constructor for memory 
    //! optimization. 
    virtual void init();
    
    //! Copy constructor for late initialization. 
    virtual void copy(const Point& other);
    
private:
    range_t _x, _y, _z;
};

////////////////////////////////////////////////////////////////////////////////
// -- INLINE METHODS -----------------------------------------------------------

// -- Point2 -------------------------------------------------------------------
/**
 * Create a new point with the given coordinates.
 * @param x X coordinate for the point 
 * @param y Y coordinate for the point 
 */
inline Point2::Point2(range_t x, range_t y): Point(), _x(x), _y(y) { }

/**
 * Move the point to the given one.
 * @param other The other point to compare.
 */
inline void Point2::moveTo(const Point& other)
{
    const Point2* ptr = dynamic_cast<const Point2*>(&other);
    if (ptr)
    {
        this->_x = ptr->_x;
        this->_y = ptr->_y;
    }
}

/**
 * Initialize the point into the origin (0, 0).
 */
inline void Point2::init()
{
    _x = _y = 0.0;
}

/**
 * Equality check.
 * @param other The point to compare with.
 */
inline bool Point2::operator==(const Point& other) const
{
    return false;
}

// -- Point3 -------------------------------------------------------------------
/**
 * Public contructor, initialize the point with the given coordinates
 * @param x X value coordinate.
 * @param y Y Value coordinate.
 * @param z Z value coordinate.
 */
inline Point3::Point3(range_t x, range_t y, range_t z): Point(), _x(x), _y(y), _z(z) { }

/**
 * Initialize the point into the origin.
 */
inline void Point3::init()
{
    _x = _y = _z = 0.0;
}

#endif // POINT_IMPL_H
