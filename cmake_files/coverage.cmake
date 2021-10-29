file(
        GLOB ALL_SOURCE_FILES 
        src/main.c 
)

add_custom_target(
    coverage
    COMMAND mkdir
    ./coverage

    COMMAND gcovr
    -r ../
    -f ../src/ ../lib/users/src/
    --html --html-details
    -o ./coverage/details.html
)

