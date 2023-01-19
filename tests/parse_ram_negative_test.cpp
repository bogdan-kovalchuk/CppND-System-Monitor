#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseRamMb;

  assert(ParseRamMb("-1") == "0");
  assert(ParseRamMb("-1024") == "0");
  assert(ParseRamMb("-2048") == "0");
  assert(ParseRamMb("-100000") == "0");
  std::printf("ParseRamMb clamps all negative inputs to zero\n");

  assert(ParseRamMb("0") == "0");
  assert(ParseRamMb("511") == "0");
  assert(ParseRamMb("512") == "1");
  assert(ParseRamMb("1024") == "1");
  assert(ParseRamMb("1536") == "2");
  std::printf("ParseRamMb non-negative rounding unchanged\n");

  assert(ParseRamMb("16384000") == "16000");
  assert(ParseRamMb("1048576") == "1024");
  std::printf("ParseRamMb realistic values unchanged\n");

  std::printf("All ParseRamMb negative-clamp tests passed.\n");
  return 0;
}
