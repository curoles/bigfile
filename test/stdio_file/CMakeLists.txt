add_executable(stdio_file_tester
    TestStdioFile.cpp
)

target_compile_options(stdio_file_tester
PRIVATE -Wall -Wno-unused-variable
)

target_link_libraries(stdio_file_tester
    bigfile
    -lstdc++fs
)

add_test(NAME test_stdio_file
    COMMAND $<TARGET_FILE:stdio_file_tester>
)
