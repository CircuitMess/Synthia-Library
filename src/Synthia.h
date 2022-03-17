#ifndef SYNTHIA_LIBRARY_SYNTHIA_H
#define SYNTHIA_LIBRARY_SYNTHIA_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Loop/LoopListener.h>
#include <Input/InputGPIO.h>
#include <driver/i2s.h>
#include "Input/SliderInput.h"
#include "Input/EncoderInput.h"
#include "Pins.hpp"
#include <Devices/Matrix/Matrix.h>

extern const i2s_pin_config_t i2s_pin_config;

class SynthiaImpl {
public:
	SynthiaImpl();

	void begin();

	Input* getInput() const;

private:
	Input* input;

};

extern SynthiaImpl Synthia;
extern SliderInput Sliders;
extern EncoderInput Encoders;

extern Matrix trackMatrix; //main 16x5 partition
extern Matrix cursorMatrix; //16x1 strip below trackMatrix
extern Matrix sliderMatrix; //2x8 strip next to sliders
extern Matrix trackRGB; //2x5 RGB LEDs left and right from trackMatrix
extern Matrix slotRGB; //5 RGB LEDs below the slot buttons
extern Matrix soloRGB; //1 solo RGB LED in the top right corner

#endif
