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
 * Generate a random point in space.
 * @return the generated point.
 */     
Point* RequestGenerator::generatePoint()
{
    range_t* point = new range_t[Point::getPointSize()];
    Point* newPt;
    
    for (size_t i = 0; i < Point::getPointSize(); i++)
    {
        point[i] = random();
    }
    newPt = new Point(point);
    delete[] point;
    
    return newPt;
}

