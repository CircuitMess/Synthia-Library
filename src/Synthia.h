#ifndef SYNTHIA_LIBRARY_SYNTHIA_H
#define SYNTHIA_LIBRARY_SYNTHIA_H

#include <Arduino.h>
#include <CircuitOS.h>
#include <Loop/LoopListener.h>
#include <Input/InputShift.h>
#include <driver/i2s.h>
#include <Devices/AW9523.h>
#include "Input/SliderInput.h"
#include "Input/EncoderInput.h"
#include "Pins.hpp"
#include "Output/RGBMatrixOutput.h"
#include <Devices/Matrix/Matrix.h>
#include <Devices/Matrix/IS31FL3731.h>

extern const i2s_pin_config_t i2s_pin_config;

class SynthiaImpl {
public:
	SynthiaImpl();

	void begin();

	InputShift* getInput() const;
	AW9523* getSlotExp() const;
	AW9523* getTrackExp() const;

	static RGBMatrixOutput trackOutput;
	static RGBMatrixOutput slotOutput;

private:
	InputShift* input;
	IS31FL3731* charlie;
	AW9523* slotExp;
	AW9523* trackExp;

};

extern SynthiaImpl Synthia;
extern SliderInput Sliders;
extern EncoderInput Encoders;

extern Matrix TrackMatrix; //main 16x5 partition
extern Matrix CursorMatrix; //16x1 strip below trackMatrix
extern Matrix SlidersMatrix; //2x8 strip next to sliders
extern Matrix TrackRGB; //2x5 RGB LEDs left and right from trackMatrix
extern Matrix SlotRGB; //5 RGB LEDs below the slot buttons
extern Matrix SoloRGB; //1 solo RGB LED in the top right corner

#endif
