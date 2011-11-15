/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   requestgenerator.cpp
 * @brief  Contains the implementation of RequestGenerator class.
 * 
 */
#include "requestgenerator.h"

range_t RequestGenerator::MAX_RANDOM  = 100.0;
range_t RequestGenerator::RAND_OFFSET = 50.0;

/**
 * Initialize the Request Generator 
 */
RequestGenerator::RequestGenerator(size_t reqCount): 
    _counter(reqCount), _randSeed(std::time(NULL)) { }

/**
 * Generate a random 2d point in space.
 * @return the generated point.
 */     
Point2* RequestGenerator::generatePoint2()
{
    return new Point2(random(), random());
}

/**
 * Generate a random 3d point in our eligible space.
 * @return the new generated request.
 */
Point3* RequestGenerator::generatePoint3()
{
    return new Point3(random(), random(), random());
}



