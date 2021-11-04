set(LIB_SOURCES src/shared_lib.c)
set(PUB_HEADERS include/count_series.h)

add_library(shared_lib SHARED ${LIB_SOURCES})
target_link_libraries(shared_lib $<BUILD_INTERFACE:num_of_char>)

install(TARGETS shared_lib EXPORT shared_lib_Targets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        INCLUDES DESTINATION include)
    
install(FILES ${PUB_HEADERS} DESTINATION include)
install(EXPORT shared_lib_Targets
        FILE shared_libConfig.cmake
        NAMESPACE Shared_Lib::
        DESTINATION lib/cmake/Shared_Lib)

if(BUILD_TESTS)
    add_subdirectory(tests)
endif()
