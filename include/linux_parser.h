#ifndef SYSTEM_PARSER_H
#define SYSTEM_PARSER_H

#include <fstream>
#include <regex>
#include <string>

namespace LinuxParser {

// Proc filesystem parser approach:
// - Stream-based functions read /proc files line-by-line using istringstream.
//   Time complexity: O(n) where n is file size. Space: O(1) per call.
// - String-based helpers (ParseStatField, ParseStatusValue) operate on
//   pre-loaded content, enabling unit testing with synthetic data.
//   ParseStatField: O(f) where f is field index (scans tokens after comm).
//   ParseStatusValue: O(k) where k is content size (linear search for key).
// Both approaches handle malformed input gracefully with fallback values.

// Paths
const std::string kProcDirectory{"/proc/"};
const std::string kCmdlineFilename{"/cmdline"};
const std::string kCpuinfoFilename{"/cpuinfo"};
const std::string kStatusFilename{"/status"};
const std::string kStatFilename{"/stat"};
const std::string kUptimeFilename{"/uptime"};
const std::string kMeminfoFilename{"/meminfo"};
const std::string kVersionFilename{"/version"};
const std::string kOSPath{"/etc/os-release"};
const std::string kPasswordPath{"/etc/passwd"};

// System
float MemoryUtilization();
long UpTime();
std::vector<int> Pids();
int TotalProcesses();
int RunningProcesses();
std::string OperatingSystem();
std::string Kernel();

// CPU
std::vector<std::string> CpuUtilization();
std::vector<std::string> CpuUtilization(int pid);

// Processes
std::string Command(int pid);
std::string Ram(int pid);
std::string Uid(int pid);
std::string User(int pid);
long UpTime(int pid);

std::string ParseStatField(const std::string& stat_line, int field_index);
std::string ParseStatusValue(const std::string& status_content,
                             const std::string& key);
long ParseLong(const std::string& s, long fallback = 0);
std::string ParseCmdline(const std::string& raw_cmdline);
std::string ParseMeminfoValue(const std::string& meminfo_content,
                              const std::string& key);
int ParsePid(const std::string& stat_line);
std::string ParseRamMb(const std::string& ram_kb);
std::string ParseUid(const std::string& status_content);
std::string ParseKernel(const std::string& version_line);
std::string ParseOperatingSystem(const std::string& os_release_content);
float ParseMemoryUtilization(const std::string& meminfo_content);
std::string ParseUser(const std::string& passwd_content, const std::string& uid);
float ComputeCpuUtilization(const std::vector<std::string>& cpu_data);
float ComputeProcessorUtilization(int user, int nice, int system, int idle,
                                  int iowait, int irq, int softirq, int steal,
                                  int prev_user, int prev_nice, int prev_system,
                                  int prev_idle, int prev_iowait, int prev_irq,
                                  int prev_softirq, int prev_steal,
                                  bool first_call);
};  // namespace LinuxParser

#endif