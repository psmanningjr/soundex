#include <gmock/gmock.h>
#include "soundex.h"

using namespace testing;

class SoundexEncoding : public testing::Test 
{
public:
    Soundex soundex;
};

TEST_F(SoundexEncoding, GivenAWordSoundexEncodeReturnsFirstCharInUpperCase)
{
    ASSERT_THAT(soundex.encode("abcde").substr(0,1), Eq("A"));
}

TEST_F(SoundexEncoding, GivenAWordSoundexEncodeConvertsConsanantsbdlAftertheFirstCharToNumbers)
{
    ASSERT_THAT(soundex.encode("zbdl"), Eq("Z134"));
}

TEST_F(SoundexEncoding, GivenAWordSoundexEncodeConvertsFullSetOfConsanantsAfterTheFirstCharToNumbers)
{
    ASSERT_THAT(soundex.encode("mrmj"), Eq("M652"));
}

TEST_F(SoundexEncoding, GivenAWordWhereAdjacentLettersEncodeTheSameThenKeepTheFirst)
{
    ASSERT_THAT(soundex.encode("xDtNmpv"), Eq("X351"));
}

TEST_F(SoundexEncoding, GivenAWordWhereFirstLetterWouldCodeToSameAsSecondLeterThenSecondLetterDropped)
{
    ASSERT_THAT(soundex.encode("xJrmD"), Eq("X653"));
}

TEST_F(SoundexEncoding, GivenAnEmptyStringEncodeShouldReturnEmptyString)
{
    ASSERT_THAT(soundex.encode(""), Eq(""));
}

TEST_F(SoundexEncoding, GivenWordWithSameCodewithHBetweenThenEncodeRetainsFirstAndRemovesH)
{
    ASSERT_THAT(soundex.encode("GhcrLf"), Eq("G641"));
}

TEST_F(SoundexEncoding, GivenWordWithSameCodewithHBetweenMultipleTimesThenEncodeRetainsFirstAndRemovesH)
{
    ASSERT_THAT(soundex.encode("GhcrLfhp"), Eq("G641"));
}

TEST_F(SoundexEncoding, GivenWordWithSameCodewithWBetweenThenEncodeRetainsFirstAndRemovesW)
{
    ASSERT_THAT(soundex.encode("cwxrLf"), Eq("C641"));
}

TEST_F(SoundexEncoding, GivenWordEncodedToMoreThanFourCharsThenItIsClippedAtFourChars)
{
    ASSERT_THAT(soundex.encode("Yabgdyr"), Eq("Y123"));
}

TEST_F(SoundexEncoding, GivenWordWithVowelsThenVowelsAreRemoved)
{
    ASSERT_THAT(soundex.encode("rjakB"), Eq("R221"));
}
