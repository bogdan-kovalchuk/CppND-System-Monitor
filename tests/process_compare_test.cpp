#include "linux_parser.h"
#include "process.h"

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <vector>

int main() {
  const auto pids = LinuxParser::Pids();
  assert(!pids.empty());

  std::vector<Process> procs;
  for (int pid : pids) {
    procs.emplace_back(pid);
  }

  for (const auto& p : procs) {
    assert(!(p > p));
    assert(p == p);
  }
  std::printf("Process operator> is irreflexive\n");

  for (size_t i = 0; i < procs.size(); ++i) {
    for (size_t j = i + 1; j < procs.size(); ++j) {
      if (procs[i] == procs[j]) {
        assert(!(procs[i] > procs[j]));
        assert(!(procs[j] > procs[i]));
      } else {
        bool i_gt_j = procs[i] > procs[j];
        bool j_gt_i = procs[j] > procs[i];
        assert(i_gt_j != j_gt_i);
      }
    }
  }
  std::printf("Process operator> establishes strict weak ordering\n");

  std::sort(procs.begin(), procs.end(), std::greater<Process>());
  for (size_t i = 1; i < procs.size(); ++i) {
    assert(!(procs[i] > procs[i - 1]));
  }
  std::printf("Sorted order is consistent with operator>\n");

  for (size_t i = 1; i < procs.size(); ++i) {
    if (procs[i].CpuUtilization() == procs[i - 1].CpuUtilization()) {
      assert(procs[i - 1].Pid() > procs[i].Pid());
    } else {
      assert(procs[i - 1].CpuUtilization() > procs[i].CpuUtilization());
    }
  }
  std::printf("Tie-breaking by PID is explicit and correct\n");

  std::printf("All Process comparison tests passed.\n");
  return 0;
}
