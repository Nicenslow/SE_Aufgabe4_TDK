/** 
 * File:   plugin.h
 * Author: Lehmann
 *
 * Inface definition for smart sensors.
 * 
 * Created on 10. November 2013, 15:49
 */
#include "FestoProcessAccess.h";
using namespace std;
#ifndef PLUGIN_H
#define	PLUGIN_H


class Plugin {
private:
	FestoProcessAccess *process;
public:
    virtual void evalCycle() = 0;
    virtual bool result() = 0;
};

#endif	/* PLUGIN_H */

