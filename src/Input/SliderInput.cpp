#include <Loop/LoopManager.h>
#include "SliderInput.h"
#include "../WithListeners.h"

SliderInput::SliderInput(){

}

void SliderInput::begin(){
	pinMode(POT_1,INPUT);
	pinMode(POT_2,INPUT);
	leftEMA_S = analogRead(POT_1);
	rightEMA_S = analogRead(POT_2);

	leftPotValue = leftlowPassFilter(analogRead(POT_1));
	leftPotValue = map(leftPotValue, 0, 620, 0, 255);
	rightPotValue = rightlowPassFilter(analogRead(POT_2));
	rightPotValue = map(rightPotValue, 0, 640, 0, 255);

	leftPotValue = 255 - constrain(leftPotValue,0,255);
	rightPotValue = 255 - constrain(rightPotValue,0,255);

	leftPotPreviousValue = leftPotValue;
	rightPotPreviousValue = rightPotValue;

	LoopManager::addListener(this);
}

uint8_t SliderInput::getLeftPotValue() const{
	return leftPotValue;
}

uint8_t SliderInput::getRightPotValue() const{
	return rightPotValue;
}

void SliderInput::loop(uint _time){
	leftPotValue = leftlowPassFilter(analogRead(POT_1));
	leftPotValue = map(leftPotValue, 0, 620, 0, 255);
	rightPotValue = rightlowPassFilter(analogRead(POT_2));
	rightPotValue = map(rightPotValue, 0, 640, 0, 255);

	leftPotValue = 255 - constrain(leftPotValue,0,255);
	rightPotValue = 255 - constrain(rightPotValue,0,255);
	if(leftPotValue != leftPotPreviousValue){
			leftPotPreviousValue = leftPotValue;
			for(auto listeners: getListeners()){
				listeners->leftPotMove(leftPotValue);
		}
	}

	if(rightPotValue != rightPotPreviousValue){
			rightPotPreviousValue = rightPotValue;
			for(auto listeners: getListeners()){
				listeners->rightPotMove(rightPotValue);
		}
	}
}

uint16_t SliderInput::leftlowPassFilter(uint16_t sensorValue){
	return leftEMA_S = (EMA_a * sensorValue) + ((1 - EMA_a) * leftEMA_S);
}
uint16_t SliderInput::rightlowPassFilter(uint16_t sensorValue){
	return rightEMA_S = (EMA_a * sensorValue) + ((1 - EMA_a) *  rightEMA_S);
}

void SynthiaSliderListener::rightPotMove(uint8_t amount){}

void SynthiaSliderListener::leftPotMove(uint8_t amount){}

