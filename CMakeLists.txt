cmake_minimum_required(VERSION 3.5)

project(ArgParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

set(SOURCE
        include/argparser.hpp
    	src/argparser.cpp

    	include/parseroption.hpp
    	src/parseroption.cpp
)

if(BUILD_SHARED_LIBS)
    add_library(ArgParser SHARED ${SOURCE})
else()
    add_library(ArgParser STATIC ${SOURCE})
endif()

if(ARGPARSER_BUILD_TESTS)
    add_executable(Test
	    test/test.cpp
    )
    target_link_libraries(Test PRIVATE ArgParser)
endif()
