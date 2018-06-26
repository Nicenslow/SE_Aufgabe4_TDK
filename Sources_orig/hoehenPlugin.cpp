/** 
 * File:   hoehenPlugin.cpp
 *
 * 
 * 
 * 
 * \author  Prof. Dr. Dr. med. Torben Kunow
 * \version 1
 * \date    2013-11-01
 */
using namespace std;

#include "hoehenPlugin.h";
#include "FestoProcessAccess.h"

unsigned short correctHight[6] = { 3373, 3402, 3690, 3402, 3076, 3773 };
unsigned short currentHight = 0;
HoehenPlugin_States currentState;

HoehenPlugin::HoehenPlugin(FestoProcessAccess *process) {
	currentState = Beginn;
	this->process = process;	
}

HoehenPlugin::~HoehenPlugin() {
    
}


void HoehenPlugin::evalCycle() {
	while (currentState != Final) {
		switch (currentState) {
		case Beginn:
			waitForEdge(0);
			currentState = ErsteFlanke;
			break;
		case ErsteFlanke:
			if (evalCurrentHight(currentHight, correctHight[1]))
			{
				currentState = DriveBack;
			}
			else
			{
				waitForEdge(1);
				currentState = ZweiteFlanke;
			}
			break;
		case ZweiteFlanke:
			if (evalCurrentHight(currentHight, correctHight[2]))
			{
				currentState = DriveBack;
			}
			else
			{
				waitForEdge(2);
				currentState = DritteFlanke;
			}
			break;
		case DritteFlanke:
			if (evalCurrentHight(currentHight, correctHight[3]))
			{
				currentState = DriveBack;
			}
			else
			{
				waitForEdge(3);
				currentState = VierteFlanke;
			}
			break;
		case VierteFlanke:
			if (evalCurrentHight(currentHight, correctHight[4]))
			{
				currentState = DriveBack;
			}
			else
			{
				waitForEdge(4);
				currentState = FünfteFlanke;
			}
			break;
		case FünfteFlanke:
			if (evalCurrentHight(currentHight, correctHight[5]))
			{
				currentState = DriveBack;
			}
			else
			{
				currentState = Result;
			}
			break;
		case Result:
			hightResult = true;
			currentState = Final;
			break;
		case DriveBack:
			hightResult = false;
			driveback();
			//currentState = Final;
			break;
		case Final:
			break;
		default:
			currentState = Beginn;
		}
	}
	//currentState = Beginn;
}

bool HoehenPlugin::result() {
	return hightResult;
}

void HoehenPlugin::driveback() {
	process->driveLeft();
	//while (!process->isItemAtBeginning());
}

void HoehenPlugin::waitForEdge(int EdgeCounter) {
	currentHight = process->getHight();
	while (evalCurrentHight(currentHight, correctHight[EdgeCounter])) { // vllt als funktion auslagern
		currentHight = process->getHight();
	}
}

bool HoehenPlugin::evalCurrentHight(unsigned short bausteinhoehe, unsigned short vorgegebeneHoeheMax) {
	return ((bausteinhoehe > (vorgegebeneHoeheMax - 60)) && (bausteinhoehe < (vorgegebeneHoeheMax + 60))); // 60 als konstante angeben
}

HoehenPlugin_States HoehenPlugin::getCurrentState() {
	return currentState;
}
	












