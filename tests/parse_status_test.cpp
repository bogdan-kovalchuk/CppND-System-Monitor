#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseStatusValue;

  const std::string tricky =
      "Name:\tUid: test\n"
      "State:\tS\n"
      "Uid:\t1000\n";
  assert(ParseStatusValue(tricky, "Uid") == "1000");
  assert(ParseStatusValue(tricky, "Name") == "Uid:");
  std::printf("ParseStatusValue key-in-value edge case passed\n");

  const std::string prefix =
      "VmSize:\t1234 kB\n"
      "VmRSS:\t5678 kB\n";
  assert(ParseStatusValue(prefix, "VmSize") == "1234");
  assert(ParseStatusValue(prefix, "VmRSS") == "5678");
  assert(ParseStatusValue(prefix, "Vm").empty());
  std::printf("ParseStatusValue prefix key safety passed\n");

  const std::string no_trailing_newline =
      "Name:\tproc1\n"
      "Uid:\t42";
  assert(ParseStatusValue(no_trailing_newline, "Uid") == "42");
  assert(ParseStatusValue(no_trailing_newline, "Name") == "proc1");
  std::printf("ParseStatusValue without trailing newline passed\n");

  const std::string duplicate_key =
      "Name:\tfirst\n"
      "Name:\tsecond\n";
  assert(ParseStatusValue(duplicate_key, "Name") == "first");
  std::printf("ParseStatusValue returns first match for duplicate keys\n");

  assert(ParseStatusValue("", "Name").empty());
  assert(ParseStatusValue("Name:\ttest\n", "Missing").empty());
  std::printf("ParseStatusValue empty and missing key cases passed\n");

  std::printf("All ParseStatusValue line-by-line tests passed.\n");
  return 0;
}
