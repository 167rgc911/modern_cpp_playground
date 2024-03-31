add_executable(aa aa.cpp)

add_library(csv_io STATIC csv.cpp)

add_custom_target(timer_h2
  COMMAND cppfront-0.7.0 -verbose -emit-cppfront-info -import-std -pure-cpp2 timer.h2
  WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/cpp2
)

add_library(timer STATIC timer.cpp)
add_dependencies(timer timer_h2)
target_include_directories(timer PUBLIC ${PROJECT_SOURCE_DIR}/cpp2)

add_executable(timer_benchmark timer_benchmark.cpp)
add_dependencies(timer_benchmark timer)
target_link_libraries(timer_benchmark timer benchmark gmock gtest)
add_test(NAME timer_benchmark COMMAND timer_benchmark)
