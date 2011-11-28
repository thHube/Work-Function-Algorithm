/** 
 * @author Alberto Franco, Mirko Polato, Lorenzo Tessari
 * @file   requestgenerator.h
 * @brief  Contains the definition of RequestGenerator class.
 * 
 */
#ifndef REQUESTGENERATOR_H
#define REQUESTGENERATOR_H

#include "point.h"

#include <vector>
#include <ctime>
#include <cstdlib>

#ifdef _MSC_VER
    #include <random>
#endif

/**
 * 
 */
class RequestGenerator
{

public:     
    
    //! Init the request generator with the number of requests
    RequestGenerator(size_t requestCount);
    
    //! Force a particualr request generation
    void forceSpecialGeneration();
    
    //! Generate a two dimensional point.
    Point* generatePoint();
    
private:
    size_t   _counter;  //!< Counter of how may request have been generated.
    size_t   _randSeed; //!< Random seed
    
    std::vector<Point>           _requestPoints; //!< Used for special requests 
    std::vector<Point>::iterator _pointIterator; //!< Iterator to generate point
    
    
#ifdef _MSC_VER 
    std::mt19937 _generator;
#endif 

    static range_t MAX_RANDOM;   //! Random number pitch
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
#ifdef _MSC_VER // -- Using features from TR1 
    std::uniform_real_distribution<> dist(-50.0, 50.0);
    double f = dist(_generator);
#else
    std::srand(_randSeed);
    double f = (double)std::rand() / RAND_MAX;
    f = f * MAX_RANDOM - RAND_OFFSET;
    _randSeed += 1;
#endif
    return f; 
}


#endif // REQUESTGENERATOR_H
