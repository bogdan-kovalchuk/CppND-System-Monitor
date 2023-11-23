#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

int main() {
  using LinuxParser::ParseStatField;

  const std::string simple =
      "1234 (bash) S 1 1234 1234 0 -1 4194304 500 0 1 0 "
      "100 50 0 0 20 0 1 0 99999 8888888 1234";
  assert(ParseStatField(simple, 14) == "100");
  assert(ParseStatField(simple, 15) == "50");
  assert(ParseStatField(simple, 16) == "0");
  assert(ParseStatField(simple, 17) == "0");
  assert(ParseStatField(simple, 22) == "99999");
  std::printf("ParseStatField simple comm fields correct\n");

  const std::string spaced =
      "5678 (Web Content) S 1 5678 5678 0 -1 4194304 500 0 1 0 "
      "200 80 10 5 30 0 1 0 50000 7777777 5678";
  assert(ParseStatField(spaced, 14) == "200");
  assert(ParseStatField(spaced, 15) == "80");
  assert(ParseStatField(spaced, 16) == "10");
  assert(ParseStatField(spaced, 17) == "5");
  assert(ParseStatField(spaced, 22) == "50000");
  std::printf("ParseStatField comm-with-spaces fields correct\n");

  const std::string multi_paren =
      "9999 (a (b) c) R 1 9999 9999 0 -1 0 0 0 0 0 "
      "300 150 20 10 40 0 1 0 75000 6666666 9999";
  assert(ParseStatField(multi_paren, 14) == "300");
  assert(ParseStatField(multi_paren, 15) == "150");
  assert(ParseStatField(multi_paren, 16) == "20");
  assert(ParseStatField(multi_paren, 17) == "10");
  assert(ParseStatField(multi_paren, 22) == "75000");
  std::printf("ParseStatField multi-paren comm fields correct\n");

  const std::string long_comm =
      "42 (gnome-shell) S 1 42 42 0 -1 4194304 1000 0 0 0 "
      "500 250 30 15 60 0 1 0 120000 5555555 42";
  assert(ParseStatField(long_comm, 14) == "500");
  assert(ParseStatField(long_comm, 15) == "250");
  assert(ParseStatField(long_comm, 22) == "120000");
  std::printf("ParseStatField long comm name fields correct\n");

  std::printf("All CpuUtilization field extraction tests passed.\n");
  return 0;
}
