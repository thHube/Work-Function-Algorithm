/**
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   configuationfactory.h
 * @brief  Contains the definition of the ConfigurationFactory class.
 *
 */
#ifndef CONFIGURATIONFACTORY_H
#define CONFIGURATIONFACTORY_H

#include <vector>
#include <stack>
#include <cstdlib>

#include "configuration.h"

/**
 *
 */
class ConfigurationFactory
{

public:

    //! Singleton access method.
    static ConfigurationFactory& get();

    //! Release the allocator.
    static void release();

    //! Initialize the allocation data with the given.
    template<typename point_type>
    void initAllocationData(point_type origin, size_t serverCount, size_t pageSize);

    //! Create an initial configuration for k-server problem.
    Configuration* createInitialConfiguration();

    //! Return a new configuration
    Configuration* create();

    //! Recycle old configurations. Must call this to deallocate configuration
    void recycle(Configuration* conf);

private:
    // -- Singleton data -------------------------------------------------------
    static ConfigurationFactory* _instance;     //!< Singleton instance
    // -- Memory management data -----------------------------------------------
    std::stack <Configuration*>  _availableObj; //!< Available object pool
    std::vector<Configuration*>  _allObj;       //!< All object reference
    // -- Configuration infos --------------------------------------------------
    size_t                       _confSize;     //!< Configuration size
    size_t                       _pointSize;    //!< Point data type size;
    size_t                       _objPerPage;   //!< Number of objects per page.
    size_t                       _PAGE_SIZE;    //!< Page size in bytes
    Point*                       _origin;       //!< Point origin to init r_0
    void*                        _confInit;     //!< An example initial conf 

    //! Defaul constructor initialize everthing.
    ConfigurationFactory();

    //! Block copy construction not to break singleton access.
    ConfigurationFactory(const ConfigurationFactory& other) { }

    //! Destruction can be done only internally
    ~ConfigurationFactory();

    //! Allocate a new memory page to use with the
    void allocatePage();
};

/**
 * Initialize the allocation data to create configuration with.
 * @param origin The point that we want to become the origin. Must be
 *               point_type > Point
 * @param serverCount Number of server to create in each request.
 * @param pageSize Number of object to store in a page.
 */
template <typename point_type> inline void
ConfigurationFactory::initAllocationData(point_type origin, size_t serverCount, size_t pageSize)
{
    _confSize   = serverCount;
    _pointSize  = sizeof(point_type);
    _objPerPage = pageSize;

    _PAGE_SIZE = (_pointSize * _confSize + sizeof(Configuration)) * _objPerPage;

    _origin    = new point_type;
    _confInit  = new point_type[_confSize];
    _origin->copy(origin);
    
    allocatePage();
}

/**
 * Allocate a page of memory with '_objPerPage' objects. The page will be
 * deallocated at the end, when deconstructor is called.
 */
inline void ConfigurationFactory::allocatePage()
{
    Configuration* page = reinterpret_cast<Configuration*>(std::malloc(_PAGE_SIZE));
    size_t objSize = _pointSize * _confSize + sizeof(Configuration);
    
    // Push back the page.
    _allObj.push_back(page);
    
    char* ptr = reinterpret_cast<char*>(page);
    for (size_t i = 0; i < _objPerPage; i++)
    {
        _availableObj.push(page);
        ptr = ptr + objSize;
        page = reinterpret_cast<Configuration*>(ptr);
    }
}

#endif // CONFIGURATIONFACTORY_H
