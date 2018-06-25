//
// Created by Jan-Niklas Jacobson on 21.06.18.
//

#include <cstdio>
#include "DummyProcess.h"

DummyProcess::DummyProcess() {
	process_image = 0;
	process_image_old = 0;
	process_image_change = 0;
	output_image = 0;
	updateProcessImage();
}

DummyProcess::~DummyProcess() {
	resetOutputs();
}

void DummyProcess::updateProcessImage(void) {
	// do nothing
}

void DummyProcess::applyOutputToProcess(void) {
	//printf("new output: %0x\n", output_image);
}

unsigned char DummyProcess::isBitSet(unsigned short bitMask) {
	return ((process_image & bitMask) != 0);
}

unsigned char DummyProcess::isBitPosEdge(unsigned short bitMask) {
	return ((process_image & bitMask) == bitMask) && ((process_image_change & bitMask) == bitMask);
}

unsigned char DummyProcess::isBitNegEdge(unsigned short bitMask) {
	return ((process_image & bitMask) == 0) && ((process_image_change & bitMask) == bitMask);
}


void DummyProcess::setBitInOutput(unsigned short bitMask) {
	output_image |= bitMask;
}

void DummyProcess::clearBitInOutput(unsigned short bitMask) {
	output_image &= ~bitMask;
}


void DummyProcess::setBitInProcess(unsigned short bitMask) {
	process_image |= bitMask;
}

void DummyProcess::clearBitInProcess(unsigned short bitMask) {
	process_image &= ~bitMask;
}

unsigned short DummyProcess::hight() {
	return height_analogue_value;
}

void DummyProcess::resetOutputs(void) {
	output_image = 0;
	applyOutputToProcess();
}

void DummyProcess::setHight(unsigned short hight) {
	height_analogue_value = hight;
}

void DummyProcess::toggleButtonStartBit(bool value) {
	if (value) {
		setBitInProcess(BUTTON_START_PRESSED);
	}
	else {
		clearBitInProcess(BUTTON_START_PRESSED);
	}
}

void DummyProcess::toggleItemAtBeginningBit(bool value) {
	if (value) {
		setBitInProcess(ITEM_DETECTED);
	}
	else {
		clearBitInProcess(ITEM_DETECTED);
	}
}

void DummyProcess::toggleItemAtMetalDetectorBit(bool value) {
	if (value) {
		setBitInProcess(ITEM_AT_JUNCTION);
	}
	else {
		clearBitInProcess(ITEM_AT_JUNCTION);
	}
}

void DummyProcess::toggleMetalDetectedBit(bool value) {
	if (value) {
		setBitInProcess(ITEM_IS_METTAL);
	}
	else {
		clearBitInProcess(ITEM_IS_METTAL);
	}
}

void DummyProcess::toggleSlideSensorBit(bool value) {
	if (value) {
		setBitInProcess(BUFFER_IS_FULL);
	}
	else {
		clearBitInProcess(BUFFER_IS_FULL);
	}
}

void DummyProcess::toggleEndSensorBit(bool value) {
	if (value) {
		setBitInProcess(ITEM_AT_END);
	}
	else {
		clearBitInProcess(ITEM_AT_END);
	}
}

void DummyProcess::saveOldImg() {
	process_image_old = process_image;
}

void DummyProcess::updateChangeImg() {
	process_image_change = process_image_old ^ process_image;
}

void DummyProcess::toggleHightSensorBit(bool value) {
	if (value) {
		setBitInProcess(ITEM_AT_HIGHT_SENSOR);
	}
	else {
		clearBitInProcess(ITEM_AT_HIGHT_SENSOR);
	}
}

void DummyProcess::toggleButtonStopBit(bool value) {
	if (value) {
		setBitInProcess(BUTTON_STOP_PRESSED);
	}
	else {
		clearBitInProcess(BUTTON_STOP_PRESSED);
	}
}

void DummyProcess::toggleButtonEmergencyBit(bool value) {
	if (value) {
		setBitInProcess(EMERGENCY_STOP_PRESSED);
	}
	else {
		clearBitInProcess(EMERGENCY_STOP_PRESSED);
	}
}






