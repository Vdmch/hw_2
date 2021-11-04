################################
# GTest
################################

# Исходник тестирования
set(test_files src/test_func.cpp)
include_directories(test_files PUBLIC include)
set(target_lib num_of_char)
set(tests_name num_of_char_test)

# Тесты
option(WITH_SANITIZERS "Add sanitizers")
if(WITH_SANITIZERS)
    # Добавление тестов с санитайзерами undefined, leak и address
    add_executable(${tests_name}_addr ${test_files})
    target_link_libraries(${tests_name}_addr PUBLIC ${target_lib} GTest::Main)

    add_test(NAME ${tests_name}_addr COMMAND ${tests_name}_addr)    
    target_compile_options(${tests_name}_addr PUBLIC -O0 -g -static-libasan -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=leak -fsanitize=address)
    target_link_options(${tests_name}_addr PUBLIC -static-libasan -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=leak -fsanitize=address)

    # Добавление тестов с санитайзером thread
    add_executable(${tests_name}_thread ${test_files})
    target_link_libraries(${tests_name}_thread PUBLIC ${target_lib} GTest::Main)
    
    add_test(NAME ${tests_name}_thread COMMAND ${tests_name}_thread)
    target_compile_options(${tests_name}_thread PUBLIC -fno-omit-frame-pointer -O0 -g -static-libasan -fsanitize=thread)
    target_link_options(${tests_name}_thread PUBLIC -fno-omit-frame-pointer -static-libasan -fsanitize=thread)
endif()

if(WITH_COVERAGE)
    # Добавление тестов для оценки покрытия
    add_executable(${tests_name} ${test_files})
    target_link_libraries(${tests_name} PUBLIC ${target_lib} GTest::Main)

    add_test(NAME ${tests_name} COMMAND ${tests_name})    
    target_compile_options(${tests_name} PUBLIC -O0 -g -static-libasan -fno-omit-frame-pointer)
    target_link_options(${tests_name} PUBLIC -static-libasan -fno-omit-frame-pointer)
endif()

option(WITH_VALGRIND "Add valgrind target")
if(WITH_VALGRIND)
    # Добавление тестов с санитайзером valgrind
    add_executable(${tests_name}_valgrind ${test_files})
    target_link_libraries(${tests_name}_valgrind PUBLIC ${target_lib} GTest::Main)
    
    add_test(NAME ${tests_name}_valgrind COMMAND ${tests_name}_valgrind)
    target_compile_options(${tests_name}_valgrind PUBLIC -O0 -g)
endif()


option(WITH_TESTS "Add test target")
if(WITH_TESTS)
    # Добавление тестов
    add_executable(${tests_name}_tests ${test_files})
    target_link_libraries(${tests_name}_tests PUBLIC ${target_lib} GTest::Main)
    
    add_test(NAME ${tests_name}_tests COMMAND ${tests_name}_tests)
    target_compile_options(${tests_name}_tests PUBLIC -O0 -g)
endif()

