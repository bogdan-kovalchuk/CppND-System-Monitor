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

  int PrevIdle = previdle_ + previowait_;
  int Idle = idle + iowait;

  int PrevNonIdle = prevuser_ + prevnice_ + prevsystem_ + previrq_ +
                    prevsoftirq_ + prevsteal_;
  int NonIdle = user + nice + system + irq + softirq + steal;

  int PrevTotal = PrevIdle + PrevNonIdle;
  int Total = Idle + NonIdle;

  int totald = Total - PrevTotal;
  int idled = Idle - PrevIdle;

  prevuser_ = user;
  prevnice_ = nice;
  prevsystem_ = system;
  previdle_ = idle;
  previowait_ = iowait;
  previrq_ = irq;
  prevsoftirq_ = softirq;
  prevsteal_ = steal;
  prevguest_ = guest;
  prevguest_nice_ = guest_nice;

  float cpu_utilization = (float)(totald - idled) / totald;

  return cpu_utilization;
}