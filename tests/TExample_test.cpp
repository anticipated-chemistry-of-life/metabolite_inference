#include "TestCase.h"
#include "TParameters.h"
#include "TExample.h"

TEST(EXAMPLETESTSUITE, EXAMPLETEST){
    int argument = 10;
    coretools::instances::parameters().addParameter("argument", coretools::str::toString(argument));
    TExample test;

    EXPECT_EQ(test.getArgument(), argument);
}
