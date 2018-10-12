add_executable(small_file_tester
    TestSmallFile.cpp
)

target_compile_options(small_file_tester
PRIVATE -Wall -Wno-unused-variable
)

target_link_libraries(small_file_tester
    bigfile
    -lstdc++fs
)

add_test(NAME test_small_file
    COMMAND $<TARGET_FILE:small_file_tester>
)
