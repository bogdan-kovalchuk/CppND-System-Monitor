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
  // LinuxParser::Ram(pid);
  // LinuxParser::Uid(pid);
  // LinuxParser::User(pid);
  // LinuxParser::UpTime(pid);
}

int Process::Pid() { return pid_; }

float Process::CpuUtilization() { return cpu_utilization_; }

string Process::Command() { return command_; }

string Process::Ram() { return ram_; }

string Process::User() { return user_; }

long int Process::UpTime() { return up_time_; }

bool Process::operator<(Process const& a) const {
  return cpu_utilization_ < a.cpu_utilization_;
}