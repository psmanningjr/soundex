#include "soundex.h"
#include <cstring>
#include <algorithm>
#include <ctype.h>

using namespace std;

class consanantsToNumber: unary_function<char, char> {
public:
  result_type operator()(argument_type letter)
  {
      char lowerLetter = tolower(letter);
      if (lowerLetter == 'b')
      {
          return (result_type)'1';
      }
      if (lowerLetter == 'z')
      {
          return (result_type)'2';
      }
      if (lowerLetter == 'd')
      {
          return (result_type)'3';
      }
      if (lowerLetter == 'l')
      {
          return (result_type)'4';
      }
    return (result_type)'*';
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
