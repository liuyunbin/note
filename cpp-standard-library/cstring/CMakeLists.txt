
add_executable(
    cstring-unittest 
    strlen/strlen_unittest.cc
    strcpy/strcpy_unittest.cc
    strncpy/strncpy_unittest.cc
    strcat/strcat_unittest.cc
    strncat/strncat_unittest.cc
    strcmp/strcmp_unittest.cc
    strncmp/strncmp_unittest.cc
    )

target_link_libraries(cstring-unittest gtest gtest_main pthread)  

