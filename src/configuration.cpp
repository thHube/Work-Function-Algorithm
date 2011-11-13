/** 
 * @author Alberto Franco
 * @file   configuration.cpp
 * @brief  Contains the implementation of the Configuration class.
 * 
 */
#include "configuration.h"
#include "configurationfactory.h"

#include <cstring>

#include <iostream> 
#include "point_impl.h"

////////////////////////////////////////////////////////////////////////////////
//-- ITERATOR ------------------------------------------------------------------

/**
 * Compare the iterator given with the other one. 
 * @param it Iterator to compare with.
 * @return True iff the two iterators reference the same server of the same 
 *         configuration, false else.
 */
bool Configuration::Iterator::operator!=(const Configuration::Iterator& it) const
{
    return (it._index != this->_index) && (it._outerPtr == this->_outerPtr);
}

/**
 * Iterators refernce servers in configurations. This operator let us access
 * those servers. Use it as usual ptr dereferencing.
 * @return A reference to current server.
 * @throw  IteratorOutOfBound If the current accesed item does not exists.
 */
Point& Configuration::Iterator::operator*() throw(IteratorOutOfBound)
{
    if (_index < _outerPtr->_serverCount)
    {
        // _outerPtr->_servers + _index;
        char* auxPtr = reinterpret_cast<char*>(_outerPtr->_servers);
        auxPtr += _index * _outerPtr->_pointSize;
        return *reinterpret_cast<Point*>(auxPtr);
    }
    throw IteratorOutOfBound();
}

/**
 * Move reference iterator to next server in the configuration.
 * @return A reference to current iterator. 
 */
Configuration::Iterator& Configuration::Iterator::operator++()
{
    _index += 1;
    return *this;
}
//-- END ITERATOR --------------------------------------------------------------
////////////////////////////////////////////////////////////////////////////////

/**
 * Return the first element of the collection. Used to easily loop through
 * the configuration without problems of messing things up. 
 * @return Iteartor referencing the first element of the configuration.
 */
Configuration::Iterator Configuration::begin() 
{
    Iterator it;
    
    it._index    = 0;
    it._outerPtr = this;
    
    return it;
}

/**
 * Return the last +1 element. Used to stop looping, comparison between 
 * iterators is also given, you may use these operators as in the stl.
 * @return The last + 1 element of the collection
 */
Configuration::Iterator Configuration::end() 
{
    Iterator it;
    
    it._index = _serverCount;
    it._outerPtr = this;
    
    return it;
}

/**
 * We suppose at this point to have all the memory allocated for servers and 
 * we just initialize all the data. 
 * @param origin
 */
void Configuration::init(const Point& origin, size_t serverCount)
{
    _serverCount = serverCount;
    
    Point* iter  = _servers;
    char* auxPtr = reinterpret_cast<char*>(iter);
    for (size_t i = 0; i < serverCount; i++) 
    {
        iter = reinterpret_cast<Point*>(auxPtr);
        iter->copy(origin);
        auxPtr += _pointSize;
    }
}

/**
 * Return a new configuration obtained swapping it with the given point.
 * @param it The server to move.
 * @param point The point to move the server to.
 * @return Newly created configuration.
 */
Configuration* Configuration::newFromSwap(const Configuration::Iterator& it, const Point& point)
{
    Configuration* neoConf = ConfigurationFactory::get().create();
    Point* iterator = neoConf->_servers;
    char* auxPtr = reinterpret_cast<char*>(iterator) + it._index * _pointSize;
    
    // -- Copy memory and substitute the point ---------------------------------
    iterator = reinterpret_cast<Point*>(auxPtr);
    std::memcpy(neoConf->_servers, _servers, _pointSize * _serverCount);
    iterator->copy(point);
    
    return neoConf;
}

/**
 * @param other 
 * @return 
 */
bool Configuration::operator==(const Configuration& other) const
{
    /// TODO Implement this method.
    return false;
}
