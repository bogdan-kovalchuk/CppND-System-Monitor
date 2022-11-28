#include "format.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

int main() {
  for (long v = 0; v <= 3600; ++v) {
    const auto a = Format::ElapsedTime(v);
    const auto b = Format::ElapsedTimeDiv(v);
    assert(a == b);
  }
  std::printf("ElapsedTime and ElapsedTimeDiv agree on 0..3600\n");

  for (long v = 86300; v <= 86500; ++v) {
    const auto a = Format::ElapsedTime(v);
    const auto b = Format::ElapsedTimeDiv(v);
    assert(a == b);
  }
  std::printf("Both agree around 24-hour boundary\n");

  for (long v = 359900; v <= 360100; ++v) {
    const auto a = Format::ElapsedTime(v);
    const auto b = Format::ElapsedTimeDiv(v);
    assert(a == b);
  }
  std::printf("Both agree around 100-hour wrap\n");

  const std::vector<long> samples = {
      0, 1, 59, 60, 61, 3599, 3600, 3661,
      7200, 86399, 86400, 100000, 200000, 359999};
  for (long v : samples) {
    assert(Format::ElapsedTimeDiv(v) == Format::ElapsedTime(v));
  }
  std::printf("Both agree on sparse large samples\n");

  assert(Format::ElapsedTimeDiv(0) == "00:00:00");
  assert(Format::ElapsedTimeDiv(3661) == "01:01:01");
  assert(Format::ElapsedTimeDiv(86399) == "23:59:59");
  std::printf("ElapsedTimeDiv spot checks passed\n");

  std::printf("All ElapsedTimeDiv range consistency tests passed.\n");
  return 0;
}
