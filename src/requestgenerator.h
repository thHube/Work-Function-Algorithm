/** 
 * @author Alberto Franco
 * @file   requestgenerator.h
 * @brief  Contains the definition of RequestGenerator class.
 * 
 */
#ifndef REQUESTGENERATOR_H
#define REQUESTGENERATOR_H

#include "point_impl.h"

#include <ctime>
#include <cstdlib>

/**
 * 
 */
class RequestGenerator
{

public:     
    
    //! Init the request generator with the number of requests
    RequestGenerator(size_t requestCount);
    
    //! Generate a two dimensional point.
    Point2* generatePoint2();
    
    //! Generate a three dimensional point
    Point3* generatePoint3();
    
private:
    size_t _counter;  //!< Counter of how may request have been generated.
    size_t _randSeed; //!< Random seed
    
    static range_t MAX_RANDOM;   //! Pitch random number
    static range_t RAND_OFFSET;  //! Offset of the random
    
    //! Generate a random number. 
    range_t random(); 
};

/**
 * Generate random number in our space.
 * @return the random number generated.
 */
inline range_t RequestGenerator::random()
{
    std::srand(_randSeed);
    _randSeed += 1;
    double f = (double)std::rand() / RAND_MAX;
    return f * MAX_RANDOM - RAND_OFFSET; 
}


#endif // REQUESTGENERATOR_H
