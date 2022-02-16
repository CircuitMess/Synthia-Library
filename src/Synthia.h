#ifndef SYNTHIA_LIBRARY_SYNTHIA_H
#define SYNTHIA_LIBRARY_SYNTHIA_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Loop/LoopListener.h>
#include <Devices/LEDmatrix/LEDmatrix.h>
#include <Input/InputGPIO.h>

extern LEDmatrixImpl LEDmatrix;

class SynthiaImpl {
public:
	SynthiaImpl();

	void begin();

	Input* getInput() const;

private:
	Input* input;

};

extern SynthiaImpl Synthia;

#endif
