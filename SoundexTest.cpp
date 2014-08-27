#include <gmock/gmock.h>


using namespace testing;

class SoundexEncoding : public testing::Test 
{
public:
	
};

TEST_F(SoundexEncoding, FailedTest)
{
    ASSERT_FALSE(true);
}
