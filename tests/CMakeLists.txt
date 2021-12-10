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

add_executable(string_parser_test
  string_parser_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(string_parser_test PRIVATE ../include)
target_compile_features(string_parser_test PRIVATE cxx_std_17)
target_compile_options(string_parser_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME string_parser_test COMMAND string_parser_test)

add_executable(boundary_test
  boundary_test.cpp
  ../src/linux_parser.cpp
)
target_include_directories(boundary_test PRIVATE ../include)
target_compile_features(boundary_test PRIVATE cxx_std_17)
target_compile_options(boundary_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME boundary_test COMMAND boundary_test)

add_executable(format_test
  format_test.cpp
  ../src/format.cpp
)
target_include_directories(format_test PRIVATE ../include)
target_compile_features(format_test PRIVATE cxx_std_17)
target_compile_options(format_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME format_test COMMAND format_test)

add_executable(format_compare_test
  format_compare_test.cpp
  ../src/format.cpp
)
target_include_directories(format_compare_test PRIVATE ../include)
target_compile_features(format_compare_test PRIVATE cxx_std_17)
target_compile_options(format_compare_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME format_compare_test COMMAND format_compare_test)

add_executable(format_edge_test
  format_edge_test.cpp
  ../src/format.cpp
)
target_include_directories(format_edge_test PRIVATE ../include)
target_compile_features(format_edge_test PRIVATE cxx_std_17)
target_compile_options(format_edge_test PRIVATE -Wall -Wextra -Wpedantic)
add_test(NAME format_edge_test COMMAND format_edge_test)

