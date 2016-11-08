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
		bool compute_rec(const int pos_index, int &result);
		int compute_inc(); 

		bool pos_ok(const int pos_index, const int new_pos);

};


// new_pos is the tentative position for pos_index.
bool TestCase::pos_ok(const int pos_index, const int new_pos) {

	// All positions are open for the first king.
	if (pos_index == 0) {
		return true;	
	}

	// At this point, pos_index > 0.
	
	// Checking against all positions till (pos_index-1);
	for (int i = 0; i < pos_index; i++) {
		int curr_king_pos = pos_in[i];

		if (new_pos == curr_king_pos) {
			return false;
		}
	}

	// Special check for previous king. It should not share corner.
	int prev_king_pos = pos_in[(pos_index - 1)] ;

	// Current position cannot be adjacent to previous king.
	if (abs(new_pos - prev_king_pos) == 1) {
		return false;
	}

	return true;
}

// TODO: Remove the pos vector passed in as-value. Pass it in as reference
// OR, dont pass it in at all.
bool TestCase::compute_rec(const int pos_index, int &result) {

	// End of recursion. All kings placed correctly.
	if (pos_index >= pos_in.size()) {
		++result;
		return true;
	}

	// Check all positions from 0 to N for pos_index king.
	for(int curr_pos = 0; curr_pos < N; curr_pos++) {

		if (pos_ok(pos_index, curr_pos)) {

				// Note the position of the latest king.
				pos_in[pos_index] = curr_pos;
				compute_rec((pos_index+1), result);

				// Revert back the position of the latest kind.
				pos_in[pos_index] = -1;
		}
	}

	return false;
}


int TestCase::compute_inc() {

	int result = 0;
	int curr_king = K;

	// This is the case when input has been completely specified.
	if (K >= pos_in.size()) {
		// TODO: Check this. Should we return 1 or 0??
		return 1;
	}

	// Check all positions from K to N for pos_index king.
	while (curr_king >= K) {

		if (curr_king >= N) {
			// We finished one solution.
			result++;
			curr_king--;

			// Revert back current king position as far as possible.
			// Note that we could have multiple kings in Nth position.
			while ((curr_king >= K) && (pos_in[curr_king] >= N)) {
				// Reset it back.
				pos_in[curr_king] = -1;
				curr_king--;
			}
		
		} else {

			// Lets try the next position of curr_king.
			int curr_king_pos = ++pos_in[curr_king];
		
			if (curr_king_pos >= N) {

				// We are out of options for this king. Retreat back.
				pos_in[curr_king] = -1;
				curr_king--;

			} else if (pos_ok(curr_king, curr_king_pos)) {
				// Ok. We have a valid position. Lets move on to the next
				// king.
				curr_king++;
			}
		}
	}

	return result;
}

int TestCase::compute_num_ways() {

	int result = 0;

	// Start computing positions for Kth index (we have positions from 0 ..
	// K-1), This is the recursive method.
	// compute_rec(K, result);

	result = compute_inc();
	return result;
}

// =======================================================================================

TestCase* get_testcase() {

	string first_line, line;
	int N = -1, K = -1; 
	TestCase *result = NULL;

	// Ignore all empty lines.
	while (first_line.empty()) {
		getline(cin, first_line);
	}

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
	// Ignore all empty lines.
	while (line.empty()) { 
		getline(cin, line);
	}
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

// =======================================================================================

