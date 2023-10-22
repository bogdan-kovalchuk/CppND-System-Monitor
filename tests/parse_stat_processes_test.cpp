#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseStatProcesses;

  const std::string stat =
      "cpu  10132852 1032843 6713288 32498698 182992 135472 95874 0 0 0\n"
      "cpu0 1329876 108936 887672 3877116 24970 18709 23153 0 0 0\n"
      "intr 341296423 216 7 0 0\n"
      "ctxt 652221234\n"
      "btime 1699901234\n"
      "processes 42567\n"
      "procs_running 3\n"
      "procs_blocked 0\n"
      "softirq 105844804 0\n";

  assert(ParseStatProcesses(stat, "processes") == 42567);
  assert(ParseStatProcesses(stat, "procs_running") == 3);
  assert(ParseStatProcesses(stat, "procs_blocked") == 0);
  std::printf("ParseStatProcesses standard stat keys passed\n");

  assert(ParseStatProcesses(stat, "missing") == 0);
  assert(ParseStatProcesses(stat, "procs") == 0);
  std::printf("ParseStatProcesses missing key returns zero\n");

  assert(ParseStatProcesses("", "processes") == 0);
  std::printf("ParseStatProcesses empty content returns zero\n");

  const std::string malformed =
      "processes abc\n"
      "procs_running xyz\n";
  assert(ParseStatProcesses(malformed, "processes") == 0);
  assert(ParseStatProcesses(malformed, "procs_running") == 0);
  std::printf("ParseStatProcesses non-numeric values return zero\n");

  const std::string negative =
      "processes -1\n";
  assert(ParseStatProcesses(negative, "processes") == 0);
  std::printf("ParseStatProcesses negative value returns zero\n");

  const std::string no_value =
      "processes\n";
  assert(ParseStatProcesses(no_value, "processes") == 0);
  std::printf("ParseStatProcesses key without value returns zero\n");

  std::printf("All ParseStatProcesses tests passed.\n");
  return 0;
}
