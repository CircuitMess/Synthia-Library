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
#include "Output/CursorMatrixOutput.h"
#include "Output/SlidersMatrixOutput.h"
#include "Output/TrackMatrixOutput.h"
#include <Devices/Matrix/DelayedMatrixOutput.h>

extern const i2s_pin_config_t i2s_pin_config;

class SynthiaImpl {
public:
	SynthiaImpl();

	void begin();

	InputShift* getInput() const;
	AW9523* getSlotExp() const;
	AW9523* getTrackExp() const;

private:
	//hardware outputting
	RGBMatrixOutput trackRGBOutput;
	RGBMatrixOutput slotRGBOutput;
	IS31FL3731 charlie;
	TrackMatrixOutput trackOutput;
	CursorMatrixOutput cursorOutput;
	SlidersMatrixOutput slidersOutput;

	DelayedMatrixOutput delayedOutput;
	MatrixOutputBuffer matrixBuffer;

	InputShift* input;
	AW9523* slotExp;
	AW9523* trackExp;

public:
	Matrix TrackMatrix; //main 16x5 partition
	Matrix CursorMatrix; //16x1 strip below trackMatrix
	Matrix SlidersMatrix; //2x8 strip next to sliders
	Matrix TrackRGB; //2x5 RGB LEDs left and right from trackMatrix
	Matrix SlotRGB; //5 RGB LEDs below the slot buttons

};

extern SynthiaImpl Synthia;
extern SliderInput Sliders;
extern EncoderInput Encoders;

#endif
