#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include <vector>

using std::string;
using std::vector;

class Processor {
 public:
  //   Processor(vector<string> stat_cpu);
  float Utilization();

 private:
  int user_;
  int nice_;
  int system_;
  int idle_;
  int iowait_;
  int irq_;
  int softirq_;
  int steal_;
  int guest_;
  int guest_nice_;
};

#endif