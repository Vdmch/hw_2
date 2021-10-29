add_library(users src/get_series.c) 

target_include_directories(users PUBLIC include)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
