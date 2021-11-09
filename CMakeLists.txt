cmake_minimum_required(VERSION 3.14)
project(basic_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

if(CMAKE_BUILD_TYPE=Debug)
    add_compile_options(-g)
elseif(CMAKE_BUILD_TYPE=Release)
    add_compile_options(-O3)
endif()

add_compile_options(-Wall -Wextra -Wpadded -pedantic)

if(WITH_COVERAGE)
    add_compile_options(--coverage)
    add_link_options(--coverage)
endif()

if(WITH_ANALYSERS)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
    include(cmake_files/analysers.cmake)
endif()

if(WITH_TESTS OR WITH_SANITIZERS OR WITH_COVERAGE OR WITH_VALGRIND)
    find_package(GTest REQUIRED)
    enable_testing()
    set(BUILD_TESTS 1)
endif()


if(BUILD_LIB)
    set(BUILD_SHARED 1)
else()
    add_executable(main src/main.c)
endif()

add_subdirectory(lib)

if(BUILD_SHARED AND NOT BUILD_LIB)
    find_package(shared_lib CONFIG REQUIRED)
    target_link_libraries(main Shared_Lib::shared_lib)
elseif(NOT BUILD_LIB)
    set(BUILD_STATIC 1)
    target_link_libraries(main static_lib) 
endif()
