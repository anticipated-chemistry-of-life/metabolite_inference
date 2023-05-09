/*
 * main.cpp
 */

#include "coretools/Main/TMain.h"

//---------------------------------------------------------------------------
// Includes for tasks
//---------------------------------------------------------------------------

#include "TExample.h"

//---------------------------------------------------------------------------
// Existing Tasks
//---------------------------------------------------------------------------

void addTaks(coretools::TMain &main) {
	// Tasks consist of a name and a pointer to a TTask object.
	// Use main.addRegularTask() to add a regular task (shown in
	// list of available tasks) Use main.addDebugTask() to add a
	// debug task (not shown in list of available tasks)

        // TODO: add all your tasks here (infer and simulate)
	main.addRegularTask("example", new TTask_example());
        main.addRegularTask("infer", new TTask_infer());
};

//---------------------------------------------------------------------------
// Existing Integration tests
//---------------------------------------------------------------------------

void addTests(coretools::TMain &){
	// Use main.addTest to add integration tests

	// Use main.addTestSuite to add test suites
};

//---------------------------------------------------------------------------
// Main function
//---------------------------------------------------------------------------

int main(int argc, char *argv[]) {
	// Create main by providing a program name, a version, an
	// affiliation, link to repo and contact email
	coretools::TMain main("metabolite_inference", "0.1", "University of Fribourg",
			      "https://bitbucket.org/wegmannlab/metabolite_inference",
			      "marco.visani@unifr.ch");

	// add existing tasks and tests
	addTaks(main);
	addTests(main);

	// now run program
	return main.run(argc, argv);
};
