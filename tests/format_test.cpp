#include "format.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  assert(Format::ElapsedTime(0) == "00:00:00");
  assert(Format::ElapsedTime(1) == "00:00:01");
  assert(Format::ElapsedTime(59) == "00:00:59");
  assert(Format::ElapsedTime(60) == "00:01:00");
  assert(Format::ElapsedTime(61) == "00:01:01");
  assert(Format::ElapsedTime(3599) == "00:59:59");
  assert(Format::ElapsedTime(3600) == "01:00:00");
  assert(Format::ElapsedTime(3661) == "01:01:01");
  std::printf("ElapsedTime basic cases passed\n");

  assert(Format::ElapsedTime(86399) == "23:59:59");
  assert(Format::ElapsedTime(86400) == "24:00:00");
  assert(Format::ElapsedTime(359999) == "99:59:59");
  assert(Format::ElapsedTime(360000) == "00:00:00");
  std::printf("ElapsedTime hour boundary cases passed\n");

  assert(Format::ElapsedTime(10) == "00:00:10");
  assert(Format::ElapsedTime(70) == "00:01:10");
  assert(Format::ElapsedTime(3610) == "01:00:10");
  std::printf("ElapsedTime zero-padding cases passed\n");

  std::printf("All Format::ElapsedTime characterization tests passed.\n");
  return 0;
}
