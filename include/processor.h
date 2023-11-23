#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <cstdint>
#include <string>
#include <vector>

#include "linux_parser.h"

using std::string;
using std::vector;

class Processor {
 public:
  float Utilization();

 private:
  std::uint64_t prev_user_ = 0;
  std::uint64_t prev_nice_ = 0;
  std::uint64_t prev_system_ = 0;
  std::uint64_t prev_idle_ = 0;
  std::uint64_t prev_iowait_ = 0;
  std::uint64_t prev_irq_ = 0;
  std::uint64_t prev_softirq_ = 0;
  std::uint64_t prev_steal_ = 0;
  bool initialized_ = false;
};

#endif
