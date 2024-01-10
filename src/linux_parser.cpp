#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

using std::stof;
using std::string;
using std::to_string;
using std::vector;

namespace {
int NumberOfProcesses(string skey) {
  int processes = 0;
  string key, line;
  std::ifstream stream(LinuxParser::kProcDirectory +
                       LinuxParser::kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == skey) {
        linestream >> processes;
        break;
      }
    }
  }
  return processes;
}
}  // namespace

string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

float LinuxParser::MemoryUtilization() {
  float used_memory = 0.0;       // relative
  float total_memory = 0.0;      // kB
  float available_memory = 0.0;  // kB
  float val;
  string line, key;

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> val;
      if (key == "MemTotal") {
        total_memory = val;
      } else if (key == "MemAvailable") {
        available_memory = val;
      }
    }
  }
  if (total_memory != 0.0) {
    used_memory = (total_memory - available_memory) / total_memory;
  }
  return used_memory;
}

long LinuxParser::UpTime() {
  long uptime = 0;  // seconds
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> uptime;
    }
  }
  return uptime;
}

vector<string> LinuxParser::CpuUtilization() {
  vector<string> stat_cpu;
  string key, value, line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "cpu") {
        while (linestream >> value) {
          stat_cpu.push_back(value);
        }
        break;
      }
    }
  }
  return stat_cpu;
}

int LinuxParser::TotalProcesses() { return NumberOfProcesses("processes"); }

int LinuxParser::RunningProcesses() {
  return NumberOfProcesses("procs_running");
}

string LinuxParser::Command(int pid) {
  string command;
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kCmdlineFilename);
  if (stream.is_open()) {
    std::getline(stream, command);
  }
  return command;
}

vector<string> LinuxParser::CpuUtilization(int pid) {
  vector<string> output;
  string value, seconds, line;
  int i = 1;
  // Extract uptime of the system in seconds
  std::ifstream stream_uptime(kProcDirectory + kUptimeFilename);
  if (stream_uptime.is_open()) {
    std::getline(stream_uptime, line);
    std::istringstream linestream(line);
    linestream >> seconds;
    output.push_back(seconds);
  }
  // Extract cpu utilization data from /proc/[PID]/stat
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    while (linestream >> value) {
      if (i == 14 || i == 15 || i == 16 || i == 17 || i == 22) {
        output.push_back(value);
      }
      i++;
    }
  }
  return output;
}

string LinuxParser::Ram(int pid) {
  string line, key, ram = "0";
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "VmSize:") {
        string raw;
        linestream >> raw;
        bool numeric = !raw.empty() &&
                       std::all_of(raw.begin(), raw.end(), ::isdigit);
        ram = numeric ? raw : "0";
        break;
      }
    }
  }
  return ram;
}

string LinuxParser::Uid(int pid) {
  string line, key, uid = "0";
  std::ifstream stream(kProcDirectory + std::to_string(pid) + kStatusFilename);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> key;
      if (key == "Uid:") {
        linestream >> uid;
        break;
      }
    }
  }
  return uid;
}

string LinuxParser::User(int pid) {
  string line, val, user;
  string uid = Uid(pid);
  std::ifstream stream(kPasswordPath);
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> val >> val;
      if (val == uid) {
        return user;
      }
    }
  }
  return user;
}

long LinuxParser::UpTime(int pid) {
  string line;
  std::ifstream stream(kProcDirectory + to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    string field22 = ParseStatField(line, 22);
    if (!field22.empty()) {
      return ParseLong(field22, 0);
    }
  }
  return 0;
}

string LinuxParser::ParseStatField(const string& stat_line, int field_index) {
  if (field_index < 1) return "";
  if (field_index == 1) {
    auto pos = stat_line.find('(');
    if (pos == string::npos) return "";
    string pid_str = stat_line.substr(0, pos);
    while (!pid_str.empty() && std::isspace(pid_str.back())) pid_str.pop_back();
    return pid_str;
  }
  if (field_index == 2) {
    auto open = stat_line.find('(');
    auto close = stat_line.rfind(')');
    if (open == string::npos || close == string::npos || close <= open)
      return "";
    return stat_line.substr(open + 1, close - open - 1);
  }
  auto close = stat_line.rfind(')');
  if (close == string::npos || close + 2 >= stat_line.size()) return "";
  string tail = stat_line.substr(close + 2);
  std::istringstream iss(tail);
  string token;
  int current = 3;
  while (iss >> token) {
    if (current == field_index) return token;
    ++current;
  }
  return "";
}

string LinuxParser::ParseStatusValue(const string& status_content,
                                     const string& key) {
  string search_key = key + ":";
  size_t pos = status_content.find(search_key);
  if (pos == string::npos) return "";
  size_t line_end = status_content.find('\n', pos);
  if (line_end == string::npos) line_end = status_content.size();
  string line = status_content.substr(pos, line_end - pos);
  std::istringstream iss(line);
  string k, val;
  iss >> k;
  iss >> val;
  return val;
}

long LinuxParser::ParseLong(const string& s, long fallback) {
  if (s.empty()) return fallback;
  try {
    size_t pos = 0;
    long val = std::stol(s, &pos);
    if (pos == 0) return fallback;
    return val;
  } catch (const std::exception&) {
    return fallback;
  }
}

string LinuxParser::ParseCmdline(const string& raw_cmdline) {
  string result = raw_cmdline;
  std::replace(result.begin(), result.end(), '\0', ' ');
  while (!result.empty() && result.back() == ' ') {
    result.pop_back();
  }
  return result;
}

string LinuxParser::ParseMeminfoValue(const string& meminfo_content,
                                      const string& key) {
  string search_key = key + ":";
  size_t pos = meminfo_content.find(search_key);
  if (pos == string::npos) return "";
  size_t line_end = meminfo_content.find('\n', pos);
  if (line_end == string::npos) line_end = meminfo_content.size();
  string line = meminfo_content.substr(pos, line_end - pos);
  std::istringstream iss(line);
  string k, val;
  iss >> k;
  iss >> val;
  return val;
}

int LinuxParser::ParsePid(const string& stat_line) {
  auto pos = stat_line.find('(');
  if (pos == string::npos || pos == 0) return -1;
  string pid_str = stat_line.substr(0, pos);
  while (!pid_str.empty() && std::isspace(pid_str.back())) pid_str.pop_back();
  if (pid_str.empty()) return -1;
  try {
    return std::stoi(pid_str);
  } catch (const std::exception&) {
    return -1;
  }
}
