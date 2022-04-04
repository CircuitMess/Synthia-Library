#include "SliderInput.h"
#include "../Pins.hpp"
#include <Loop/LoopManager.h>

SliderInput::SliderInput(){

}

void SliderInput::begin(){
	pinMode(POT_L, INPUT);
	pinMode(POT_R, INPUT);

	uint16_t potValue;

	potValue = analogRead(POT_L);
	leftEMA_S = potValue;
	leftPotPreviousValue = leftPotValue = 255 - constrain(map(potValue, 0, MaxPotReading, 0, 255), 0, 255);

	potValue = analogRead(POT_R);
	rightEMA_S = potValue;
	rightPotPreviousValue = rightPotValue = 255 - constrain(map(potValue, 0, MaxPotReading, 0, 255), 0, 255);

	if(rightPotValue % 2 != 0){
		rightPotPreviousValue = --rightPotValue;
	}

	if(leftPotValue % 2 != 0){
		leftPotPreviousValue = --leftPotValue;
	}

	LoopManager::addListener(this);
}

uint8_t SliderInput::getLeftPotValue() const{
	return leftPotValue;
}

uint8_t SliderInput::getRightPotValue() const{
	return rightPotValue;
}

void SliderInput::loop(uint time){
	uint16_t potValue;

	potValue = leftFilter(analogRead(POT_L));
	uint16_t cLeftPotValue = 255 - constrain(map(potValue, 0, MaxPotReading, 0, 255), 0, 255);

	potValue = rightFilter(analogRead(POT_R));
	uint16_t cRightPotValue = 255 - constrain(map(potValue, 0, MaxPotReading, 0, 255), 0, 255);

	if(leftPotPreviousValue == -1){
		leftPotPreviousValue = leftPotValue = cLeftPotValue;
	}
	if(abs((int) cLeftPotValue - (int) leftPotPreviousValue) >= MinPotMove){
		leftPotPreviousValue = leftPotValue = cLeftPotValue;

		iterateListeners([this](SliderListener* l){
			l->leftPotMove(leftPotValue);
		});
	}

	if(rightPotPreviousValue == -1){
		rightPotPreviousValue = rightPotValue = cRightPotValue;
	}
	if(abs((int) cRightPotValue - (int) rightPotPreviousValue) >= MinPotMove){
		rightPotPreviousValue = rightPotValue = cRightPotValue;

		iterateListeners([this](SliderListener* l){
			l->rightPotMove(rightPotValue);
		});
	}
}

uint16_t SliderInput::leftFilter(uint16_t sensorValue){
	leftEMA_S = (EMA_a * (float) sensorValue) + ((1.0f - EMA_a) * leftEMA_S);
	return leftEMA_S;
}

uint16_t SliderInput::rightFilter(uint16_t sensorValue){
	rightEMA_S = (EMA_a * (float) sensorValue) + ((1.0f - EMA_a) * rightEMA_S);
	return rightEMA_S;
}

void SliderListener::rightPotMove(uint8_t value){ }

void SliderListener::leftPotMove(uint8_t value){ }

