#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using boost::multiprecision::cpp_int;

cpp_int get_value(const string& line) {
  bool first = true;
  int first_value = 0;
  int last_value = 0;

  for(const auto c : line) {
    if(isdigit(c)) {
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
     cpp_int v = get_value(line);
     total += v;
     cout << line << endl;
     cout << v << endl;
     cout << total << endl;
  }

  cout << total << endl;

  return 0;
}
