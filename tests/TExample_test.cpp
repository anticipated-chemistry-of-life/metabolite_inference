#include "TestCase.h"
#include "TParameters.h"
#include "TExample.h"

TEST(EXAMPLETESTSUITE, EXAMPLETEST){
    coretools::TParameters params;
    int argument = 10;
    params.addParameter("argument", coretools::str::toString(argument));
    coretools::TLog logfile;
    TExample test(params, &logfile);

    EXPECT_EQ(test.getArgument(), argument);
}