/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   point.h 
 * @brief  Contains the definition of the Point interface. 
 * 
 */
#ifndef POINT_H
#define POINT_H

#include "defs.h"
#include <string>

//! Forward declarations for friendship.
class Configuration;
class ConfigurationFactory;

/**
 * Point define a class implementation template for metric space points. 
 * Points that implement this interface must take care that if d(a, b) is 
 * the distance between point 'a' and point 'b' so:
 *   1. d(a, b) = d(b, a)
 *   3.
 *   2. d(a, b) + d(b, c) >= d(a, c)
 */
class Point
{
    friend class Configuration;
    friend class ConfigurationFactory;
    
public:
    
    //! Set the size of the point (class-wide)
    static void setPointSize(size_t size) { _pointSize = size; }
    
    //! Get the size of the point.
    static size_t getPointSize() { return _pointSize; }
    
    //! Return the dimension in bytes of the point type.
    static size_t getObjectSize() { return sizeof(range_t) * _pointSize +  sizeof(Point); }
    
    //! Create a new point with the given initializer.
    Point(range_t* initializer = NULL, bool copy = true);
    
    //! Calculate the distance between two points. 
    range_t distance(const Point& other);
    
    //! Return point in a printable fromat.
    std::string toString();
    
    //! Deallocate coordinates array 
    void dealloc();

private:
    
    static size_t       _pointSize;     //!< Dimension of the point.
    range_t*            _coords;        //!< Coordinates of the point
    
    //! Method for late initialization. Used instead of constructor for memory 
    //! optimization. 
    void init();
    
    //! Copy constructor for late initialization. 
    void copy(const Point& other);
};

/**
 * Deallocate coordinates of the current point 
 */
inline void Point::dealloc() 
{
    delete[] _coords;
}

#endif // POINT_H
