
add_executable(
    reproduce-multi-machine-data-processing-01
    01.cc
    tiny-huge-number-calculator.cc
    )

target_link_libraries(
    reproduce-multi-machine-data-processing-01
    glog
    )

