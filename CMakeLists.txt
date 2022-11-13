cmake_minimum_required(VERSION 3.5)

project(ArgParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(HEADERS
    include/argparser.hpp
    include/parseroption.hpp
)

set(SOURCE
    	src/argparser.cpp
    	src/parseroption.cpp
)

if(BUILD_SHARED_LIBS)
    add_library(${PROJECT_NAME} SHARED ${HEADERS} ${SOURCE})
else()
    add_library(${PROJECT_NAME} STATIC ${HEADERS} ${SOURCE})
endif()

target_include_directories(${PROJECT_NAME}
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER "${HEADERS}")


if(ARGPARSER_BUILD_TESTS)
    add_executable(ArgParserTest
	    test/test.cpp
    )
    target_link_libraries(ArgParserTest PRIVATE ${PROJECT_NAME})
endif()
