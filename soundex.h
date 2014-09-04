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
    string removeDuplicatesAroundTargetChar(char specialTargetChar, const string& word);
    bool emptyString(const string& word);
    void removeTargetChar();
    void removeTargetCharAndLetterAfter();
    bool anotherTargetCharFound();
    bool letterBeforeTargetChar();
    bool letterAfterTargetChar();
    bool sameCodeBeforeAndAfterTargetChar();
    bool dupAroundTargetChar();
    string removeVowelsAndY(const string& word);
    string removeInvalidChars(const string& word);
    string makeCorrectLengthByClippingOrZeroPadding(const string& word);
    char targetChar;
    size_t indexOfSpecialChar;
    string newStr;
};

#endif // SOUNDEX_H
