################################
# GTest
################################

# Исходник тестирования
set(test_files src/test_func.cpp)
set(target_lib test_func)

# Тесты
option(WITH_SANITIZERS "Add sanitizers")
if(WITH_SANITIZERS)
    # Добавление тестов с санитайзерами undefined, leak и address
    add_executable(runUnitTests_addr ${test_files})
    target_link_libraries(runUnitTests_addr PUBLIC ${target_lib} GTest::Main)

    add_test(NAME runUnitTests_addr COMMAND runUnitTests_addr)    
    target_compile_options(runUnitTests_addr PUBLIC -O0 -g -static-libasan -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=leak -fsanitize=address)
    target_link_options(runUnitTests_addr PUBLIC -static-libasan -fno-omit-frame-pointer -fsanitize=undefined -fsanitize=leak -fsanitize=address)

    # Добавление тестов с санитайзером thread
    add_executable(runUnitTests_thread ${test_files})
    target_link_libraries(runUnitTests_thread PUBLIC ${target_lib} GTest::Main)
    
    add_test(NAME runUnitTests_thread COMMAND runUnitTests_thread)
    target_compile_options(runUnitTests_thread PUBLIC -fno-omit-frame-pointer -O0 -g -static-libasan -fsanitize=thread)
    target_link_options(runUnitTests_thread PUBLIC -fno-omit-frame-pointer -static-libasan -fsanitize=thread)
endif()

if(WITH_COVERAGE)
    # Добавление тестов для оценки покрытия
    add_executable(runUnitTests ${test_files})
    target_link_libraries(runUnitTests PUBLIC ${target_lib} GTest::Main)

    add_test(NAME runUnitTests COMMAND runUnitTests)    
    target_compile_options(runUnitTests PUBLIC -O0 -g -static-libasan -fno-omit-frame-pointer)
    target_link_options(runUnitTests PUBLIC -static-libasan -fno-omit-frame-pointer)
endif()

option(WITH_VALGRIND "Add valgrind target")
if(WITH_VALGRIND)
    # Добавление тестов с санитайзером valgrind
    add_executable(runUnitTests_valgrind ${test_files})
    target_link_libraries(runUnitTests_valgrind PUBLIC ${target_lib} GTest::Main)
    
    add_test(NAME runUnitTests_valgrind COMMAND runUnitTests_valgrind)
    target_compile_options(runUnitTests_valgrind PUBLIC -O0 -g)
endif()
