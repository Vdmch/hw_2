add_subdirectory(num_of_char)

if(BUILD_SHARED)
    add_subdirectory(shared_lib)
else()
    add_subdirectory(static_lib)
endif()

