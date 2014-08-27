#include <gmock/gmock.h>
#include "soundex.h"

using namespace testing;

class SoundexEncoding : public testing::Test 
{
public:
    Soundex soundex;
};

TEST_F(SoundexEncoding, GivenAStringSoundexEncodeReturnsItInUpperCase)
{
    ASSERT_THAT(soundex.encode("abcde").substr(0,1), Eq("A"));
}
