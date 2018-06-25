
//
// Created by Jan-Niklas Jacobson on 21.06.18.
//

#ifndef DUMMYTEST_H
#define DUMMYTEST_H


#include "minilab1008processimage.h"
#include "iomasks.h"
#include "hoehenPlugin.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <tuple>

using namespace std;

typedef std::tuple<unsigned int, unsigned int, unsigned short> LogTuple;

class DummyTest {
public:
	DummyTest(/*FestoProcessImage* processImage, Plugin* plugin =0*/);
	Plugin *plugin;
	~DummyTest();
	void testPlugin();
private:
	void eval();
	void evalStates();
	void testLog(char* logFile);

private:
	FestoProcessImage* process;
};


#endif //SEP34_SIMPROCESS_H
