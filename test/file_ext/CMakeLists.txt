add_executable(file_ext_tester
    TestFileExt.cpp
)

target_compile_options(file_ext_tester
PRIVATE -Wall -Wno-unused-variable
)

target_link_libraries(file_ext_tester
    bigfile
    -lstdc++fs
)

add_test(NAME test_file_ext
    COMMAND $<TARGET_FILE:file_ext_tester>
)
