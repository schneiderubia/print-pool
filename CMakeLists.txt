cmake_minimum_required(VERSION 3.0)
project(print_pool)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 12.0)
#        message(FATAL_ERROR "GCC 12.0 ou superior eh necessário para usar <format>.")
#    endif()
#elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13.0)
#        message(FATAL_ERROR "Clang 13.0 ou superior eh necessário para usar <format>.")
#    endif()
#endif()

add_executable(print_pool main.cpp
        process.cpp
        process.h
        printer.cpp
        printer.h
        pool.cpp
        pool.h
        log.h
        printjob.h
)
