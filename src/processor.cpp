#include "processor.h"

#include <array>
#include <charconv>
#include <cstdint>

namespace {
bool ParseCounter(const std::string& value, std::uint64_t& result) {
  if (value.empty()) return false;
  const char* begin = value.data();
  const char* end = begin + value.size();
  const auto parsed = std::from_chars(begin, end, result);
  return parsed.ec == std::errc{} && parsed.ptr == end;
}
}  // namespace

float Processor::Utilization() {
  vector<string> stat_cpu = LinuxParser::CpuUtilization();

  if (stat_cpu.size() < 8) return 0.0f;

  std::array<std::uint64_t, 8> counters{};
  for (std::size_t index = 0; index < counters.size(); ++index) {
    if (!ParseCounter(stat_cpu[index], counters[index])) return 0.0f;
  }

  const auto [user, nice, system, idle, iowait, irq, softirq, steal] =
      counters;

  float cpu_utilization = LinuxParser::ComputeProcessorUtilization(
      user, nice, system, idle, iowait, irq, softirq, steal,
      prev_user_, prev_nice_, prev_system_,
      prev_idle_, prev_iowait_, prev_irq_,
      prev_softirq_, prev_steal_, !initialized_);

  prev_user_ = user;
  prev_nice_ = nice;
  prev_system_ = system;
  prev_idle_ = idle;
  prev_iowait_ = iowait;
  prev_irq_ = irq;
  prev_softirq_ = softirq;
  prev_steal_ = steal;
  initialized_ = true;

  return cpu_utilization;
}
