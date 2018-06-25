/** 
 * File:   factory.h
 *
 * Service class setting up all objects of the system.
 * 
 * \author  Prof. Dr. Thomas Lehmann
 * \version 1
 * \date    2013-11-10
 */

#ifndef FACTORY_H
#define	FACTORY_H

#include "fsm.h"
#include "DummyProcess.h"

class FSMFactory{
public:
	FSM* createFSM();
	FSM* DummyFSM(DummyProcess* processImage);
};

#endif	/* FACTORY_H */

