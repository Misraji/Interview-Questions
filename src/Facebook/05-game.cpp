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
int num_bits_set(int val) {

	int count = 0;

	while(val) {
		val = val & (val-1);
		count++;
	}

	return count;
}

int num_moves(const int start_val) {

	// cout << "start_val = " << start_val << endl;

	if (start_val == 0) {
		throw runtime_error("start val must be > 0");
	}

	// Actual algorithm variables.
	int moves = 0;
	int curr_val = start_val;
	int curr_num_bits = num_bits_set(start_val);

	// First determine power k;
	int two_power = 1;
	vector<int> valid_k; 
	bool start_val_power = false;

	while (two_power < start_val) {
		valid_k.push_back(two_power);
		two_power = two_power << 1;
	}

	if (two_power == start_val) {
		start_val_power = true;
	}

	// Reducing power by 1 to make it less than start_val;
	two_power = two_power >> 1;
	
	/*
	cout << "valid_k = ";
	for (int i=0; i < valid_k.size(); i++) {
		cout << valid_k[i] << ",";
	}
	cout << endl;
	*/

	if (start_val_power == false) {
		// TODO: Is there a different loop break condition??
		int max_k_index = valid_k.size()-1;
		for(int i= 0; i <= max_k_index; i++) {

			int two_power = valid_k[i];
			// n - 2^k
			int tmp_val = curr_val - two_power;
			int tmp_num_bits = num_bits_set(tmp_val);

			// Safety condition.
			if (tmp_val <= 0) {
				break;
			}

			if (tmp_num_bits == curr_num_bits ) {
				// tmp_val has same beauty as before.
				curr_val = tmp_val;
				moves++;

				// Recalculate new max_k_index;
				max_k_index = 0;
				while (valid_k[max_k_index] < curr_val) {
					max_k_index++;
				}
				max_k_index--;

				// Reset counter
				i = 0;
			}
		}

	} else {

		// TODO: Is there a different loop break condition??
		for(int i= valid_k.size()-1; i >= 0; i--) {

			int two_power = valid_k[i];
			// n - 2^k
			int tmp_val = curr_val - two_power;
			int tmp_num_bits = num_bits_set(tmp_val);

			// Safety condition.
			if (tmp_val <= 0) {
				break;
			}

			if (tmp_num_bits == curr_num_bits ) {
				// tmp_val has same beauty as before.
				curr_val = tmp_val;
				moves++;
			}
		}
	}

	return moves;
}

void solve(const int start_val) {

	int result = num_moves(start_val);

	if (result % 2) {
		cout << "First Player" << endl;

	} else {
		cout << "Second Player" << endl;
	}
}
// =======================================================================================

int main(int argc, const char **argv) {

	vector<int> test_cases;

	// Get all inputs;
	get_input(test_cases);

	for(int i = 0; i < test_cases.size(); i++) {
		solve(test_cases[i])	;
	}
}

// =======================================================================================

