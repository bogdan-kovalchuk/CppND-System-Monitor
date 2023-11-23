#include "linux_parser.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <limits>

int main() {
  using LinuxParser::ComputeProcessorUtilization;

  assert(ComputeProcessorUtilization(
      100, 20, 50, 800, 10, 5, 3, 2,
      0, 0, 0, 0, 0, 0, 0, 0, true) == 0.0f);
  std::printf("ComputeProcessorUtilization first call returns zero\n");

  {
    float r = ComputeProcessorUtilization(
        100, 20, 50, 800, 10, 5, 3, 2,
        100, 20, 50, 800, 10, 5, 3, 2, false);
    assert(r == 0.0f);
    assert(!std::isnan(r));
    std::printf("ComputeProcessorUtilization zero delta returns zero\n");
  }

  {
    float r = ComputeProcessorUtilization(
        200, 20, 60, 800, 10, 5, 3, 2,
        100, 20, 50, 800, 10, 5, 3, 2, false);
    assert(r > 0.0f);
    assert(r <= 1.0f);
    assert(!std::isnan(r));
    std::printf("ComputeProcessorUtilization normal delta = %.4f\n", r);
  }

  {
    std::uint64_t u1 = 100, ni1 = 10, s1 = 50, id1 = 1000;
    std::uint64_t io1 = 5, ir1 = 2, si1 = 1, st1 = 0;
    std::uint64_t u2 = 110, ni2 = 10, s2 = 52, id2 = 1005;
    std::uint64_t io2 = 5, ir2 = 2, si2 = 1, st2 = 0;
    float r = ComputeProcessorUtilization(
        u2, ni2, s2, id2, io2, ir2, si2, st2,
        u1, ni1, s1, id1, io1, ir1, si1, st1, false);
    assert(r >= 0.0f && r <= 1.0f);
    assert(!std::isnan(r));
    assert(!std::isinf(r));
    std::printf("ComputeProcessorUtilization small delta = %.4f\n", r);
  }

  {
    float r = ComputeProcessorUtilization(
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, false);
    assert(r == 0.0f);
    assert(!std::isnan(r));
    std::printf("ComputeProcessorUtilization all zeros returns zero\n");
  }

  {
    const std::uint64_t high =
        static_cast<std::uint64_t>(std::numeric_limits<int>::max()) + 1000;
    float r = ComputeProcessorUtilization(
        high + 10, high + 10, high + 10, high + 20,
        high + 20, high + 10, high + 10, high + 10,
        high, high, high, high, high, high, high, high, false);
    assert(r > 0.0f && r < 1.0f);
    assert(std::isfinite(r));
    std::printf("ComputeProcessorUtilization supports counters above INT_MAX\n");
  }

  {
    float r = ComputeProcessorUtilization(
        99, 100, 100, 100, 100, 100, 100, 100,
        100, 100, 100, 100, 100, 100, 100, 100, false);
    assert(r == 0.0f);
    std::printf("ComputeProcessorUtilization rejects decreasing counters\n");
  }

  std::printf("All ComputeProcessorUtilization tests passed.\n");
  return 0;
}
