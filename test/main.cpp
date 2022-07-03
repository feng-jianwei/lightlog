#include "gmock/gmock-actions.h"
#include "gmock/gmock-function-mocker.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include <gmock/gmock-spec-builders.h>
#include "logger/logger.h"

using namespace std;
void writelog(const std::string &log)
{
	cout << log << endl;
}

class LightLogEnv : public testing::Environment {
	void SetUp() override
	{
		
	}
};

int main()
{
	testing::InitGoogleTest();
	testing::AddGlobalTestEnvironment(new LightLogEnv);
	int ret = RUN_ALL_TESTS();
	return ret;
}
