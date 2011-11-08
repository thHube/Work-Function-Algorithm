/** 
 * @author Alberto Franco
 * @file   workfunctionalgorithm.cpp
 * @brief  Contains the implementation of the WorkFunctionAlgorithm class.
 * 
 */
#include "workfunctionalgorithm.h"

#include <iostream>

/**
 * Initialize the algorithm allocating the initial configuration.
 */
WorkFunctionAlgorithm::WorkFunctionAlgorithm()
{
    _currentConf = ConfigurationFactory::get().createInitialConfiguration();
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
    Configuration::Iterator it = _currentConf->begin();
    Configuration::Iterator servant = it;
    
    // -- Calculate the first minimum iteration --------------------------------
    Configuration* conf = _currentConf->newFromSwap(it, *request);
    minDistance = work(t - 1, conf) + (*it).distance(*request);
    ConfigurationFactory::get().recycle(conf);
    
    ++it;
    
    // -- Minimize distance work(t, conf) --------------------------------------
    for(; it != _currentConf->end(); ++it)
    {
        conf = _currentConf->newFromSwap(it, *request);
        
        actualDistance = work(t - 1, conf) + (*it).distance(*request);
        ConfigurationFactory::get().recycle(conf);
        
        if (actualDistance < minDistance)
        {
            minDistance = actualDistance;
            servant = it;
        }
    }
    
    // -- Update old configuration and recycle old -----------------------------
    Configuration* aux;
    conf = _currentConf->newFromSwap(servant, *request);
    aux = _currentConf;
    _currentConf = conf;
    ConfigurationFactory::get().recycle(aux);
    
    // -- Finally print what server has served the request ---------------------
    std::cout << "\nRequest[" << t << "]: " << request->toString() << " served by #" 
              << servant.getServerNumber() << std::endl; 
}

/**
 * Work function implementation.
 * @param index Index to calculate the work function on
 * @param conf Current configuration
 */
range_t WorkFunctionAlgorithm::work(size_t index, Configuration* conf)
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
    
    // -- First work function calculation --------------------------------------
    Configuration* swapped = conf->newFromSwap(it, req);
    minDistance = work(index - 1, swapped) + (*it).distance(req);
    ConfigurationFactory::get().recycle(swapped);
    
    // -- The rest of the calculation ------------------------------------------
    for (; it != conf->end(); ++it)
    {
        swapped = conf->newFromSwap(it, req);
        actualDistance = work(index - 1, swapped) + (*it).distance(req);
        if (actualDistance < minDistance)
        {
            minDistance = actualDistance;
        }
        ConfigurationFactory::get().recycle(swapped);
    }
    // -- Return the min{ ... } calculated -------------------------------------
    return minDistance;
}

