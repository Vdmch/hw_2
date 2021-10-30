cmake_minimum_required(VERSION 3.14)
project(basic_test)

set (CMAKE_CXX_STANDARD 17)
set (CMAKE_C_STANDARD 11)

add_compile_options(-Wall -Wextra -pedantic)

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
    set(BUILD_TESTS ON)
endif()

add_subdirectory(lib)

add_executable(main src/main.c)
target_link_libraries(main static_lib)
