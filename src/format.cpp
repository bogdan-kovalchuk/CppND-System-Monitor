#include "format.h"

#include <string>

using std::string;
using std::to_string;

namespace {
void add_zero(string& s) {
  if (s.length() < 2) {
    s = "0" + s;
  }
}
}  // namespace

string Format::ElapsedTime(long seconds) {
  string h = to_string(seconds / 3600);
  string m = to_string((seconds / 60) % 60);
  string s = to_string(seconds % 60);

  add_zero(h);
  add_zero(m);
  add_zero(s);

  return h + ":" + m + ":" + s;
}