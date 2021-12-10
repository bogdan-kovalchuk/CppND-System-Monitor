#include "format.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

int main() {
  assert(Format::ElapsedTime(-1) == "00:00:00");
  assert(Format::ElapsedTime(-100) == "00:00:00");
  assert(Format::ElapsedTime(-3600) == "00:00:00");
  std::printf("ElapsedTime negative inputs clamped to zero\n");

  assert(Format::ElapsedTimeDiv(-1) == "00:00:00");
  assert(Format::ElapsedTimeDiv(-100) == "00:00:00");
  assert(Format::ElapsedTimeDiv(-3600) == "00:00:00");
  std::printf("ElapsedTimeDiv negative inputs clamped to zero\n");

  assert(Format::ElapsedTime(360000) == "00:00:00");
  assert(Format::ElapsedTime(360001) == "00:00:01");
  assert(Format::ElapsedTime(720000) == "00:00:00");
  std::printf("ElapsedTime wraps at 100 hours\n");

  assert(Format::ElapsedTimeDiv(360000) == "00:00:00");
  assert(Format::ElapsedTimeDiv(360001) == "00:00:01");
  assert(Format::ElapsedTimeDiv(720000) == "00:00:00");
  std::printf("ElapsedTimeDiv wraps at 100 hours\n");

  const std::vector<long> edge_cases = {-1, -3600, 0, 359999, 360000, 719999};
  for (long v : edge_cases) {
    const auto a = Format::ElapsedTime(v);
    const auto b = Format::ElapsedTimeDiv(v);
    assert(a == b);
  }
  std::printf("Both implementations agree on edge cases\n");

  std::printf("All negative and long-duration tests passed.\n");
  return 0;
}
