add_executable(big_file_tester
    TestBigFile.cpp
)

target_compile_options(big_file_tester
PRIVATE -Wall -Wno-unused-variable
)

target_link_libraries(big_file_tester
    bigfile
    -lstdc++fs
)

add_test(NAME test_big_file
    COMMAND $<TARGET_FILE:big_file_tester>
)
