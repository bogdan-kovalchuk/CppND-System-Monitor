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
  ram_ = std::to_string((int)(std::stoi(LinuxParser::Ram(pid)) / 1024));
  // LinuxParser::Uid(pid);
  // LinuxParser::User(pid);
  up_time_ = LinuxParser::UpTime(pid) / sysconf(_SC_CLK_TCK);
  CalculateCpuUtilization(LinuxParser::CpuUtilization(pid));
}

int Process::Pid() { return pid_; }

float Process::CpuUtilization() { return cpu_utilization_; }

string Process::Command() { return command_; }

string Process::Ram() { return ram_; }

string Process::User() { return user_; }

long int Process::UpTime() { return up_time_; }

bool Process::operator>(Process const& a) const {
  return (cpu_utilization_ > a.cpu_utilization_);
}

void Process::CalculateCpuUtilization(vector<string> cpu_utilization_data) {
  if (cpu_utilization_data.size() < 6) {
    cpu_utilization_ = 0.0;
    return;
  }
  int uptime = std::stoi(cpu_utilization_data[0]);
  int utime = std::stoi(cpu_utilization_data[1]);
  int stime = std::stoi(cpu_utilization_data[2]);
  int cutime = std::stoi(cpu_utilization_data[3]);
  int cstime = std::stoi(cpu_utilization_data[4]);
  int starttime = std::stoi(cpu_utilization_data[5]);

  int total_time = utime + stime + cutime + cstime;
  int seconds = uptime - (starttime / sysconf(_SC_CLK_TCK));
  cpu_utilization_ = (float)(total_time / sysconf(_SC_CLK_TCK)) / seconds;
}