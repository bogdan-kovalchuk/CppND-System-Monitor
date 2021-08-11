#include "processor.h"

float Processor::Utilization() {
  int PrevIdle = previdle_ + previowait_;
  int Idle = idle + iowait;

  int PrevNonIdle = prevuser_ + prevnice_ + prevsystem_ + previrq_ +
                    prevsoftirq_ + prevsteal_;
  int NonIdle = user + nice + system + irq + softirq + steal;

  int PrevTotal = PrevIdle + PrevNonIdle;
  int Total = Idle + NonIdle;

  // differentiate: actual value minus the previous one
  int totald = Total - PrevTotal;
  int idled = Idle - PrevIdle;

  float CPU_Percentage = (totald - idled) / totald;
  return cpu_utilization_;
}