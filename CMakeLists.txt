# in the name of Allah

cmake_minimum_required(VERSION 3.8)
project(framework)

find_package(Boost COMPONENTS system thread regex filesystem)
if (Boost_FOUND)   
    include_directories(${Boost_INCLUDE_DIR})
    # link_directories(${Boost_LIBRARY_DIR})
    add_executable(${PROJECT_NAME} main.cpp framework.hpp)
    target_link_libraries(${PROJECT_NAME} pthread ${Boost_LIBRARIES})
    message(${Boost_INCLUDE_DIR})
endif()
