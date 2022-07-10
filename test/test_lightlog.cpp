#include "lightlog.h"
#include "gtest/gtest.h"
#include "ctime"
using namespace std;
using namespace LightLog;

TEST(lightlog, SyncLog)
{
	auto testCount = 0;
	auto testTime = 100000;
	OpenAyncLog();
	time_t begin = time(nullptr);
	cout << " begin " << ctime(&begin) << endl;;
	while (testCount++ < testTime) {
		AyncLog("nishishei %d", testCount);		
	}
	time_t end = time(nullptr);
	cout << " end "<< ctime(&end) << endl;;
}
