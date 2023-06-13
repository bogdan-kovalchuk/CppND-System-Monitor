#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseKernel;

  const std::string normal =
      "Linux version 5.15.0-91-generic (buildd@lcy02-amd64-045) "
      "(gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0, GNU ld_version) "
      "#101-Ubuntu SMP Tue Nov 14 13:30:08 UTC 2023";
  assert(ParseKernel(normal) == "5.15.0-91-generic");
  std::printf("ParseKernel normal version line passed\n");

  const std::string minimal = "Linux version 6.1.0";
  assert(ParseKernel(minimal) == "6.1.0");
  std::printf("ParseKernel minimal version line passed\n");

  assert(ParseKernel("").empty());
  std::printf("ParseKernel empty line returns empty\n");

  assert(ParseKernel("Linux").empty());
  std::printf("ParseKernel single token returns empty\n");

  assert(ParseKernel("Linux version").empty());
  std::printf("ParseKernel two tokens returns empty\n");

  const std::string custom = "FreeBSD version 13.2-RELEASE";
  assert(ParseKernel(custom) == "13.2-RELEASE");
  std::printf("ParseKernel non-Linux version passed\n");

  std::printf("All ParseKernel tests passed.\n");
  return 0;
}
