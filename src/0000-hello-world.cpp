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

int main(int argc, const char **argv) {

	map<int, vector<string> > dict;
	vector<vector<string> > secrets;

	get_input(dict, secrets);

}
