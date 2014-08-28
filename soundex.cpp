#include "soundex.h"
#include <cstring>
#include <algorithm>
#include <ctype.h>
#include <unordered_map>

using namespace std;

const char notADigit{'*'};

class consanantsToNumber: unary_function<char, char> {
public:
  result_type operator()(argument_type letter)
  {
      const unordered_map<char, char> encodings
      {
          {'b','1'}, {'f','1'}, {'p','1'}, {'v','1'},

          {'c','2'}, {'g','2'}, {'j','2'}, {'k','2'}, {'q','2'},
          {'s','2'}, {'x','2'}, {'z','2'}, {'k','2'},

          {'d','3'}, {'t','3'},

          {'l','4'},

          {'m','5'}, {'n','5'},

          {'r','6'}
      };
      auto encodeResult = encodings.find(tolower(letter));

      return encodeResult == encodings.end() ? (result_type) notADigit : (result_type) encodeResult->second;
  }
};


Soundex::Soundex()
{
}

string Soundex::encode(const string& word)
{
   return firstLetterToUpperCase(convertNonFirstLettersToNumbers(word));
}

string Soundex::firstLetterToUpperCase(const string& word)
{
    string newStr = word;
    newStr[0]=toupper(word[0]);
    return newStr;
}

string Soundex::convertNonFirstLettersToNumbers(const string& word)
{
   string numStr = word;
   transform(word.begin()+1,word.end(),numStr.begin()+1,::consanantsToNumber());
   return numStr;
}
