#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseStatField;
  using LinuxParser::ParseStatusValue;

  const std::string stat_line =
      "1234 (test proc) S 1 1234 1234 0 -1 4194304 500 0 1 0 "
      "100 50 0 0 20 0 1 0 99999 8888888 1234 18446744073709551615 "
      "1 1 0 0 0 0 0 0 0 0 0 0 17 0 0 0 0 0 0";

  assert(ParseStatField(stat_line, 1) == "1234");
  assert(ParseStatField(stat_line, 2) == "test proc");
  assert(ParseStatField(stat_line, 3) == "S");
  assert(ParseStatField(stat_line, 14) == "100");
  assert(ParseStatField(stat_line, 15) == "50");
  assert(ParseStatField(stat_line, 22) == "99999");
  assert(ParseStatField(stat_line, 44) == "0");
  assert(ParseStatField(stat_line, 0).empty());
  assert(ParseStatField(stat_line, 99).empty());
  std::printf("ParseStatField: all cases passed\n");

  const std::string stat_parens =
      "42 (comm (with) parens) S 1 42 42 0 -1 0 0 0 10 20 0 0 20 0 1 0 "
      "5000 1111 0 0 0 0 0 0 0 0 0 0 17 1 0 0 0 0 0";
  assert(ParseStatField(stat_parens, 1) == "42");
  assert(ParseStatField(stat_parens, 2) == "comm (with) parens");
  assert(ParseStatField(stat_parens, 3) == "S");
  assert(ParseStatField(stat_parens, 12) == "10");
  assert(ParseStatField(stat_parens, 22) == "0");
  std::printf("ParseStatField (embedded parens): passed\n");

  const std::string status =
      "Name:\ttest_proc\n"
      "Umask:\t0022\n"
      "State:\tS (sleeping)\n"
      "Tgid:\t1234\n"
      "Pid:\t1234\n"
      "PPid:\t1\n"
      "Uid:\t1000\t1000\t1000\t1000\n"
      "VmSize:\t  21740 kB\n"
      "VmRSS:\t   5000 kB\n";

  assert(ParseStatusValue(status, "Name") == "test_proc");
  assert(ParseStatusValue(status, "State") == "S");
  assert(ParseStatusValue(status, "Uid") == "1000");
  assert(ParseStatusValue(status, "VmSize") == "21740");
  assert(ParseStatusValue(status, "VmRSS") == "5000");
  assert(ParseStatusValue(status, "Missing").empty());
  std::printf("ParseStatusValue: all cases passed\n");

  std::printf("All string-based parser tests passed.\n");
  return 0;
}
