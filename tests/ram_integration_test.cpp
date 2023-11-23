#include "linux_parser.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdio>
#include <string>
#include <unistd.h>

int main() {
  using LinuxParser::ParseStatusValue;

  const std::string status_normal =
      "Name:\tbash\n"
      "State:\tS (sleeping)\n"
      "VmSize:\t  21740 kB\n"
      "VmRSS:\t   5000 kB\n";
  std::string val = ParseStatusValue(status_normal, "VmSize");
  assert(val == "21740");
  bool numeric = std::all_of(val.begin(), val.end(), ::isdigit);
  assert(numeric);
  std::printf("Ram integration: normal VmSize extraction passed\n");

  const std::string status_no_vm =
      "Name:\tkthread\n"
      "State:\tS (sleeping)\n";
  val = ParseStatusValue(status_no_vm, "VmSize");
  assert(val.empty());
  std::printf("Ram integration: missing VmSize returns empty\n");

  const std::string status_non_numeric =
      "VmSize:\tunknown kB\n";
  val = ParseStatusValue(status_non_numeric, "VmSize");
  assert(val == "unknown");
  bool is_num = std::all_of(val.begin(), val.end(), ::isdigit);
  assert(!is_num);
  std::printf("Ram integration: non-numeric VmSize detected\n");

  const std::string status_zero =
      "VmSize:\t0 kB\n";
  val = ParseStatusValue(status_zero, "VmSize");
  assert(val == "0");
  numeric = std::all_of(val.begin(), val.end(), ::isdigit);
  assert(numeric);
  std::printf("Ram integration: zero VmSize passed\n");

  const std::string status_large =
      "VmSize:\t16384000 kB\n";
  val = ParseStatusValue(status_large, "VmSize");
  assert(val == "16384000");
  assert(LinuxParser::ParseRamMb(val) == "16000");
  std::printf("Ram integration: large VmSize to MB conversion passed\n");

  const std::string current_ram = LinuxParser::Ram(getpid());
  assert(!current_ram.empty());
  assert(std::all_of(current_ram.begin(), current_ram.end(),
                     [](unsigned char ch) { return std::isdigit(ch); }));
  assert(LinuxParser::ParseLong(current_ram, -1) > 0);
  std::printf("Ram reads numeric VmSize for the current process\n");

  std::printf("All Ram integration tests passed.\n");
  return 0;
}
