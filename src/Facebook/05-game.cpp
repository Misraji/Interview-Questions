#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <sstream>
using std::istringstream;

#include <string>
using std::string;
using std::getline;

#include <vector>
using std::vector;

#include <map>
using std::map;

#include <set>
using std::set;

#include <algorithm>
using std::sort;
using std::swap;
using std::min;
using std::max;

#include <utility>
using std::pair;

// =======================================================================================
//
void get_input(vector<int> &test_cases) {

	string line;

	// skip empty lines;
	while (line.empty()) {
		getline(cin, line);
	}

	istringstream line_in(line);
	int num_cases = 0;

	line_in >> num_cases;

	for(int i=0; i < num_cases; ++i) {

		// Delete existing contents
		line = string();

		// skip empty lines;
		while (line.empty()) {
			getline(cin, line);
		}

		istringstream num_in(line);
		int val = 0;

		num_in >> val;
		test_cases.push_back(val);
	}
}

// =======================================================================================

int main(int argc, const char **argv) {

	vector<int> test_cases;

	get_input(test_cases);

}
