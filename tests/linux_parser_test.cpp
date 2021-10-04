#include "linux_parser.h"

#include <algorithm>
#include <cassert>
#include <cstdio>

int main() {
  const auto os = LinuxParser::OperatingSystem();
  assert(!os.empty());
  std::printf("OperatingSystem: %s\n", os.c_str());

  const auto kernel = LinuxParser::Kernel();
  assert(!kernel.empty());
  std::printf("Kernel: %s\n", kernel.c_str());

  const long uptime = LinuxParser::UpTime();
  assert(uptime > 0);
  std::printf("UpTime: %ld s\n", uptime);

  const auto pids = LinuxParser::Pids();
  assert(!pids.empty());
  assert(std::all_of(pids.begin(), pids.end(), [](int p) { return p > 0; }));
  std::printf("Pids: %zu entries\n", pids.size());

  const float mem = LinuxParser::MemoryUtilization();
  assert(mem >= 0.0F && mem <= 1.0F);
  std::printf("MemoryUtilization: %.3f\n", mem);

  const int total = LinuxParser::TotalProcesses();
  assert(total >= 0);
  std::printf("TotalProcesses: %d\n", total);

  const int running = LinuxParser::RunningProcesses();
  assert(running >= 0);
  std::printf("RunningProcesses: %d\n", running);

  const int pid1 = pids.front();
  const auto cmd = LinuxParser::Command(pid1);
  std::printf("Command(%d): %.60s\n", pid1, cmd.c_str());

  const auto ram = LinuxParser::Ram(pid1);
  assert(!ram.empty());
  std::printf("Ram(%d): %s kB\n", pid1, ram.c_str());

  const auto uid = LinuxParser::Uid(pid1);
  assert(!uid.empty());
  std::printf("Uid(%d): %s\n", pid1, uid.c_str());

  const auto user = LinuxParser::User(pid1);
  std::printf("User(%d): %s\n", pid1, user.c_str());

  const long proc_uptime = LinuxParser::UpTime(pid1);
  assert(proc_uptime >= 0);
  std::printf("UpTime(%d): %ld ticks\n", pid1, proc_uptime);

  const auto cpu = LinuxParser::CpuUtilization();
  assert(!cpu.empty());
  std::printf("CpuUtilization fields: %zu\n", cpu.size());

  const auto pid_cpu = LinuxParser::CpuUtilization(pid1);
  assert(pid_cpu.size() >= 6);
  std::printf("CpuUtilization(%d) fields: %zu\n", pid1, pid_cpu.size());

  std::printf("All characterization tests passed.\n");
  return 0;
}
