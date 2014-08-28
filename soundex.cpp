#include "soundex.h"
#include <cstring>
#include <algorithm>
#include <ctype.h>
#include <unordered_map>

using namespace std;

const char notADigit{'*'};

class consanantsToNumber: unary_function<char, char> {
public:
  result_type operator () (argument_type letter)
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

struct NoDupString
{
public:
    NoDupString()
    {
        noDupString = "";
    }

    void operator() (char letter)
    {
        if (EmptyString() ||
            differentLetter(letter))
        {
            addLetter(letter);
        }
    }

    string noDupString;

private:

    bool EmptyString()
    {
        return (noDupString.length() == 0);
    }

    bool differentLetter(char letter)
    {
        return (letter != lastLetterAdded());
    }

    char lastLetterAdded()
    {
        return noDupString[noDupString.length()-1];
    }

    void addLetter(char letter)
    {
        noDupString.push_back(letter);
    }

};

Soundex::Soundex()
{
}

string Soundex::encode(const string& word)
{
    if (emptyString(word))
    {
        return "";
    }
   return firstLetterToUpperCase(encodeNonFirstLetters(word));
}

bool Soundex::emptyString(const string& word)
{
    return (word.length() == 0);
}

string Soundex::firstLetterToUpperCase(const string& word)
{
    string newStr = word;
    newStr[0]=toupper(word[0]);
    return newStr;
}

string Soundex::encodeNonFirstLetters(const string& word)
{
    string numEncodedStr = removeDuplicates(convertLettersToNumbers(word));
    return word.substr(0,1).append(numEncodedStr.substr(1,numEncodedStr.length()-1));
}

string Soundex::convertLettersToNumbers(const string& word)
{
   string numStr = word;
   transform(word.begin(),word.end(),numStr.begin(),::consanantsToNumber());
   return numStr;
}

string Soundex::removeDuplicates(const string& word)
{
    NoDupString newStr = for_each(word.begin(), word.end(), NoDupString());
    return newStr.noDupString;
}

