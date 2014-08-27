#include "soundex.h"
#include <cstring>

using namespace std;

Soundex::Soundex()
{
}

string Soundex::encode(const string& word)
{
    return firstLetterToUpper(word);
}

string Soundex::firstLetterToUpper(const string& word)
{
    string newStr = word;
    newStr[0]=toupper(word[0]);
    return newStr;
}

