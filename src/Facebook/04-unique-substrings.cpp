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
void get_input(string &input) {

	string line;

	// Skip empty lines.
	while(line.empty()) {
		getline(cin, line);
	}

	istringstream line_in(line);
	line_in >> input;
}

int num_unique_substrings(string &line) {

	// Use set to store sub-strings. This would automatically eliminate duplicates
	set<string> substr_set;

	for(int i = 0; i < line.size(); i++) {

		int max_size = (line.size() - i);

		for (int j = 1; j <= max_size; j++) {
			string curr = line.substr(i, j);
			substr_set.insert(curr);
		}
	}

	return substr_set.size();
}

// =======================================================================================

int main(int argc, const char **argv) {

	string input;
	get_input(input);

	cout << num_unique_substrings(input) << endl;
}

// =======================================================================================
