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

	int16_t leftPotPreviousValue = -1;
	int16_t rightPotPreviousValue = -1;

	uint16_t leftFilter(uint16_t sensorValue);
	uint16_t rightFilter(uint16_t sensorValue);

	const uint8_t MinPotMove = 2; // Minimum value change before listeners are triggered
	const float EMA_a = 0.01; // Filter alpha
	float rightEMA_S = 0;
	float leftEMA_S = 0;

};

#endif //SYNTHIA_LIBRARY_SLIDERINPUT_H