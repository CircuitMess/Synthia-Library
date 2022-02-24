#include <Loop/LoopManager.h>
#include "EncoderInput.h"

EncoderInput::EncoderInput(){

}

void EncoderInput::begin(){
	pinMode(ENC_1A,INPUT);
	pinMode(ENC_1B,INPUT);

	pinMode(ENC_2A,INPUT);
	pinMode(ENC_2B,INPUT);
	LoopManager::addListener(this);

}

void EncoderInput::loop(uint _time){
	currentStateLeft = digitalRead(ENC_1A);
	currentStateRight = digitalRead(ENC_2A);

	if(currentStateLeft != previousStateLeft){
		int encMovedValue;
		if(digitalRead(ENC_1B) != currentStateLeft){
			leftEncCounter++;
			encMovedValue = 1;
		}else{
			leftEncCounter--;
			encMovedValue = -1;
		}
		for(auto listeners: getListeners()){
			listeners->leftEncMove(encMovedValue);
		}
	}
	previousStateLeft = currentStateLeft;

	if(currentStateRight != previousStateRight){
		int encMovedValue;
		if(digitalRead(ENC_2B) != currentStateRight){
			rightEncCounter++;
			encMovedValue = 1;
		}else{
			rightEncCounter--;
			encMovedValue = -1;
		}
		for(auto listeners: getListeners()){
			listeners->rightEnctMove(encMovedValue);
		}
	}
	previousStateRight = currentStateRight;
}

int EncoderInput::getLeftEncValue() const{
	return leftEncCounter;
}

int EncoderInput::getRightEncValue() const{
	return rightEncCounter;
}

void SynthiaEncoderListener::leftEncMove(int8_t amount){ }

void SynthiaEncoderListener::rightEnctMove(int8_t amount){ }

