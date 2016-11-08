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

struct TestCase {

	public:
		const int N;
		const int K;
		vector<int> pos_in;

		TestCase(const int n, const int k): N(n), K(k), pos_in(N, -1) {}

		int compute_num_ways();

	private:
		bool compute_rec(vector<int> pos, const int pos_index, int &result);
		bool pos_ok(const vector<int> &pos, const int pos_index, const int new_pos);

};


// new_pos is the tentative position for pos_index.
bool TestCase::pos_ok(const vector<int> &pos, const int pos_index, const int new_pos) {

	// All positions are open for the first king.
	if (pos_index == 0) {
		return true;	
	}

	// At this point, pos_index > 0.
	
	// Checking against all positions till (pos_index-1);
	for (int i = 0; i < pos_index; i++) {
		int curr_king_pos = pos[i];

		if (new_pos == curr_king_pos) {
			return false;
		}
	}

	// Special check for previous king. It should not share corner.
	int prev_king_pos = pos[(pos_index - 1)] ;

	// Current position cannot be adjacent to previous king.
	if (abs(new_pos - prev_king_pos) == 1) {
		return false;
	}

	return true;
}

// TODO: Remove the pos vector passed in as-value. Pass it in as reference
// OR, dont pass it in at all.
bool TestCase::compute_rec(vector<int> pos, const int pos_index, int &result) {

	// End of recursion. All kings placed correctly.
	if (pos_index >= pos.size()) {
		++result;
		return true;
	}

	// Check all positions from 0 to N for pos_index king.
	for(int curr_pos = 0; curr_pos < N; curr_pos++) {

		if (pos_ok(pos, pos_index, curr_pos)) {

				// Note the position of the latest king.
				pos[pos_index] = curr_pos;

				compute_rec(pos, (pos_index+1), result);
		}
	}

	return false;
}

int TestCase::compute_num_ways() {

	int result = 0;

	// Start computing positions for Kth index (we have positions from 0 ..
	// K-1)
	compute_rec(pos_in, K, result);

	return result;
}

// =======================================================================================

TestCase* get_testcase() {

	string first_line, line;
	int N = -1, K = -1; 
	TestCase *result = NULL;

	getline(cin, first_line);
	istringstream first_line_in(first_line);

	first_line_in >> N >> K;
	result = new TestCase(N, K);

	// Check if any positions have been given.
	// If no positions have been given, the next line belongs to a new test
	// case.
	if (K == 0) {
		return result;
	}

	// All the positions are specified on a single line.
	getline(cin, line);
	istringstream line_in(line);

	for (int i = 0; i < K; i++) {
		int curr_pos = 0;

		line_in >> curr_pos;
		result->pos_in[i] = curr_pos;
	}

	return result;
}

void get_input(vector<TestCase*> &tests) {

	string line;
	int num_cases = -1;

	getline(cin, line);
	istringstream line_in(line);

	line_in >> num_cases;
	if (num_cases <= 0) {
		throw runtime_error("No input cases");
	}

	for (int i = 0; i < num_cases; i++) {
		TestCase *curr_case = NULL;

		curr_case = get_testcase();
		if (curr_case == NULL) {
			throw runtime_error("Error in creating test case.");
		}
		
		tests.push_back(curr_case);
	}
}

// =======================================================================================

int main(int argc, const char **argv) {

	vector<TestCase *> tests;
	get_input(tests);

	// Solve all test cases
	for(int i = 0 ; i < tests.size(); i++) {

		// TODO: Do that weird modulo if needed.
		TestCase *curr_test = tests[i];
		cout << curr_test->compute_num_ways() << endl; 
	}

	// Free up all resources
	for(int i = 0 ; i < tests.size(); i++) {
		TestCase *curr_test = tests[i];

		tests[i] = NULL;
		delete curr_test;
	}

}
