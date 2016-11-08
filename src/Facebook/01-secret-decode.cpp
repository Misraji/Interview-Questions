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
void get_input(map<int, vector<string> > &valid_words, vector<vector<string> >&secrets) {

	string line;
	while (getline(cin, line)) {

		istringstream line_in(line);
		string word;

		line_in >> word;

		if (word == "//dict") {
			break;
		}
	}

	// Get all dictionary words here.
	// TODO: How do we deal with spaces and truncation
	while (getline(cin, line)) {

		// Using string stream to perform automatic truncation.
		istringstream line_in(line);
		string word;

		line_in >> word;

		if (word == "//secret") {
			break;
		}

		// Add word to dictionary.
		valid_words[word.size()].push_back(word);
	}

	// Now get all the secrets we want to decode.
	while (getline(cin, line)) {

		// Create new vector<string> for current secrets.
		secrets.push_back(vector<string>());

		vector<string> &curr_secrets = secrets[secrets.size()-1];

		// Using string stream to perform automatic truncation.
		istringstream line_in(line);
		string word;

		while (line_in >> word) {
			curr_secrets.push_back(word);
		}
	}
}

// =======================================================================================

class Solver {

	public:
		Solver(map<int, vector<string> > &d) : dict(d) {}

		void match(vector<string> &secret_line);

	private:
		bool match_rec(vector<string> &secret_line, int i , map<char, char> &solution);
		bool match_word(const string &from, const string &to, map<char, char> &solution);

		map<int, vector<string> > &dict;
};

bool match_partial(const string &partial, const string &to, vector<bool> &mask) {

	for (int i = 0; i < partial.size(); i++) {
		if (mask[i] && (partial[i] != to[i])) {
			return false;		
		}
	}
	return true;
}

bool Solver::match_word(const string &from, const string &to, map<char, char> &solution) {

	vector<bool> mask(to.size(), false);
	map<char, char> partial_sol;

	// Generate partial transformation based on current solution
	string partial(from);
	for(int i = 0; i < partial.size(); i++) {
		char curr = partial[i];
		if (solution.count(curr) > 0) {
			partial[i] = solution[curr];
			mask[i] = true;
		}
	}

	if (match_partial(partial, to, mask) == false) {
		return false;
	}

	for(int i=0; i < partial.size(); i++) {
		// Do only if current character has not been decoded.
		if (mask[i] == false) {
			
			char curr_secret = partial[i];
			char curr_decoded = to[i];

			if (partial_sol.count(curr_secret) > 0) {
				// If we have encountered this secret char before. Make sure its right.
				if (partial_sol[curr_secret] != curr_decoded) {
					// Current mapping is incompatible with previous mapping.
					// Abort this word processing.
					return false;
				}

				// Current mapping is consistent with previous mapping. Good.
				// Proceed.
				
			} else {
				// This is the first time we are encountering this mapping.
				// Proceed.
				partial_sol[curr_secret] = curr_decoded;
			}
		}
	}

	// Add partial_sol to existing solution.
	for(auto itr = partial_sol.begin(); itr != partial_sol.end(); itr++) {
		pair<char, char> tmp = *itr;
		solution[tmp.first] = tmp.second;
	}

	//  YAY. Word match succeeded.
	return true;
}

string decode_word(string secret, map<char, char> &solution) {
	
	string result(secret);

	for(int i = 0; i < result.size(); i++) {
		char curr = result[i];
		result[i] = solution[curr]; 
	}

	return result;
}

void print_output(vector<string> &secret_line, map<char, char> &solution) {

	for (int j = 0; j < secret_line.size(); j++) {
		cout << secret_line[j] << " ";
	}
	cout << "= ";

	for (int j = 0; j < secret_line.size(); j++) {
		cout << decode_word(secret_line[j], solution) << " ";
	}
	cout << endl;
}

bool Solver::match_rec(vector<string> &secret_line, int i , map<char, char> &solution) {

	if (i >= secret_line.size()) {
		// Recursive solution succeeded. Print output and leave.
		print_output(secret_line, solution);
		return true;
	}

	string &curr_secret = secret_line[i];
	vector<string> &possible_words = dict[curr_secret.size()];

	// Grab all possible words that can match and try them.
	for (int j = 0; j < possible_words.size(); j++) {

		string &curr_word = possible_words[i];

		// Generating a copy of the solution for testing word matching.
		map<char, char> tmp_solution(solution);
			
		if (match_word(curr_secret, curr_word, tmp_solution) ) {
			// if the word matched correctly, lets continue decoding other
			// words.
			if (match_rec(secret_line, (i+1), tmp_solution)) {
				return true;
			}
		}
	}

	// TODO: Throw exception here.
	return false;
}

void Solver::match(vector<string> &secret_line) {
	map<char, char> solution;
	bool success  = match_rec(secret_line, 0, solution);

	if (success == false) {
		throw runtime_error("Mapping failed.");
	}
}

// =======================================================================================

int main(int argc, const char **argv) {

	map<int, vector<string> > dict;
	vector<vector<string> > secrets;

	get_input(dict, secrets);

	Solver tmp(dict);

	for (int i = 0; i < secrets.size(); i++) {
		tmp.match(secrets[i]);
	}
	cout << "dict = " << dict.size() << endl;
	cout << "secrets = " << secrets.size() << endl;
}
