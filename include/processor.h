#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  void UpdateCpuUtilization(vector<string> stat_cpu);
  float Utilization();

 private:
  float cpu_utilization_ = 0.0;
  int prevuser_ = 0;
  int prevnice_ = 0;
  int prevsystem_ = 0;
  int previdle_ = 0;
  int previowait_ = 0;
  int previrq_ = 0;
  int prevsoftirq_ = 0;
  int prevsteal_ = 0;
  int prevguest_ = 0;
  int prevguest_nice_ = 0;
};

#endif