#include "processor.h"

float Processor::Utilization() {
  vector<string> stat_cpu = LinuxParser::CpuUtilization();

  if (stat_cpu.size() < 10) return 0.0f;

  int user = stoi(stat_cpu[0]);
  int nice = stoi(stat_cpu[1]);
  int system = stoi(stat_cpu[2]);
  int idle = stoi(stat_cpu[3]);
  int iowait = stoi(stat_cpu[4]);
  int irq = stoi(stat_cpu[5]);
  int softirq = stoi(stat_cpu[6]);
  int steal = stoi(stat_cpu[7]);
  int guest = stoi(stat_cpu[8]);
  int guest_nice = stoi(stat_cpu[9]);

  bool first_call = (prev_user_ == 0 && prev_nice_ == 0 &&
                     prev_system_ == 0 && prev_idle_ == 0 &&
                     prev_iowait_ == 0 && prev_irq_ == 0 &&
                     prev_softirq_ == 0 && prev_steal_ == 0);

  float cpu_utilization = LinuxParser::ComputeProcessorUtilization(
      user, nice, system, idle, iowait, irq, softirq, steal,
      prev_user_, prev_nice_, prev_system_,
      prev_idle_, prev_iowait_, prev_irq_,
      prev_softirq_, prev_steal_, first_call);

  prev_user_ = user;
  prev_nice_ = nice;
  prev_system_ = system;
  prev_idle_ = idle;
  prev_iowait_ = iowait;
  prev_irq_ = irq;
  prev_softirq_ = softirq;
  prev_steal_ = steal;
  prev_guest_ = guest;
  prev_guest_nice_ = guest_nice;

  return cpu_utilization;
}
