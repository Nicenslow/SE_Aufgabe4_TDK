/** 
 * File:   plugin.h
 * Author: Lehmann
 *
 * Inface definition for smart sensors.
 * 
 * Created on 10. November 2013, 15:49
 */
#include "plugin.h";
using namespace std;
#ifndef HOEHENPLUGIN_H
#define	HOEHENPLUGIN_H

enum HoehenPlugin_States { Beginn,ErsteFlanke,ZweiteFlanke,DritteFlanke,VierteFlanke,FünfteFlanke,DriveBack,Result,Final };

class HoehenPlugin : public Plugin {
private:
	HoehenPlugin_States currentState;
	unsigned short correctHight[6];
	FestoProcessAccess *process;
	bool hightResult;
public:
	HoehenPlugin(FestoProcessAccess *process);
	~HoehenPlugin();
	HoehenPlugin_States getCurrentState();
	virtual void evalCycle();
	virtual bool result();
	virtual bool evalCurrentHight(unsigned short bausteinhoehe, unsigned short vorgegebeneHoeheMax);
	virtual void driveback();
	virtual void waitForEdge(int EdgeCounter);
};

#endif	/* HOEHENPLUGIN_H */

