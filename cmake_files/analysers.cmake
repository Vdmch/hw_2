file(
        GLOB ALL_SOURCE_FILES 
        src/main.c 
        lib/*/src/*.c 
        lib/*/include/*.c 
)

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
