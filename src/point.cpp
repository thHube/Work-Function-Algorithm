/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   point.cpp
 * @brief  Contains the implementation of Point class. 
 * 
 */
#include "point.h"
#include <cmath>
#include <cstdio>

size_t Point::_pointSize = 3; //!< Initialization of the static member

/**
 * 
 */
Point::Point(range_t* initializer, bool copy)
{
    if (copy) init();
    if (initializer)
    {
        if (copy) 
        {
            for (size_t i = 0; i < _pointSize; i++)
            {
                _coords[i] = initializer[i];
            }
        }
        else
        {
            _coords = initializer;
        }
    }
    else 
    {
        for (size_t i = 0; i < _pointSize; i++)
        {
            _coords[i] = 0.0;
        }
    }
}

/**
 * Copy a point into current object.
 * @param other Point to copy into current
 */
void Point::copy(const Point& other)
{
    for (size_t i = 0; i < _pointSize; i++) 
    {
        _coords[i] = other._coords[i];
    }
}

/**
 * Calculate the distance between two points.
 * @param other The point to calculate the distance.
 * @return Calculated distance.
 */
range_t Point::distance(const Point& other)
{
    double dist = 0.0;
    double coord = 0.0;
    for (size_t i = 0; i < _pointSize; i++)
    {
        coord = _coords[i] - other._coords[i];
        dist += coord * coord;
    }
    return std::sqrt(dist);
}

/**
 * Initialize an empty point. Create a 
 */
void Point::init()
{
    _coords = new range_t[_pointSize];
}

/**
 * Convert current point to a string 
 * @return the string relative to current point. 
 */
std::string Point::toString()
{
    std::string ptString = "[";
    char buffer[256];
    for (size_t i = 0; i < _pointSize; i++) 
    {
        std::sprintf(buffer, "%f, ", _coords[i]);
        ptString += buffer;
    }
    return ptString + "]";
}

