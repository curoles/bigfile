add_executable(stdio_file_tester
    TestStdioFile.cpp
)

target_link_libraries(stdio_file_tester
    bigfile
)

add_test(NAME test_stdio_file
    COMMAND $<TARGET_FILE:stdio_file_tester>
)
