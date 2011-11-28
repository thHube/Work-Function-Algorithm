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
 * Force request generator to generate requests from the given vector of points
 */
void RequestGenerator::forceSpecialGeneration()
{
    Point::setPointSize(2);
    range_t requestPoints[] = {
       5.0,  5.0, // -- Upper right
       5.0, -5.0, // -- Lower right
      -5.0, -5.0, // -- Lower left
      -5.0,  5.0  // -- Upper left
    };
    
    // -- Push back all points where to perform requests -----------------------
    _requestPoints.push_back(Point(requestPoints));
    _requestPoints.push_back(Point(requestPoints + 2));
    _requestPoints.push_back(Point(requestPoints + 4));
    _requestPoints.push_back(Point(requestPoints + 6));
    
    // -- Init iterator --------------------------------------------------------
    _pointIterator = _requestPoints.begin();
}
 
/**
 * Generate a random point in space.
 * @return the generated point.
 */     
Point* RequestGenerator::generatePoint()
{
    range_t* point = new range_t[Point::getPointSize()];
    Point* newPt;
    
    if (_requestPoints.empty()) 
    {
        for (size_t i = 0; i < Point::getPointSize(); i++)
            point[i] = random();
        
        newPt = new Point(point);
        delete[] point;
    }
    else
    {
        newPt = new Point;
        newPt->copy(*_pointIterator);
        _pointIterator++;
        if (_pointIterator == _requestPoints.end()) 
        {
            _pointIterator = _requestPoints.begin();
        }
    }
    return newPt;
}

