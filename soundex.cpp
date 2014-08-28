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

          {'r','6'},
          {'h','H'},
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
    numEncodedStr = removeDuplicatesAroundH(numEncodedStr);
    numEncodedStr = removeVowelsAndY(numEncodedStr);
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

string Soundex::removeDuplicatesAroundH(const string& word)
{
    newStr = word;
    while (anotherHFound())
    {
        if (dupAroundH())
        {
            removeHAndLetterAfter();
        }
        else
        {
            removeH();
        }
    }
    return newStr;
}

bool Soundex::dupAroundH()
{
    return (letterBeforeH() && letterAfterH() && sameCodeBeforeAndAfterH());
}

bool Soundex::letterBeforeH()
{
    return(indexOfH >0);
}

bool Soundex::letterAfterH()
{
    return(indexOfH < newStr.length());
}

bool Soundex::sameCodeBeforeAndAfterH()
{
    return(newStr[indexOfH-1] == newStr[indexOfH+1]);
}

bool Soundex::anotherHFound()
{
    indexOfH = newStr.find("H");
    return (indexOfH != string::npos);
}

void Soundex::removeH()
{
    newStr.erase(indexOfH,1);
}

void Soundex::removeHAndLetterAfter()
{
    newStr.erase(indexOfH,2);
}

string Soundex::removeVowelsAndY(const string& word)
{
    NoVowelsOrYString noVowelStr = for_each(word.begin(), word.end(), NoVowelsOrYString());
    return noVowelStr.noVowelsOrYString;
    return word;
}
