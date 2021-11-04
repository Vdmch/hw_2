add_library(num_of_char STATIC src/num_of_char.c) 

target_include_directories(num_of_char PUBLIC include)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
