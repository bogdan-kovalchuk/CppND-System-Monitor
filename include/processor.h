#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
#include <vector>

#include "linux_parser.h"

using std::stoi;
using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();

 private:
  int prev_user_ = 0;
  int prev_nice_ = 0;
  int prev_system_ = 0;
  int prev_idle_ = 0;
  int prev_iowait_ = 0;
  int prev_irq_ = 0;
  int prev_softirq_ = 0;
  int prev_steal_ = 0;
  int prev_guest_ = 0;
  int prev_guest_nice_ = 0;
};

#endif