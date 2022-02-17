#ifndef SYNTHIA_LIBRARY_SYNTHIA_H
#define SYNTHIA_LIBRARY_SYNTHIA_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Loop/LoopListener.h>
#include <Devices/LEDmatrix/LEDmatrix.h>
#include <Input/InputGPIO.h>
#include <driver/i2s.h>

extern const i2s_pin_config_t i2s_pin_config;
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
