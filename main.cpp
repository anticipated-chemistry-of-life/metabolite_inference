/*
 * estimHet.cpp
 *
 *  Created on: Feb 19, 2015
 *      Author: wegmannd
 */

#include "TMain.h"

//---------------------------------------------------------------------------
// Includes for tasks
//---------------------------------------------------------------------------

#include "TExample.h"


//---------------------------------------------------------------------------
// Existing Tasks
//---------------------------------------------------------------------------

void addTaks(TMain & main) {
	// Tasks consist of a name and a pointer to a TTask object.
    // Use main.addRegularTask() to add a regular task (shown in list of available tasks)
	// Use main.addDebugTask()   to add a debug task (not shown in list of available tasks)

	main.addRegularTask("example", new TTask_example());
};

//---------------------------------------------------------------------------
// Existing Integration tests
//---------------------------------------------------------------------------

void addTests(TMain & main){
    // Use main.addTest to add integration tests

	// Use main.addTestsuite to add test suits
};


//---------------------------------------------------------------------------
//Main function
//---------------------------------------------------------------------------

int main(int argc, char* argv[]){
	//Create main by providing a program name, a version, link to repo and contact email
	TMain main("NAME", "0.1", "https://bitbucket.org/wegmannlab/name", "daniel.wegmann@unifr.ch");

	//add existing tasks
	addTaks(main);

	//now run program
	return main.run(argc, argv);
};
