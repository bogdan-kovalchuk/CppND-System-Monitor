#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  using LinuxParser::ParseUid;

  const std::string normal =
      "Name:\tbash\n"
      "State:\tS (sleeping)\n"
      "Uid:\t1000\t1000\t1000\t1000\n"
      "Gid:\t1000\t1000\t1000\t1000\n";
  assert(ParseUid(normal) == "1000");
  std::printf("ParseUid normal case passed\n");

  const std::string root =
      "Name:\tinit\n"
      "Uid:\t0\t0\t0\t0\n";
  assert(ParseUid(root) == "0");
  std::printf("ParseUid root process passed\n");

  assert(ParseUid("").empty());
  std::printf("ParseUid empty content returns empty\n");

  const std::string no_uid =
      "Name:\ttest\n"
      "State:\tS\n";
  assert(ParseUid(no_uid).empty());
  std::printf("ParseUid missing Uid key returns empty\n");

  const std::string uid_with_tabs =
      "Uid:\t  42\t42\t42\t42\n";
  assert(ParseUid(uid_with_tabs) == "42");
  std::printf("ParseUid with leading whitespace in value passed\n");

  const std::string uid_first_match =
      "Uid:\t100\n"
      "Uid:\t200\n";
  assert(ParseUid(uid_first_match) == "100");
  std::printf("ParseUid returns first match\n");

  std::printf("All ParseUid tests passed.\n");
  return 0;
}
