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
    assert(!(procs[i] > procs[i - 1]));
  }
  std::printf("Sort order valid for %zu processes\n", procs.size());

  std::vector<Process> procs2;
  for (int pid : pids) {
    procs2.emplace_back(pid);
  }
  std::sort(procs2.begin(), procs2.end(), std::greater<Process>());
  assert(procs.size() == procs2.size());
  for (size_t i = 0; i < procs.size(); ++i) {
    assert(procs[i].Pid() == procs2[i].Pid());
  }
  std::printf("Sort order is deterministic across runs\n");

  int equal_count = 0;
  for (size_t i = 1; i < procs.size(); ++i) {
    if (procs[i].CpuUtilization() == procs[i - 1].CpuUtilization()) {
      ++equal_count;
    }
  }
  std::printf("Processes with equal CPU: %d\n", equal_count);

  std::printf("All process ordering tests passed.\n");
  return 0;
}
