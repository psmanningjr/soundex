#include "soundex.h"
#include <cstring>
#include <algorithm>
#include <ctype.h>
#include <unordered_map>

using namespace std;

const char notADigit{'*'};
static const size_t MaxCode_Length{4};


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

          {'r','6'},
          {'h','H'},
          {'w','W'},
          {'g','G'},
          {'a','A'},
          {'e','E'},
          {'i','I'},
          {'o','O'},
          {'u','U'},
          {'y','Y'}
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
            differentAdjacentLetter(letter))
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

    bool differentAdjacentLetter(char letter)
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

struct NoVowelsOrYString
{
public:
    NoVowelsOrYString()
    {
        noVowelsOrYString = "";
    }

    void operator() (char letter)
    {
        if (EmptyString() ||
            letterToKeep(letter))
        {
            addLetter(letter);
        }
    }

    string noVowelsOrYString;

private:

    const string charsToRemove = "aeiouy";

    bool EmptyString()
    {
        return (noVowelsOrYString.length() == 0);
    }

    bool letterToKeep(char letter)
    {
        return (charsToRemove.find(tolower(letter)) == string::npos);
    }

    void addLetter(char letter)
    {
        noVowelsOrYString.push_back(letter);
    }

};

struct NoInvalidCharsString
{
public:
    NoInvalidCharsString()
    {
        noInvalidCharsString = "";
    }

    void operator() (char letter)
    {
        if (EmptyString() ||
            letterToKeep(letter))
        {
            addLetter(letter);
        }
    }

    string noInvalidCharsString;

private:

    bool EmptyString()
    {
        return (noInvalidCharsString.length() == 0);
    }

    bool letterToKeep(char letter)
    {
        return (letter != notADigit);
    }

    void addLetter(char letter)
    {
        noInvalidCharsString.push_back(letter);
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
    numEncodedStr = removeDuplicatesAroundTargetChar('h',numEncodedStr);
    numEncodedStr = removeDuplicatesAroundTargetChar('w',numEncodedStr);
    numEncodedStr = removeVowelsAndY(numEncodedStr);
    numEncodedStr = removeInvalidChars(numEncodedStr);
    numEncodedStr = makeCorrectLengthByClippingOrZeroPadding(numEncodedStr);
    numEncodedStr.resize(MaxCode_Length,'0');
    return word.substr(0,1).append(numEncodedStr.substr(1,3));
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

string Soundex::removeDuplicatesAroundTargetChar(char targetSpecialChar, const string& word)
{
    targetChar = toupper(targetSpecialChar);
    newStr = word;
    while (anotherTargetCharFound())
    {
        if (dupAroundTargetChar())
        {
            removeTargetCharAndLetterAfter();
        }
        else
        {
            removeTargetChar();
        }
    }
    return newStr;
}

bool Soundex::dupAroundTargetChar()
{
    return (letterBeforeTargetChar() && letterAfterTargetChar() && sameCodeBeforeAndAfterTargetChar());
}

bool Soundex::letterBeforeTargetChar()
{
    return(indexOfSpecialChar >0);
}

bool Soundex::letterAfterTargetChar()
{
    return(indexOfSpecialChar < newStr.length());
}

bool Soundex::sameCodeBeforeAndAfterTargetChar()
{
    return(newStr[indexOfSpecialChar-1] == newStr[indexOfSpecialChar+1]);
}

bool Soundex::anotherTargetCharFound()
{
    indexOfSpecialChar = newStr.find(targetChar);
    return (indexOfSpecialChar != string::npos);
}

void Soundex::removeTargetChar()
{
    newStr.erase(indexOfSpecialChar,1);
}

void Soundex::removeTargetCharAndLetterAfter()
{
    newStr.erase(indexOfSpecialChar,2);
}

string Soundex::removeVowelsAndY(const string& word)
{
    NoVowelsOrYString noVowelStr = for_each(word.begin(), word.end(), NoVowelsOrYString());
    return noVowelStr.noVowelsOrYString;
    return word;
}

string Soundex::removeInvalidChars(const string& word)
{
    NoInvalidCharsString noInvalidStr = for_each(word.begin(), word.end(), NoInvalidCharsString());
    return noInvalidStr.noInvalidCharsString;
    return word;
}
string Soundex::makeCorrectLengthByClippingOrZeroPadding(const string& word)
{
    string numEncodedStr = word;
    numEncodedStr.resize(MaxCode_Length,'0');
    return numEncodedStr;
}
