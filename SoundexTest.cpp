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
