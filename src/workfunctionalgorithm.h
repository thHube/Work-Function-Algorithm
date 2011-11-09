/** 
 * @author Alberto Franco
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
    WorkFunctionAlgorithm(range_t = 100.0);
    
    //! Process a request
    void processRequest(Point* request);
    
private:
    Configuration*      _currentConf;  //!< Current server configuation
    std::vector<Point*> _requests;     //!< Request arrived at current point
    range_t             _limit;        //!< Superior limit for current request
    
    //! Calculate work function w(i, C)
    range_t work(size_t index, Configuration* conf);
    
    //! Calculate work function on first step w(1, C)
    range_t workOnFirst(Configuration* conf);  
    
    //! Update limit based on last request.
    void updateLimit();
    
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
    
    minDistance = (*it).distance(*_requests[0]);
    ++it;
    
    for (; it != conf->end(); ++it) 
    {
        actualDistance = (*it).distance(*_requests[0]);
        if (minDistance > actualDistance)
        {
            minDistance = actualDistance;
        }
    }
    return minDistance;
}

#endif // WORKFUNCTIONALGORITHM_H
