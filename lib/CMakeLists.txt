add_subdirectory(num_of_char)

if(BUILD_STATIC)
    add_subdirectory(static_lib)
endif()

if(BUILD_SHARED)
    add_subdirectory(shared_lib)
endif()
