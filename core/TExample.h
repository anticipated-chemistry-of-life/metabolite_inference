/*
 * TExampleTask.h
 *
 *  Created on: Nov 30, 2020
 *      Author: phaentu
 */

#ifndef TEXAMPLETASK_H_
#define TEXAMPLETASK_H_

#include "TParameters.h"
#include "TTask.h"

//--------------------------------------
// TExample
//--------------------------------------
class TExample{
private:
	TLog* _logfile;
	int _argument;

public:
	TExample(TParameters & Parameters, TLog* Logfile);
	void doSomething(TRandomGenerator* Randomgenerator);

	int getArgument(){ return _argument; };
};



//--------------------------------------
// Tasks
//--------------------------------------
class TTask_example:public TTask{
public:
	//constructtor must fill explanation shown to users
	TTask_example(){ _explanation = "An example task"; };

	//a task must overlaod the run function that takes two arguments: TParameters & Parameters, TLog* Logfile
	//Usually, a task creates an object and calls its function
	void run(TParameters & Parameters, TLog* Logfile){
		TExample example(Parameters, Logfile);
		example.doSomething(_randomGenerator);
	};

};


#endif /* TEXAMPLETASK_H_ */
