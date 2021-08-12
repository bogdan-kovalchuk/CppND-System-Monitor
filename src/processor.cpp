#include "processor.h"

float Processor::Utilization() {
  vector<string> stat_cpu = LinuxParser::CpuUtilization();

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

  int prev_idle = prev_idle_ + prev_iowait_;
  int idl = idle + iowait;

  int prev_nonidle = prev_user_ + prev_nice_ + prev_system_ + prev_irq_ +
                     prev_softirq_ + prev_steal_;
  int nonidle = user + nice + system + irq + softirq + steal;

  int prev_total = prev_idle + prev_nonidle;
  int total = idl + nonidle;

  int totald = total - prev_total;
  int idled = idl - prev_idle;

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

  float cpu_utilization = (float)(totald - idled) / totald;

  return cpu_utilization;
}