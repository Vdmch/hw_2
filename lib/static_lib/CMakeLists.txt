add_library(static_lib src/static_lib.c) 

target_include_directories(static_lib PUBLIC include)
target_link_libraries(static_lib num_of_char)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
