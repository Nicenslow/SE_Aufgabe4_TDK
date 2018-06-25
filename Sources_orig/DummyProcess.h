//
// Created by Jan-Niklas Jacobson on 21.06.18.
//

#ifndef DUMMYPROCESS_H
#define DUMMYPROCESS_H
#include "processimage.h"
#include "iomasks.h"
// if SIL is defined, no hardware interface is accessed or compiled in.
#define SIL

class DummyProcess : public FestoProcessImage {
private:
	unsigned short process_image;
	unsigned short process_image_old;
	unsigned short process_image_change;
	unsigned short output_image;
	unsigned short height_analogue_value;

	virtual void clearBitInProcess(unsigned short bitMask);
	virtual void setBitInProcess(unsigned short bitMask);
public:
	DummyProcess();
	virtual ~DummyProcess();
public:
	virtual void updateProcessImage(void);
	virtual void applyOutputToProcess(void);
	virtual unsigned char isBitSet(unsigned short bitMask);
	virtual unsigned char isBitPosEdge(unsigned short bitMask);
	virtual unsigned char isBitNegEdge(unsigned short bitMask);
	virtual void setBitInOutput(unsigned short bitMask);
	virtual void clearBitInOutput(unsigned short bitMask);
	virtual void resetOutputs(void);
	virtual unsigned short hight();

	virtual void setHight(unsigned short hight);
	virtual void toggleButtonStartBit(bool value);
	virtual void toggleItemAtBeginningBit(bool value);
	virtual void toggleItemAtMetalDetectorBit(bool value);
	virtual void toggleMetalDetectedBit(bool value);
	virtual void toggleSlideSensorBit(bool value);
	virtual void toggleEndSensorBit(bool value);
	virtual void toggleHightSensorBit(bool value);
	virtual void toggleButtonStopBit(bool value);
	virtual void toggleButtonEmergencyBit(bool value);

	virtual void saveOldImg();
	virtual void updateChangeImg();
};

#endif // DUMMYPROCESS_H