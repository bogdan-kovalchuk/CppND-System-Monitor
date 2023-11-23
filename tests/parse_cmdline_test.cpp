#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseCmdline;

  assert(ParseCmdline("") == "");
  std::printf("ParseCmdline empty input passed\n");

  std::string single = "ls";
  assert(ParseCmdline(single) == "ls");
  std::printf("ParseCmdline single arg passed\n");

  const char with_nulls_raw[] = "ls\0-la\0/tmp";
  std::string with_nulls(with_nulls_raw, sizeof(with_nulls_raw) - 1);
  std::string expected = "ls -la /tmp";
  assert(ParseCmdline(with_nulls) == expected);
  std::printf("ParseCmdline null-byte replacement passed\n");

  const char trailing_raw[] = "echo\0hello\0";
  std::string trailing(trailing_raw, sizeof(trailing_raw) - 1);
  assert(ParseCmdline(trailing) == "echo hello");
  std::printf("ParseCmdline trailing nulls trimmed\n");

  std::string spaces = "no nulls here";
  assert(ParseCmdline(spaces) == "no nulls here");
  std::printf("ParseCmdline no-null passthrough passed\n");

  std::string all_nulls(5, '\0');
  assert(ParseCmdline(all_nulls) == "");
  std::printf("ParseCmdline all-null input returns empty\n");

  std::printf("All ParseCmdline tests passed.\n");
  return 0;
}
