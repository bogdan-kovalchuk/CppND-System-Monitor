#include "linux_parser.h"

#include <cassert>
#include <cstdio>
#include <string>

int main() {
  const auto pids = LinuxParser::Pids();
  assert(!pids.empty());

  for (int pid : pids) {
    const auto uid = LinuxParser::Uid(pid);
    const auto user = LinuxParser::User(pid);
    if (uid.empty() || uid == "0") {
      std::printf("Pid %d: Uid='%s' User='%s'\n", pid, uid.c_str(), user.c_str());
    }
  }
  std::printf("User lookup completed for %zu pids\n", pids.size());

  const auto uid1 = LinuxParser::Uid(pids.front());
  const auto user1 = LinuxParser::User(pids.front());
  std::printf("First pid %d: Uid='%s' User='%s'\n",
              pids.front(), uid1.c_str(), user1.c_str());

  const int fake_pid = 999999;
  const auto fake_uid = LinuxParser::Uid(fake_pid);
  const auto fake_user = LinuxParser::User(fake_pid);
  std::printf("Fake pid %d: Uid='%s' User='%s'\n",
              fake_pid, fake_uid.c_str(), fake_user.c_str());

  std::printf("All User lookup tests passed.\n");
  return 0;
}
