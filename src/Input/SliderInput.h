#ifndef SYNTHIA_LIBRARY_SLIDERINPUT_H
#define SYNTHIA_LIBRARY_SLIDERINPUT_H

#include <Loop/LoopListener.h>
#include "../Pins.hpp"
#include <vector>
#include "../WithListeners.h"

class SliderInput;

class SynthiaSliderListener {
	friend SliderInput;

private:

	virtual void leftPotMove(uint8_t amount);
	virtual void rightPotMove(uint8_t amount);
};

class SliderInput : public LoopListener, public WithListeners<SynthiaSliderListener> {

public:
	SliderInput();

	void begin();

	void loop(uint _time) override;

	uint8_t getLeftPotValue() const;

	uint8_t getRightPotValue() const;

private:
	uint16_t leftPotValue;
	uint16_t rightPotValue;

	uint8_t leftPotPreviousValue;
	uint8_t rightPotPreviousValue;

	uint16_t leftlowPassFilter(uint16_t sensorValue);
	uint16_t rightlowPassFilter(uint16_t sensorValue);

	float EMA_a = 0.02;      //initialization of EMA alpha
	int rightEMA_S = 0;          //initialization of EMA S
	int leftEMA_S = 0;          //initialization of EMA S

};

#endif //SYNTHIA_LIBRARY_SLIDERINPUT_H