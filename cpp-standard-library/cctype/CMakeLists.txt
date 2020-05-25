
add_executable(
    cctype-unittest
    islower/islower_unittest.cc
    isupper/isupper_unittest.cc
    isalpha/isalpha_unittest.cc
    isdigit/isdigit_unittest.cc
    isxdigit/isxdigit_unittest.cc
    )

target_link_libraries(cctype-unittest gtest gtest_main pthread)  

