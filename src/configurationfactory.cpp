/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   configuationfactory.cpp
 * @brief  Contains the implementation of the ConfigurationFactory class.
 * 
 */
#include "configurationfactory.h"
#include <cstring>

////////////////////////////////////////////////////////////////////////////////
// -- STATIC AREA --------------------------------------------------------------
//! Initialization of the singleton instance.
ConfigurationFactory* ConfigurationFactory::_instance = NULL;

/**
 * Get method to access the configurationfactory object.
 * @return A reference to the only instance of the class.
 */
ConfigurationFactory& ConfigurationFactory::get()
{
    if (!_instance)
    {
        _instance = new ConfigurationFactory;
    }
    return *_instance;
}

/**
 * Release the singleton object. Delete all memory page allocated.
 */
void ConfigurationFactory::release()
{
    if (_instance) 
    {
        delete _instance;
    }
}
// -- END STATIC AREA ----------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////
/**
 * Initialize The factory.
 */
ConfigurationFactory::ConfigurationFactory()
{

}

/**
 * Deconstructor, deallocate all memory pages. 
 */
ConfigurationFactory::~ConfigurationFactory()
{   
    for (size_t i = 0; i < _allObj.size(); i++) 
    {
        std::free(&_allObj[i]);
    }
    delete[] _confInit;
}

/**
 * Initialize a configuration with k server in r_0.
 * @return the newly created configuration.
 */
Configuration* ConfigurationFactory::createInitialConfiguration()
{
    Configuration* conf = create();
    conf->init(*_origin, _confSize);
    return conf;
}

/**
 * Create a new object. It is not created if there are still object in the pool
 * else a memory page is allocated.
 * @return Object requested.
 */
Configuration* ConfigurationFactory::create()
{
    if (_availableObj.size() == 0)
    {
        allocatePage();
    }
    Configuration* element = _availableObj.top();
    _availableObj.pop();
    
    // -- Set the pointer to the preallocated Point array ----------------------
    element->_servers     = reinterpret_cast<Point*>(element + 1);
    element->_serverCount = _confSize;
    element->_pointSize   = _pointSize - sizeof(Point);

    char* aux = reinterpret_cast<char*>(element->_servers);
    // -- Size of point and calculated size of point are different -------------
    for (size_t i = sizeof(Point) * _confSize, j = 0; i < _confSize * _pointSize; j++)
    {
        // -- Start from the end of points and create a correct configuration --
        element->_servers[j]._coords = reinterpret_cast<range_t*>(aux + i);
        element->_servers[j].copy(*_origin);
        i += _pointSize - sizeof(Point);
    }
    
    return element;
}

/**
 * Put the object given in the available object pool.
 * @param conf The object to recycle.
 */
void ConfigurationFactory::recycle(Configuration* conf)
{
    _availableObj.push(conf);
}

