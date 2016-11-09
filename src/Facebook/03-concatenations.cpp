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
void get_input(map<string,int> &words, int &num_words, string &line) {

	string words_line;

	while (words_line.empty()) {
		getline(cin, words_line);
	}

	istringstream words_in(words_line);
	string curr_word;

	num_words = 0;
	while (words_in >> curr_word) {
		words[curr_word]++;
		++num_words;
	}

	line = string();
	while(line.empty()) {
		getline(cin, line);
	}

}

int get_substr(map<string,int> &words, int num_words, string &line) {

	if (words.empty()) {
		throw runtime_error("No words list supplied.");
	}

	int word_size = words.begin()->first.size();

	vector<int> start_indexes;

	// Maintaining a record of all starting indexes of interest.
	for(int i=0; i < line.size(); i++) {
		string curr_sub_str = line.substr(i, word_size);

		if (words.count(curr_sub_str) > 0) {
			start_indexes.push_back(i);
			// cout << "starting index " << i << endl;
		}
	}

	// full_length_indexes contain all index positions whose next (num_word-1)
	// positions are also words.
	vector<int> full_length_indexes;
	set<int> all_indexes( start_indexes.begin(), start_indexes.end());

	// cout << "start_indexes.size() = " << start_indexes.size() << endl;

	for (int i = 0; i <= (start_indexes.size() - num_words); i++) {


		int curr_index = start_indexes[i];
		all_indexes.erase(curr_index);

		// cout << "Starting with index " <<  curr_index << endl;
		
		int j = 1;
		for( ; j < num_words; j++) {

			int expected_index = (curr_index + word_size);
	
			// check to see if jth index is in all_indexes.
			// If not, then we break out.
			if (all_indexes.count(expected_index) <= 0) {
				// cout << "Did not find expected index " << expected_index << endl;
				break;
			}
		}

		// Ok. j has full count. start_indexes should be considered further
		if (j >=  num_words) {
			full_length_indexes.push_back(start_indexes[i]);
			// cout << "full_length_indexes " << start_indexes[i] << endl;
		}
	}

	// Final_indexes contains all positions that contain num_words valid words
	// in a sequence. Lets now check to see if they are the right words.
	vector<int> final_indexes;

	for(int i = 0; i < full_length_indexes.size(); i++) {
		
		int curr_index = full_length_indexes[i];
		map<string, int> tmp_words(words);
		int j = 0;

		for(j = 0; j < num_words; j++) {

			int jth_index = curr_index + (j*word_size);
			string jth_word = line.substr(jth_index, word_size);

			// Note that this word definitely exists in the map;
			// Check its current count; If it less than/zero, then we have
			// already used it up.
			if (tmp_words[jth_word] <= 0) {
				break;
			}
			
			tmp_words[jth_word]--;
		}

		// Since the string is guaranteed to exist only once, we return back
		// the index immediately.
		if (j >= num_words) {
			return curr_index;
		}
	}

	throw runtime_error("Could not find index.");
	return -1;
}

// =======================================================================================

int main(int argc, const char **argv) {

	map<string,int> words;
	int num_words = 0;
	string line;

	get_input(words, num_words, line);
	// cout  << "num_words =  " << num_words << endl;

	cout << get_substr(words, num_words, line) << endl;
}

// =======================================================================================

