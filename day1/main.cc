#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <optional>

#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

// maybe KNP would work here, but we are doing brute force
optional<pair<int, int>> value_found(const string& line, const int index) {
  vector<string> patterns = {
    "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
  };

  unordered_map<string, int> dict = {
    {"one", 1}, {"two", 2}, {"three", 3},
    {"four", 4}, {"five", 5}, {"six", 6},
    {"seven", 7}, {"eight", 8}, {"nine", 9}};

  int rest_of_a_string_len = line.size() - index;

  for(const auto& pattern : patterns) {
    if(rest_of_a_string_len < pattern.size()) {
      continue;
    }

    // try to match the string
    for(int i = 0; i < pattern.size(); i++) {
      bool match = true;

      for(int i = 0; i < pattern.size(); i++) {
        if(pattern[i] != line[index + i]) {
          match = false;
          break;
        }
      }

      if(match) {
        cout << "Found: " << pattern << " " << dict[pattern] << " " <<  pattern.size() << endl;
        return {{ dict[pattern], 0 }};
      }
    }
  }

  return std::nullopt;
}

cpp_int get_value(const string& line) {
  bool first = true;
  int first_value = 0;
  int last_value = 0;

  for(int i = 0; i < line.size(); i++) {
    char c = line[i];

    if(!isdigit(c)) {
      auto val = value_found(line, i);

      if(val.has_value()) {
        auto [value, cursor_shift] = val.value();

        if(first) {
          first = false;
          first_value = value;
        }

        last_value = value;
        i += cursor_shift;
      }
    } else {
      if(first) {
        first = false;
        first_value = c - '0';
      }

      last_value = c - '0';
    }
  }

  cpp_int value = first_value * 10 + last_value;
  return value;
}

int main(int argc, char *argv[]) {
  std::ifstream file("input.txt");
  std::string line;

  cpp_int total = 0;
  while (std::getline(file, line)) {
     cout << line << endl;
     cpp_int v = get_value(line);
     total += v;
     cout << v << endl;
     cout << total << endl;
  }

  cout << total << endl;

  return 0;
}
