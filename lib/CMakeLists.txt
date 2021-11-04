add_subdirectory(num_of_char)

if(BUILD_STATIC)
    add_subdirectory(static_lib)
elseif(BUILD_SHAERD)
    add_subdirectory(shared_lib)
endif()
