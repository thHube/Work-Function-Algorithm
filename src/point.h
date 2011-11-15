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
    
    //! Virtual Deconstructor.
    virtual ~Point() { }
    
    //! Move current point to the given one. 
    virtual void moveTo(const Point& other) = 0;
    
    //! Calculate the distance between two points. 
    virtual range_t distance(const Point& other) = 0;
    
    //! Tells if the points are the same. 
    virtual bool operator==(const Point& other) const = 0; 
    
    //! Return point in a printable fromat.
    virtual std::string toString() = 0;
    
protected:
    
    //! Method for late initialization. Used instead of constructor for memory 
    //! optimization. 
    virtual void init() = 0;
    
    //! Copy constructor for late initialization. 
    virtual void copy(const Point& other) = 0;
};

#endif // POINT_H
