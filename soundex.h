#ifndef SOUNDEX_H
#define SOUNDEX_H
#include <string>

using namespace std;

class Soundex
{
public:
    Soundex();

    string encode(const string& word);
    string firstLetterToUpperCase(const string& word);

private:
    string encodeNonFirstLetters(const string& word);
    string convertLettersToNumbers(const string& word);
    string removeDuplicates(const string& word);
    bool emptyString(const string& word);
};

#endif // SOUNDEX_H
