/*
* File:   main.cpp
* Author: Lehmann
*
* Created on 8. November 2013, 16:24
*/

#define SUCCESSFUL 0
#define CONVEYOUR 3775

#include <cstdlib>
#include <cstdio>

#include "factory.h"
#include "fsm.h"
#include "hoehenPlugin.h"
#include "DummyProcess.h"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "OCDFAInspection"

using namespace std;

FILE *openLog(char *logpath) {
	return fopen(logpath, "r");
}

unsigned short getNextHight(FILE *log) {
	int temp1, temp2, err;
	int hight;
	err = fscanf(log, "%i; %i; %i\n", &temp1, &temp2, &hight);
	return (err < 3) ? (unsigned short)0 : (unsigned short)hight;
}

void initSensors(DummyProcess *processImage) {
	processImage->setHight(CONVEYOUR); // init conveyour height
									   // set active low bits
	processImage->toggleButtonStartBit(true); // init button
	processImage->toggleItemAtBeginningBit(true); // init sensor at beginning
	processImage->toggleHightSensorBit(true); // init hightsensor
	processImage->toggleItemAtMetalDetectorBit(true); // init item at metal detector
	processImage->toggleButtonStopBit(true);
	processImage->toggleButtonEmergencyBit(true);
	processImage->toggleEndSensorBit(true);
}

int testPluginError(FSM *fsm, DummyProcess *processImage, char * filePath) {
	initSensors(processImage);
	FILE *log = openLog(filePath);

	processImage->updateChangeImg();
	fsm->eval();

	processImage->saveOldImg();
	processImage->toggleButtonStartBit(false); // press button
	processImage->updateChangeImg();
	fsm->eval();

	processImage->saveOldImg();
	processImage->toggleButtonStartBit(true);
	processImage->toggleItemAtBeginningBit(false);
	processImage->updateChangeImg();
	fsm->eval();
	processImage->toggleItemAtBeginningBit(true);

	unsigned short hight = CONVEYOUR;
	do {
		processImage->saveOldImg();
		processImage->setHight(hight);
		hight = getNextHight(log);
		if (hight == 0) {
			break;
		}
		processImage->updateChangeImg();
		fsm->eval();
	} while (fsm->getHoehenPluginState() != DriveBack);

	processImage->toggleItemAtBeginningBit(false);
	processImage->saveOldImg();
	processImage->updateChangeImg();

	fsm->eval();

	if (fsm->getCurrentState() != Error) {
		return -1;
	}
	return 0;
}

int testPluginSuccess(FSM *fsm, DummyProcess *processImage, bool isMetal) {
	initSensors(processImage);
	FILE *log = openLog(const_cast<char *>("../Logs/processlog1.txt"));
	if (log == NULL) {
		return -1;
	}

	processImage->updateChangeImg();
	fsm->eval();
	if (fsm->getCurrentState() != Standby) {
		return -1;
	}

	processImage->saveOldImg();
	processImage->toggleButtonStartBit(false); // press button
	processImage->updateChangeImg();
	fsm->eval();
	if (fsm->getCurrentState() != Ready) {
		return -1;
	}

	processImage->toggleButtonStartBit(true);
	processImage->saveOldImg();
	processImage->toggleItemAtBeginningBit(false);
	processImage->updateChangeImg();
	fsm->eval();
	if (fsm->getHoehenPluginState() != Start) {
		return -1;
	}
	processImage->toggleItemAtBeginningBit(true);

	unsigned short hight = CONVEYOUR;
	do {
		processImage->saveOldImg();
		processImage->setHight(hight);
		hight = getNextHight(log);
		if (hight == 0) {
			break;
		}
		processImage->updateChangeImg();
		fsm->eval();
	} while (!fsm->getHoehenPluginState() == Final);

	if (fsm->getCurrentState() != Transport) {
		return -1;
	}

	processImage->saveOldImg();
	processImage->toggleItemAtMetalDetectorBit(false);
	processImage->updateChangeImg();
	fsm->eval();
	if (fsm->getCurrentState() != MetalDetection) {
		return -1;
	}

	processImage->saveOldImg();
	if (isMetal) {
		processImage->toggleMetalDetectedBit(true);
		processImage->updateChangeImg();
		fsm->eval();
		if (fsm->getCurrentState() != Metalic) {
			return -1;
		}

		processImage->toggleSlideSensorBit(false);
		processImage->saveOldImg();
		processImage->toggleSlideSensorBit(true);
		processImage->updateChangeImg();
		fsm->eval();
		if (fsm->getCurrentState() != SlideReached) {
			return -1;
		}

		processImage->toggleSlideSensorBit(false);
		processImage->toggleEndSensorBit(false);
		processImage->updateChangeImg();
		fsm->eval();
		if (fsm->getCurrentState() != Error) {
			return -1;
		}
	}
	else {
		processImage->toggleMetalDetectedBit(false);
		processImage->updateChangeImg();
		fsm->eval();
		if (fsm->getCurrentState() != NonMetalic) {
			return -1;
		}

		processImage->saveOldImg();
		processImage->toggleEndSensorBit(false);
		processImage->updateChangeImg();
		fsm->eval();
		if (fsm->getCurrentState() != EndReached) {
			return -1;
		}
	}

	return 0;
}

int testStartUp(FSM *fsm, DummyProcess *processImage) {

}

int main(int argc, char **argv) {
	bool run = true; // set this to false for debugging
	bool test = true; // set this to false to use festo hardware
	FSMFactory factory;

	FSM *fsm;
	if (test) {
		DummyProcess *processImage = new DummyProcess();
		fsm = factory.DummyFSM(processImage);

		// Start test1
		if (testPluginSuccess(fsm, processImage, true) != SUCCESSFUL) {
			printf("Error @ Test1!\n");
		}
		else {
			printf("Test1 successful\n");
		}

		processImage = new DummyProcess();
		fsm = factory.DummyFSM(processImage);

		// Start test2
		if (testPluginSuccess(fsm, processImage, false) != SUCCESSFUL) {
			printf("Error @ Test2!\n");
		}
		else {
			printf("Test2 successful\n");
		}

		processImage = new DummyProcess();
		fsm = factory.DummyFSM(processImage);

		// Start test3
		if (testPluginError(fsm, processImage,
			"../Logs/processlog2.txt") != SUCCESSFUL) {
			printf("Error @ Test3!\n");
		}
		else {
			printf("Test3 successful\n");
		}

		processImage = new DummyProcess();
		fsm = factory.DummyFSM(processImage);

		// Start test4
		if (testPluginError(fsm, processImage,
			"../Logs/processlog3.txt") != SUCCESSFUL) {
			printf("Error @ Test4!\n");
		}
		else {
			printf("Test4 successful\n");
		}
	}
	else {
		fsm = factory.createFSM();

		// Start Processing
		while (fsm != NULL && run) {
			fsm->eval();
		}
	}
	delete fsm;

	return 0;
}

#pragma clang diagnostic pop
