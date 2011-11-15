/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   configuation.h 
 * @brief  Contains the definition of the Configuration class.
 * 
 */
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "point.h"

//! Forward declaration for friendship.
class ConfigurationFactory;

//! Exception declaration for out of bound iterators
class IteratorOutOfBound { };

/**
 * 
 */
class Configuration
{
    friend class ConfigurationFactory;
    
public:
    
    /**
     * 
     */
    class Iterator 
    {
        //! Standard C++ does not automatically defines inner class as friends.
        friend class Configuration;
        
    public: 
        
        //! Unequality check. To see if we are at the end.
        bool operator!=(const Iterator& it) const;
        
        //! Increment operator to cycle through the data sturcture.
        Iterator& operator++();
        
        //! Dereferencing operator to access data. 
        Point& operator*() throw(IteratorOutOfBound);
        
        //! Return the server number of the current iterator
        size_t getServerNumber() const { return _index; } 
        
    private:
        
        size_t         _index;    //!< Index of the point this iterator
        Configuration* _outerPtr; //!< 
        
    }; friend class Iterator; //!< same as before.
    
    //! Check equality between two configurations.
    bool operator==(const Configuration& other) const;
    
    //! First element of the data structure. 
    Iterator begin();
    
    //! Last + 1 element of the data structure. Does not hold any valid element
    Iterator end();
    
    //! Create a new configuation replacing (*it) with point
    Configuration* newFromSwap(const Iterator& it, const Point& point);
    
    //! Return configuration size
    size_t size();
    
private:
    
    Point* _servers;     //!< Position of the k servers.
    size_t _serverCount; //!< Count of the servers.
    size_t _pointSize;   //!< Size of the point type in B.
    
    //! Block construction of the objects.
    Configuration() { }
    
    //! Block also dellocation of objects.
    ~Configuration() { }
    
    //! Initialize the configuration from the given point. 
    void init(const Point& origin, size_t serverCount);
};

/**
 * Getter for server count field
 * @return the size in number of servers of the configuration.
 */
inline size_t Configuration::size()
{
    return _serverCount;
}

#endif // CONFIGURATION_H
