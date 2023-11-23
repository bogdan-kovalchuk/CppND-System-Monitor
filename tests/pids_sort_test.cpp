#include "linux_parser.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>

int main() {
  const auto pids = LinuxParser::Pids();
  assert(!pids.empty());
  std::printf("Pids: %zu entries\n", pids.size());

  assert(std::is_sorted(pids.begin(), pids.end()));
  std::printf("Pids are sorted in ascending order\n");

  for (size_t i = 1; i < pids.size(); ++i) {
    assert(pids[i] > pids[i - 1]);
  }
  std::printf("Pids have no duplicates\n");

  assert(std::all_of(pids.begin(), pids.end(), [](int p) { return p > 0; }));
  std::printf("All Pids are positive\n");

  const auto pids2 = LinuxParser::Pids();
  assert(std::is_sorted(pids2.begin(), pids2.end()));
  for (size_t i = 1; i < pids2.size(); ++i) {
    assert(pids2[i] > pids2[i - 1]);
  }
  std::printf("Each Pids snapshot is deterministically ordered\n");

  std::printf("All Pids sorting tests passed.\n");
  return 0;
}
