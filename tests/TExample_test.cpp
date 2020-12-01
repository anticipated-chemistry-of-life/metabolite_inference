#include "TestCase.h"
#include "TParameters.h"
#include "TExample.h"

TEST(EXAMPLETESTSUIT, EXAMPLETEST){
    TParameters params;
    int argument = 10;
    params.addParameter("argument", toString(argument));
    TLog logfile;
    TExample test(params, &logfile);

    EXPECT_EQ(test.getArgument(), argument);
}