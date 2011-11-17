/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   workfunctionalgorithm.h 
 * @brief  Contains the definition of the WorkFunctionAlgorithm class.
 * 
 */
#ifndef WORKFUNCTIONALGORITHM_H
#define WORKFUNCTIONALGORITHM_H

#include <vector>

#include "defs.h"
#include "point.h"
#include "configuration.h"
#include "configurationfactory.h"

class WorkFunctionAlgorithm
{

public:
    
    //! Public constructor
    WorkFunctionAlgorithm(range_t, Point*);
    
    //! Process a request
    void processRequest(Point* request);
    
private:
    Configuration*      _currentConf;  //!< Current server configuation
    std::vector<Point*> _requests;     //!< Request arrived at current point
    range_t             _limit;        //!< Superior limit for current request
    Point*              _origin;       //!< Initial server position
    
    //! Calculate work function w(i, C)
    range_t work(size_t index, Configuration* conf, range_t up, range_t part);
    
    //! Calculate work function on first step w(1, C)
    range_t workOnFirst(Configuration* conf);  
    
    //! Update limit based on last request.
    void updateLimit(Point& s);
    
    //! Calculate the distance from the origin of the actual configuation
    range_t distanceFromOrigin(Configuration* conf);
    
};

/**
 * Calculate work function on first request given the configuration. 
 * This is implemented to give the actual algorithm more order. 
 * We calculate the work fun on r_1 because we know that w(0, r_0) == 0.
 * @param conf The actual configuation to minimize.
 */
inline range_t WorkFunctionAlgorithm::workOnFirst(Configuration* conf)
{
    Configuration::Iterator it = conf->begin();
    range_t minDistance, actualDistance;
    
    minDistance = _requests[0]->distance(*it);
    ++it;
    
    for (; it != conf->end(); ++it) 
    {
        actualDistance = _requests[0]->distance(*it);
        if (minDistance > actualDistance)
        {
            minDistance = actualDistance;
        }
    }
    return minDistance;
}

/**
 * Calculate the distance from the initial configuation of the given configuation
 * @param conf Actual configuration to calculate 
 * @return Calculated distance 
 */
inline range_t WorkFunctionAlgorithm::distanceFromOrigin(Configuration* conf)
{
    Configuration::Iterator it = conf->begin();
    range_t distance = 0.0;
    for (; it != conf->end(); ++it)
    {
        distance += _origin->distance(*it);
    }
    return distance;
}


#endif // WORKFUNCTIONALGORITHM_H
