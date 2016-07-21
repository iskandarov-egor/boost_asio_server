cmake_minimum_required(VERSION 2.8)

set(SOURCES acceptor_loop.cpp config.cpp file_serving.cpp logger.cpp main.cpp)

add_executable(final ${SOURCES})
find_package( Boost COMPONENTS system REQUIRED ) #whatever libs you need
include_directories( ${Boost_INCLUDE_DIRS} )
find_package( Threads )
set(CMAKE_EXE_LINKER_FLAGS "-lboost_system -lpthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set( LIBS_TO_LINK
    ${Boost_LIBRARIES}
    ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries( final
    ${LIBS_TO_LINK}
)