#include "format.h"

#include <cassert>
#include <cstdio>
#include <string>
#include <vector>

int main() {
  const std::vector<long> test_values = {
      0, 1, 59, 60, 61, 3599, 3600, 3661, 86399, 86400,
      359999, 360000, 10, 70, 3610, 100, 1000, 10000, 100000};

  for (long v : test_values) {
    const auto a = Format::ElapsedTime(v);
    const auto b = Format::ElapsedTimeDiv(v);
    if (a != b) {
      std::printf("MISMATCH at %ld: ElapsedTime='%s' ElapsedTimeDiv='%s'\n",
                  v, a.c_str(), b.c_str());
      return 1;
    }
  }
  std::printf("Both implementations agree on %zu values.\n", test_values.size());

  std::printf("All comparison tests passed.\n");
  return 0;
}
