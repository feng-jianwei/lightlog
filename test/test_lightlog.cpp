#include "lightlog.h"
#include "gtest/gtest.h"
#include <sys/syslimits.h>
using namespace std;
using namespace LightLog;

TEST(lightlog, SyncLog)
{
	OpenAyncLog();
	AyncLog("nishishei %d", 100);		
	SyncLog("1231 %d %s", 2131, "123");
}
