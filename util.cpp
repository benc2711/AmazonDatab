#include <iostream>
#include <sstream>
#include <cctype>
#include <algorithm>
#include "util.h"
#include <set>
#include <string>

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
    if (rawWords.size() > 2){
    string lowerRaw = convToLower(word);
    bool containsPunc = false;
    for(unsigned int i =0; i< lowerRaw.size(); i++){
      if (lowerRaw[i] > 122 || lowerRaw[i]< 97){
        containsPunc = true;
      }
    }
    std::string left;
    std::string right;
    if(containsPunc){
      left = ltrim(rawWords);
      right = rtrim(rawWords);
    }
    if(left.size() > 1){
      retval.insert(left);
    }
    if(right.size() > 1){
      retval.insert(right);
    }
  }
  
    
    
  }
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
