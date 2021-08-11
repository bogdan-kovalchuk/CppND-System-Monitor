#include "processor.h"

// Processor::Processor(vector<string> stat_cpu){

// }

float Processor::Utilization() {
  //   int PrevIdle = previdle_ + previowait_;
  //   int Idle = idle_ + iowait_;

  //   int PrevNonIdle =
  //       prevuser_ + prevnice_ + prevsystem_ + previrq_ + prevsoftirq_ +
  //       prevsteal_;
  //   int NonIdle = user_ + nice_ + system_ + irq_ + softirq_ + steal_;

  //   int PrevTotal = PrevIdle + PrevNonIdle;
  //   int Total = Idle + NonIdle;

  //   // differentiate: actual value minus the previous one
  //   int totald = Total - PrevTotal;
  //   int idled = Idle - PrevIdle;

  //   float CPU_Percentage = (totald - idled) / totald;
  return 0.0;
}