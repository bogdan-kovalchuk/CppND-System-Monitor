#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseMeminfoValue;

  const std::string meminfo =
      "MemTotal:       16384000 kB\n"
      "MemFree:         8192000 kB\n"
      "MemAvailable:   12288000 kB\n"
      "Buffers:          512000 kB\n"
      "Cached:          4096000 kB\n"
      "SwapTotal:       2048000 kB\n"
      "SwapFree:        2048000 kB\n";

  assert(ParseMeminfoValue(meminfo, "SwapTotal") == "2048000");
  assert(ParseMeminfoValue(meminfo, "SwapFree") == "2048000");
  std::printf("ParseMeminfoValue full-line match for Swap keys passed\n");

  assert(ParseMeminfoValue(meminfo, "Total").empty());
  assert(ParseMeminfoValue(meminfo, "Free").empty());
  assert(ParseMeminfoValue(meminfo, "Cache").empty());
  assert(ParseMeminfoValue(meminfo, "Cached") == "4096000");
  std::printf("ParseMeminfoValue suffix-only keys do not match\n");

  const std::string tricky =
      "VmSizeExtra:\t  999 kB\n"
      "VmPeak:\t  100 kB\n"
      "VmSize:\t  200 kB\n";
  assert(ParseMeminfoValue(tricky, "VmSize") == "200");
  assert(ParseMeminfoValue(tricky, "Vm").empty());
  assert(ParseMeminfoValue(tricky, "Peak").empty());
  std::printf("ParseMeminfoValue prefix collision avoided\n");

  const std::string embedded =
      "XMemTotal:\t999 kB\n"
      "MemTotal:\t16000 kB\n";
  assert(ParseMeminfoValue(embedded, "MemTotal") == "16000");
  assert(ParseMeminfoValue(embedded, "XMemTotal") == "999");
  std::printf("ParseMeminfoValue embedded prefix does not cross-match\n");

  std::printf("All ParseMeminfoValue prefix-safety tests passed.\n");
  return 0;
}
