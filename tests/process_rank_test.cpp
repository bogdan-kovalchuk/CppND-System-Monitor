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
  std::sort(procs.begin(), procs.end(), std::greater<Process>());

  for (size_t i = 1; i < procs.size(); ++i) {
    float cpu_prev = procs[i - 1].CpuUtilization();
    float cpu_curr = procs[i].CpuUtilization();
    if (cpu_prev == cpu_curr) {
      assert(procs[i - 1].Pid() > procs[i].Pid());
    } else {
      assert(cpu_prev > cpu_curr);
    }
  }
  std::printf("Multi-criteria sort order valid for %zu processes\n", procs.size());

  int tie_count = 0;
  for (size_t i = 1; i < procs.size(); ++i) {
    if (procs[i].CpuUtilization() == procs[i - 1].CpuUtilization()) {
      ++tie_count;
      assert(procs[i - 1].Pid() != procs[i].Pid());
    }
  }
  std::printf("Processes with tied CPU (broken by PID): %d\n", tie_count);

  std::vector<Process> procs2;
  for (int pid : pids) {
    procs2.emplace_back(pid);
  }
  std::sort(procs2.begin(), procs2.end(), std::greater<Process>());
  assert(procs.size() == procs2.size());
  for (size_t i = 0; i < procs.size(); ++i) {
    assert(procs[i].Pid() == procs2[i].Pid());
  }
  std::printf("Multi-criteria sort is deterministic\n");

  std::printf("All multi-criteria process ordering tests passed.\n");
  return 0;
}
