#ifndef SYNTHIA_LIBRARY_SLIDERINPUT_H
#define SYNTHIA_LIBRARY_SLIDERINPUT_H

#include <Loop/LoopListener.h>
#include "../WithListeners.h"

class SliderInput;

class SliderListener {
friend SliderInput;

private:
	virtual void leftPotMove(uint8_t value);
	virtual void rightPotMove(uint8_t value);

};

class SliderInput : public LoopListener, public WithListeners<SliderListener> {
public:
	SliderInput();

	void begin();
	void loop(uint time) override;

	uint8_t getLeftPotValue() const;
	uint8_t getRightPotValue() const;

private:
	uint8_t leftPotValue;
	uint8_t rightPotValue;

	uint8_t leftPotPreviousValue;
	uint8_t rightPotPreviousValue;

	uint16_t leftFilter(uint16_t sensorValue);
	uint16_t rightFilter(uint16_t sensorValue);

	const uint16_t MaxPotReading = 650; // Maximum analogRead from pots
	const uint8_t MinPotMove = 2; // Minimum value change before listeners are triggered
	const float EMA_a = 0.01; // Filter alpha
	float rightEMA_S = 0;
	float leftEMA_S = 0;

};

#endif //SYNTHIA_LIBRARY_SLIDERINPUT_H