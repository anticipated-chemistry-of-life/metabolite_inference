#include "TMetaboliteCore.h"
#include "TParameters.h"
#include "TestCase.h"

TEST(EXAMPLETESTSUITE, EXAMPLETEST){
    int argument = 10;
    coretools::instances::parameters().addParameter("argument", coretools::str::toString(argument));
	TMetaboliteCore test;

    EXPECT_EQ(test.getArgument(), argument);
}
