#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseRamMb;

  assert(ParseRamMb("0") == "0");
  assert(ParseRamMb("1024") == "1");
  assert(ParseRamMb("2048") == "2");
  assert(ParseRamMb("10240") == "10");
  std::printf("ParseRamMb exact multiples of 1024 passed\n");

  assert(ParseRamMb("512") == "1");
  assert(ParseRamMb("1023") == "1");
  assert(ParseRamMb("1536") == "2");
  assert(ParseRamMb("1025") == "1");
  std::printf("ParseRamMb rounding at boundary values passed\n");

  assert(ParseRamMb("1") == "0");
  assert(ParseRamMb("511") == "0");
  assert(ParseRamMb("100") == "0");
  std::printf("ParseRamMb sub-512 kB values round to zero\n");

  assert(ParseRamMb("") == "0");
  assert(ParseRamMb("abc") == "0");
  assert(ParseRamMb("-1024") == "0");
  std::printf("ParseRamMb invalid inputs return zero\n");

  assert(ParseRamMb("16384000") == "16000");
  assert(ParseRamMb("1048576") == "1024");
  std::printf("ParseRamMb realistic process sizes passed\n");

  std::printf("All ParseRamMb tests passed.\n");
  return 0;
}
