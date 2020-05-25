
add_executable(
    cctype-unittest
    islower/islower_unittest.cc
    isupper/isupper_unittest.cc
    isalpha/isalpha_unittest.cc
    isdigit/isdigit_unittest.cc
    isxdigit/isxdigit_unittest.cc
    isalnum/isalnum_unittest.cc
    isblank/isblank_unittest.cc
    isspace/isspace_unittest.cc
    iscntrl/iscntrl_unittest.cc
    ispunct/ispunct_unittest.cc
    isgraph/isgraph_unittest.cc
    isprint/isprint_unittest.cc
    tolower/tolower_unittest.cc
    toupper/toupper_unittest.cc
    )

target_link_libraries(cctype-unittest gtest gtest_main pthread)  

