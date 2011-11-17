/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   point_impl.cpp
 * @brief  Contains the implementation of Point3 and Point2 classes. 
 * 
 */
#include "point_impl.h"

#include <string>
#include <cstdio>
#include <cmath>
#include <typeinfo>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// -- POINT2 -------------------------------------------------------------------

/**
 * 
 */
void Point2::copy(const Point& other)
{
    const Point2* ptr = reinterpret_cast<const Point2*>(&other);
    if (ptr)
    {
        this->_x = ptr->_x; 
        this->_y = ptr->_y;
        return;
    }
    throw std::bad_cast();
}

/**
 * Calculate the distance between two points. 
 * @param other Other point 
 * @return 
 */
range_t Point2::distance(const Point& other)
{
    const Point2* ptr = reinterpret_cast<const Point2*>(&other);
    if (ptr)
    {
        range_t distSquared = (ptr->_x - _x) * (ptr->_x - _x);
        distSquared += (ptr->_y - _y) * (ptr->_y - _y);
        return std::sqrt(distSquared);
    }
    throw std::bad_cast();
}

/**
 * toString() method.
 * @return a string depicting the point.
 */
std::string Point2::toString()
{
    using namespace std;
    
    char buffer[256];
    sprintf(buffer, "(%f ,%f)", _x, _y);
    
    return string(buffer);
}


// -- END POINT2 ---------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
// -- POINT3 -------------------------------------------------------------------

/**
 * Copy the given point into current.
 * @param other The point to copy.
 */
void Point3::copy(const Point& other)
{
    // const Point3* ptr = reinterpret_cast<const Point3*>(&other);
    const Point3* ptr = (const Point3*)((char*)&other);
    if (ptr)
    {
        this->_x = ptr->_x;
        this->_y = ptr->_y;
        this->_z = ptr->_z;
        return;
    }
    std::cout << "Point3::copy error! " << std::endl;
    throw std::bad_cast();
}

/**
 * Claculate the distance between two points.
 * @param other The point to calculate the distance to.
 * @return The distance between the two.
 */
range_t Point3::distance(const Point& other)
{
    // const Point3* ptr = reinterpret_cast<const Point3*>(&other);
    const Point3* ptr = (const Point3*)((char*)&other);
    if (ptr)
    {
        range_t squareDistance = (ptr->_x - _x) * (ptr->_x - _x);
        squareDistance += (ptr->_y - _y) * (ptr->_y - _y);
        squareDistance += (ptr->_z - _z) * (ptr->_z - _z);
        return std::sqrt(squareDistance);
    }
    std::cout << "Point3::distance error!" << std::endl;
    throw std::bad_cast();
}

/**
 * 
 */
void Point3::moveTo(const Point& other)
{
    const Point3* ptr = reinterpret_cast<const Point3*>(&other);
    if (ptr)
    {
        _x = ptr->_x;
        _y = ptr->_y;
        _z = ptr->_z;
        return;
    }
    std::cout << "Point3::moveTo error!" << std::endl;
    throw std::bad_cast();
}

/**
 * Equality check.
 */ 
bool Point3::operator==(const Point& other) const
{
    return false;
}

/**
 * Convert the point into a string. 
 * @return the string descibing current point.
 */
std::string Point3::toString()
{
    using namespace std;
    
    char buffer[256];
    sprintf(buffer, "(%f ,%f, %f)", _x, _y, _z);
    
    return string(buffer);
}

// -- END POINT3 ---------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
