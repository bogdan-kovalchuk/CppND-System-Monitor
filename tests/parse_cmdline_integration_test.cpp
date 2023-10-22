#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseCmdline;

  std::string with_nulls = std::string("/usr/bin/python3\0script.py\0--verbose", 33);
  std::string result = ParseCmdline(with_nulls);
  assert(result == "/usr/bin/python3 script.py --verbose");
  std::printf("ParseCmdline converts null separators to spaces\n");

  std::string single_arg = std::string("/bin/ls", 7);
  assert(ParseCmdline(single_arg) == "/bin/ls");
  std::printf("ParseCmdline single arg without nulls passed\n");

  std::string kernel_thread(1, '\0');
  assert(ParseCmdline(kernel_thread).empty());
  std::printf("ParseCmdline kernel thread (single null) returns empty\n");

  std::string with_trailing = std::string("echo\0hello\0", 11);
  assert(ParseCmdline(with_trailing) == "echo hello");
  std::printf("ParseCmdline trailing null trimmed\n");

  std::string long_cmd =
      std::string("/usr/bin/gcc\0-Wall\0-Wextra\0-O2\0-c\0main.cpp\0-o\0main", 46);
  assert(ParseCmdline(long_cmd) ==
         "/usr/bin/gcc -Wall -Wextra -O2 -c main.cpp -o main");
  std::printf("ParseCmdline realistic build command passed\n");

  std::string embedded_spaces = "no nulls at all just spaces";
  assert(ParseCmdline(embedded_spaces) == "no nulls at all just spaces");
  std::printf("ParseCmdline spaces-only passthrough\n");

  std::printf("All ParseCmdline integration behavior tests passed.\n");
  return 0;
}
