if(BUILD_STATIC)
    add_library(num_of_char STATIC src/num_of_char.c) 
elseif(BUILD_SHAERD)
    add_library(num_of_char SHAERD src/num_of_char.c) 
endif()

target_include_directories(num_of_char PUBLIC include)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
