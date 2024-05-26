#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid) : pid_(pid) {
  command_ = LinuxParser::Command(pid);
  ram_ = LinuxParser::ParseRamMb(LinuxParser::Ram(pid));
  user_ = LinuxParser::User(pid);
  up_time_ = LinuxParser::UpTime() - LinuxParser::UpTime(pid) / sysconf(_SC_CLK_TCK);
  cpu_utilization_ = LinuxParser::ComputeCpuUtilization(LinuxParser::CpuUtilization(pid));
}

int Process::Pid() { return pid_; }

float Process::CpuUtilization() { return cpu_utilization_; }

string Process::Command() { return command_; }

string Process::Ram() { return ram_; }

string Process::User() { return user_; }

long int Process::UpTime() { return up_time_; }

bool Process::operator>(Process const& a) const {
  if (cpu_utilization_ != a.cpu_utilization_)
    return cpu_utilization_ > a.cpu_utilization_;
  return pid_ > a.pid_;
}