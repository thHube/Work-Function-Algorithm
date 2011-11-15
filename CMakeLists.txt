# ---------------------------------------------------------------------------- #
# -- Work Function Algorithm implementation in C++                          -- #
# -- author: Alberto Franco, Mirko Polato, Lorenzo Tessari                  -- #
# -- file:   CMakeList.txt                                                  -- #
# -- brief:  Makefile for the project. We use CMake project manager.        -- # 
# ---------------------------------------------------------------------------- #
project(approxalgorithms)
cmake_minimum_required(VERSION 2.6)

# -- Target sources for the project --
set(TARGET_SRC 
"src/main.cpp"                  #! Entry point 
"src/configuration.cpp"         #! Class Configuration
"src/configurationfactory.cpp"  #! Class ConfigurationFactory
"src/workfunctionalgorithm.cpp" #! Class WorkFunctionAlgorithm
"src/requestgenerator.cpp"      #! Class RequestGenerator
"src/point_impl.cpp")           #! Class Point3 and Point2

# -- Target name for the project --
set(EXEC_NAME "work") 

# -- Compilation directive --
add_executable(${EXEC_NAME} ${TARGET_SRC})
