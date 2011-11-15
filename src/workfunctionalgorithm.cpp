/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   workfunctionalgorithm.cpp
 * @brief  Contains the implementation of the WorkFunctionAlgorithm class.
 * 
 */
#include "workfunctionalgorithm.h"

#include <iostream>

/**
 * Initialize the algorithm allocating the initial configuration.
 * @param limit The superior limit for first iteration. Should be greater 
 * that the eligble space. 
 */
WorkFunctionAlgorithm::WorkFunctionAlgorithm(range_t limit, Point* origin)
{
    _currentConf = ConfigurationFactory::get().createInitialConfiguration();
    _limit = limit;
    _origin = origin;
}

/**
 * Process a request using the work function algorithm. 
 * @param request The request that has arrived. 
 */
void WorkFunctionAlgorithm::processRequest(Point* request)
{
    // -- Push back request and init variables ---------------------------------
    _requests.push_back(request);
    size_t t = _requests.size();
    range_t minDistance, actualDistance;
    Configuration::Iterator it, servant;
    Configuration* conf;
    minDistance = _limit;
    
    // -- Minimize distance work(t, conf) --------------------------------------
    for(it = _currentConf->begin(); it != _currentConf->end(); ++it)
    {
        std::cout << " - " << it.getServerNumber() << std::endl;
        conf = _currentConf->newFromSwap(it, *request);
        actualDistance = (*it).distance(*request);
        
        actualDistance += work(t - 1, conf, _limit + actualDistance, actualDistance);
        ConfigurationFactory::get().recycle(conf);
        
        if (actualDistance < minDistance)
        {
            minDistance = actualDistance;
            servant = it;
        }
    }
    // -- Update limit ---------------------------------------------------------
    updateLimit(*servant);
    
    // -- Update old configuration and recycle old -----------------------------
    Configuration* aux;
    conf = _currentConf->newFromSwap(servant, *request);
    aux = _currentConf;
    _currentConf = conf;
    ConfigurationFactory::get().recycle(aux);
    
    // -- Finally print what server has served the request ---------------------
    std::cout << "Request[" << t << "]: " << request->toString() << " served by #" 
              << servant.getServerNumber() << std::endl; 
}

/**
 * Work function implementation.
 * @param index Index to calculate the work function on
 * @param conf Current configuration
 */
range_t WorkFunctionAlgorithm::work(size_t index, Configuration* conf, 
                                    range_t upperBound, range_t partialSum)
{
    // -- If it is one, we process using utility function created. -------------
    if (index == 1) 
    {
        return workOnFirst(conf);
    } 
    else if (index == 0) 
    {
        return 0.0;
    }
    
    // -- Declarations ---------------------------------------------------------
    Configuration::Iterator it = conf->begin();
    range_t minDistance, actualDistance;
    Point& req = *_requests[index - 1];
    Configuration* swapped;
    minDistance = _limit;
    
    // -- The rest of the calculation ------------------------------------------
    for (; it != conf->end(); ++it)
    {
        swapped = conf->newFromSwap(it, req);
        actualDistance = (*it).distance(req);
        
        if (upperBound - partialSum < distanceFromOrigin(swapped))
        {
            continue;
        }
        
        actualDistance += work(index - 1, swapped, upperBound, partialSum + actualDistance);
        if (actualDistance < minDistance)
        {
            minDistance = actualDistance;
        }
        ConfigurationFactory::get().recycle(swapped);
    }
    // -- Return the min{ ... } calculated -------------------------------------
    return minDistance;
}

/**
 * Update the limit with previos move of the server.
 */
void WorkFunctionAlgorithm::updateLimit(Point& servant)
{
    Point* lastReq = _requests.back();
    _limit += lastReq->distance(servant);
}


