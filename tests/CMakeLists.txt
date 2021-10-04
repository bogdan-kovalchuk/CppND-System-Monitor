cmake_minimum_required(VERSION 3.16)
project(system_monitor_focused_tests LANGUAGES CXX)

enable_testing()

add_executable(linux_parser_test
  linux_parser_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(linux_parser_test PRIVATE ../include)
target_compile_features(linux_parser_test PRIVATE cxx_std_17)
target_compile_options(linux_parser_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME linux_parser_test COMMAND linux_parser_test)

