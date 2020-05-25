
add_executable(
    cstring-unittest 
    strlen/strlen_unittest.cc
    strcpy/strcpy_unittest.cc
    strncpy/strncpy_unittest.cc
    strcat/strcat_unittest.cc
    strncat/strncat_unittest.cc
    strcmp/strcmp_unittest.cc
    strncmp/strncmp_unittest.cc
    strchr/strchr_unittest.cc
    strrchr/strrchr_unittest.cc
    strspn/strspn_unittest.cc
    strcspn/strcspn_unittest.cc
    strpbrk/strpbrk_unittest.cc
    strstr/strstr_unittest.cc
    strtok/strtok_unittest.cc
    )

target_link_libraries(cstring-unittest gtest gtest_main pthread)  

