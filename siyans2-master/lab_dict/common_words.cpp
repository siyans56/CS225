/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        std::ptr_fun<int, int>(&std::ispunct));
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());
    //file_word_maps is now the size of the amount of files we have

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current
        // file
        vector<string> words = file_to_vector(filenames[i]);

        for (size_t j = 0; j < words.size(); j++) {
          if (file_word_maps[i].find(words[j]) != file_word_maps[i].end()) { //already exists in map, update freq
            file_word_maps[i].find(words[j])->second = file_word_maps[i].find(words[j])->second + 1;
          }
          else { //create new entry
            file_word_maps[i][words[j]] = 1;
          }
        }
    }
}

void CommonWords::init_common()
{
  for (size_t i = 0; i < file_word_maps.size(); i++) {
      for (auto & key_val : file_word_maps[i]) { //make an iterator to go thru each map
      // for (map<string, int>::iterator key_val = file_word_maps[i].begin(); it != file_word_maps[i].end(); ++it) {
        if (common.find(key_val.first) != common.end()) { //already exists in map, update freq
          common.find(key_val.first)->second = common.find(key_val.first)->second + 1;
        }
        else { //create new entry
          common[key_val.first] = 1;
        }
      }
      /* Your code goes here! */
      //have a word vector that contains all words in current file.
      //Need to calculate the frequencies and make that the val

  }
//   for (auto & file : file_word_maps) {
//   for (auto & word : file) {
//     common[word.first]++;
//   }
// }

}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    vector<string> out;
    /* Your code goes here! */
    bool toinsert = true;
    for (auto & key_val : common) { //for every common word
      if (key_val.second == file_word_maps.size()) { //need to check if word is IN EVERY file
        //THEN NEED TO CHECK IF IN EACH OF THOSE FILES IF THE FREQ >= N
        toinsert = true;
        for (auto & file : file_word_maps) {
          if (file.find(key_val.first)->second < n) {
            toinsert = false;
            break;
          }
        }
        if (toinsert) out.push_back(key_val.first);
      }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
