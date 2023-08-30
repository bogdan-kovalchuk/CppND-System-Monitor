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

  assert(ParseMeminfoValue(meminfo, "MemTotal") == "16384000");
  assert(ParseMeminfoValue(meminfo, "MemFree") == "8192000");
  assert(ParseMeminfoValue(meminfo, "MemAvailable") == "12288000");
  assert(ParseMeminfoValue(meminfo, "Buffers") == "512000");
  assert(ParseMeminfoValue(meminfo, "Cached") == "4096000");
  assert(ParseMeminfoValue(meminfo, "SwapTotal") == "2048000");
  assert(ParseMeminfoValue(meminfo, "SwapFree") == "2048000");
  std::printf("ParseMeminfoValue standard meminfo passed\n");

  assert(ParseMeminfoValue(meminfo, "Missing").empty());
  assert(ParseMeminfoValue(meminfo, "memtotal").empty());
  assert(ParseMeminfoValue(meminfo, "MEMTOTAL").empty());
  std::printf("ParseMeminfoValue missing key returns empty\n");

  const std::string sparse =
      "MemTotal:16384000 kB\n"
      "MemFree:    8192000 kB\n"
      "MemAvailable:  12288000 kB\n";
  assert(ParseMeminfoValue(sparse, "MemTotal") == "16384000");
  assert(ParseMeminfoValue(sparse, "MemFree") == "8192000");
  assert(ParseMeminfoValue(sparse, "MemAvailable") == "12288000");
  std::printf("ParseMeminfoValue varied whitespace passed\n");

  const std::string no_unit =
      "HugePages_Total:       0\n"
      "HugePages_Free:        0\n";
  assert(ParseMeminfoValue(no_unit, "HugePages_Total") == "0");
  assert(ParseMeminfoValue(no_unit, "HugePages_Free") == "0");
  std::printf("ParseMeminfoValue without kB unit passed\n");

  assert(ParseMeminfoValue("", "MemTotal").empty());
  std::printf("ParseMeminfoValue empty content returns empty\n");

  std::printf("All ParseMeminfoValue tests passed.\n");
  return 0;
}
