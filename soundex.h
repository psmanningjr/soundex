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
    string convertNonFirstLettersToNumbers(const string& word);
    string removeDuplicates(const string& word);
//    int consanantsToNumber(int letter);
};

#endif // SOUNDEX_H
