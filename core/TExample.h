/*
 * TExampleTask.h
 *
 *  Created on: Nov 30, 2020
 *      Author: phaentu
 */

#ifndef TEXAMPLETASK_H_
#define TEXAMPLETASK_H_

#include "coretools/Main/TParameters.h"
#include "coretools/Main/TTask.h"

//--------------------------------------
// TExample
//--------------------------------------
class TExample {
private:
	size_t _argument;

public:
	TExample();
	void doSomething() const;

	[[nodiscard]] size_t getArgument() const { return _argument; };
};

//--------------------------------------
// Tasks
//--------------------------------------
class TTask_example : public coretools::TTask {
public:
	// constructor must fill explanation shown to users
	TTask_example() { _explanation = "An example task"; };

	// a task must overload the run function that takes two arguments:
	// coretools::TParameters & Parameters, coretools::TLog* Logfile Usually, a
	// task creates an object and calls its function
	void run() override {
		TExample example;
		example.doSomething();
	};
};

// TODO: Add task to simulate
class TTask_infer : public coretools::TTask {
      public:
        // constructor must fill explanation shown to users
        TTask_infer() { _explanation = "Inferring metabolite presence in all the species there are on this planet!!"; };

        // a task must overload the run function that takes two arguments:
        // coretools::TParameters & Parameters, coretools::TLog* Logfile Usually, a
        // task creates an object and calls its function
        void run() override {
                std::cout << "Inferring!!!" << std::endl;
        };
};


#endif /* TEXAMPLETASK_H_ */
