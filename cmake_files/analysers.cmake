if(BUILD_STATIC)
        file(
                GLOB ALL_SOURCE_FILES 
                src/main.c 
                lib/static_lib/src/*.c 
                lib/static_lib/include/*.c 
                lib/num_of_char/src/*.c 
                lib/num_of_char/include/*.c 
        )
else()
        file(
                GLOB ALL_SOURCE_FILES 
                src/main.c 
                lib/shared_lib/src/*.c 
                lib/shared_lib/include/*.c 
                lib/num_of_char/src/*.c 
                lib/num_of_char/include/*.c 
        )
endif()

add_custom_target(
        analysers
        
        COMMAND echo ------------------------------------- clang-format -------------------------------------
        COMMAND clang-format
        -style=Google 
        -i
        ${ALL_SOURCE_FILES}
        COMMAND echo  done: clang-format

        COMMAND echo --------------------------------------- cppcheck ---------------------------------------
        COMMAND cppcheck
        --language=c
        --inconclusive
        --enable=all
        ${ALL_SOURCE_FILES}
        COMMAND echo  done: cppcheck

        COMMAND echo -------------------------------------- clang-tidy --------------------------------------
        COMMAND clang-tidy
        -p ./
        ${ALL_SOURCE_FILES}
        --checks=-clang-analyzer-security.insecureAPI.DeprecatedOrUnsafeBufferHandling
        COMMAND echo  done: clang-tidy

        COMMAND echo -------------------------------------- scan-build --------------------------------------
        COMMAND scan-build make

        COMMAND echo ---------------------------------------- infer -----------------------------------------
        COMMAND infer run --compilation-database ./compile_commands.json
        
#        COMMAND echo ---------------------------------------- cpplint ---------------------------------------
#        COMMAND python3 -m cpplint
#        ${ALL_SOURCE_FILES}
)
