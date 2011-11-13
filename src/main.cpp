/** 
 * @author Alberto Franco
 * @file   main.cpp
 * @brief  Contains program entry point.
 * 
 */
#include <iostream>
#include <cstdlib>

#include "configurationfactory.h"
#include "requestgenerator.h"
#include "workfunctionalgorithm.h"

const size_t PAGE_SIZE = 256u;

void printHelpMessage()
{
    std::cout << "Usage: work <k> <request count> [3 | 2]" << std::endl
              << "   <k> is the number of the k-server. It's number of server \n"
              << "       that you want to be used by the solver."
              << "   <request count> is a integer number and represent how \n"
              << "       many request you want to generate for work.\n"
              << "   [3 | 2] three or two dimensional point to deal with. All\n"
              << "       points are generated in the interval [-50.0, 50.0]";
}

int main(int argc, char **argv) 
{
    if(argc < 4) 
    {
        printHelpMessage();
        return 1;
    }
    
    // -- Process system parameters. -------------------------------------------
    size_t k            = std::atoi(argv[1]);
    size_t requestCount = std::atoi(argv[2]);
    size_t spaceSize    = std::atoi(argv[3]);
    
    //  -- Init the request generator, algorithm class and allocator -----------
    RequestGenerator generator(requestCount);
    ConfigurationFactory::get().initAllocationData(Point3(), k, PAGE_SIZE);
    Point3* origin = new Point3();
    WorkFunctionAlgorithm work(200.0, origin);
    
    // -- Print some message ---------------------------------------------------
    switch(spaceSize)
    {
        case 2:  std::cout << "Generating " << requestCount << " 2d requests..." 
                           << std::endl; break;
        case 3:  std::cout << "Generating " << requestCount << " 3d requests..." 
                           << std::endl; break;
        default: std::cout << "Error! - #" << spaceSize << " not supported" 
                           << std::endl; return 2;
    }
    
    // -- Start processing requests --------------------------------------------
    Point* req;
    for (size_t i = 0; i < requestCount; i++)
    {
        if (spaceSize == 2)
            req = generator.generatePoint2();
        else
            req = generator.generatePoint3();        
        
        work.processRequest(req);
        delete req;
    }
    
    delete origin;
    return 0;
}
