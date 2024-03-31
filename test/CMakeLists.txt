add_executable(cons1 cons1.cpp)
add_test(NAME cons1 COMMAND cons1)

add_executable(cons2 cons2.cpp)
add_test(NAME cons2 COMMAND cons2)

add_executable(cons3 cons3.cpp)
add_test(NAME cons3 COMMAND cons3)

add_executable(access1 access1.cpp)
add_test(NAME access1 COMMAND access1)

add_executable(access2 access2.cpp)
add_test(NAME access2 COMMAND access2)

add_executable(csv csv.cpp)
target_link_libraries(csv csv_io)
add_test(NAME csv COMMAND csv)
set_property(TEST csv PROPERTY
    FAIL_REGULAR_EXPRESSION "XXX [^a-z]"
)

add_executable(csv_map csv_map.cpp)
target_link_libraries(csv_map csv_io)
add_test(NAME csv_map COMMAND csv_map)
set_property(TEST csv_map PROPERTY
    FAIL_REGULAR_EXPRESSION "XXX [^a-z]"
)

add_executable(csv_map2 csv_map2.cpp)
target_link_libraries(csv_map2 csv_io)
add_test(NAME csv_map2 COMMAND csv_map2)
set_property(TEST csv_map2 PROPERTY
    FAIL_REGULAR_EXPRESSION "XXX [^a-z]"
)

add_executable(search search.cpp)
target_link_libraries(search csv_io)
add_test(NAME search COMMAND search)

add_executable(search2 search2.cpp)
target_link_libraries(search2 csv_io)
add_test(NAME search2 COMMAND search2)

add_executable(search3 search3.cpp)
target_link_libraries(search3 csv_io)
add_test(NAME search3 COMMAND search3)

add_executable(search_notfound search_notfound.cpp)
target_link_libraries(search_notfound csv_io)
add_test(NAME search_notfound COMMAND search_notfound)
set_property(TEST search_notfound PROPERTY WILL_FAIL TRUE)

# add_executable(exception_at_pos exception_at_pos.cpp)
# target_link_libraries(exception_at_pos csv_io)
# add_test(NAME exception_at_pos COMMAND exception_at_pos)
# set_property(TEST exception_at_pos PROPERTY WILL_FAIL TRUE)

add_executable(test_timer timer.cpp)
target_link_libraries(test_timer timer)
add_test(NAME test_timer COMMAND test_timer)

add_executable(test_timer2 timer2.cpp)
target_link_libraries(test_timer2 timer)
add_test(NAME test_timer2 COMMAND test_timer2)

add_executable(test_timer2_1 timer2_1.cpp)
target_link_libraries(test_timer2_1 timer)
add_test(NAME test_timer2_1 COMMAND test_timer2_1)

add_executable(test_timer3 timer3.cpp)
target_link_libraries(test_timer3 timer)
add_test(NAME test_timer3 COMMAND test_timer3)

add_executable(test_timer3_1 timer3_1.cpp)
target_link_libraries(test_timer3_1 timer)
add_test(NAME test_timer3_1 COMMAND test_timer3_1)

