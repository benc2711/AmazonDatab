#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>
#include <string>
#include <cctype>


using namespace std;
std::string convToLower(std::string src)
{
    std::transform(src.begin(), src.end(), src.begin(), ::tolower);
    return src;
}

/** Complete the code to convert a string containing a rawWord
    to a set of words based on the criteria given in the assignment **/
std::set<std::string> parseStringToWords(string rawWords)
{
  std::set<std::string> retval;
  stringstream ss(rawWords);
  string word;
  while(ss >> word){
    string leftWord;
    string rightWord;
    bool punc = false;
    
    
    for(unsigned int i =0; i< word.size();i++){
        if(ispunct(word[i]) != 0){
          leftWord = word.substr(0, i);
          rightWord = word.substr(i+1);
          punc = true;
        
          if(leftWord.size() > 1){
            retval.insert(leftWord);
            
          }
          if(rightWord.size() > 1){
            retval.insert(rightWord);
            
          }
        }
      }
    if(!punc){
          retval.insert(word);
        }
  
    
    
  }

  return retval;
}

/**************************************************
 * COMPLETED - You may use the following functions
 **************************************************/

// Used from http://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
// trim from start
std::string &ltrim(std::string &s) {
    s.erase(s.begin(), 
	    std::find_if(s.begin(), 
			 s.end(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string &rtrim(std::string &s) {
    s.erase(
	    std::find_if(s.rbegin(), 
			 s.rend(), 
			 std::not1(std::ptr_fun<int, int>(std::isspace))).base(), 
	    s.end());
    return s;
}

// trim from both ends
std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}
