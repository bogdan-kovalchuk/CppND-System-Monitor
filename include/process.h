#ifndef PROCESS_H
#define PROCESS_H

#include <linux_parser.h>

#include <string>

class Process {
 public:
  Process(int pid);
  int Pid();
  std::string User();
  std::string Command();
  float CpuUtilization();
  std::string Ram();
  long int UpTime();
  bool operator<(Process const& a) const;

 private:
  const int pid_;
  std::string user_;
  std::string command_;
  float cpu_utilization_;
  std::string ram_;
  long int up_time_;
};

#endif