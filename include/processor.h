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