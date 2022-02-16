#include "Synthia.h"
#include "Pins.hpp"
#include <Loop/LoopManager.h>

LEDmatrixImpl LEDmatrix;

SynthiaImpl Synthia;

SynthiaImpl::SynthiaImpl(){}

void SynthiaImpl::begin(){
	Serial.println(115200);

	if(!LEDmatrix.begin(I2C_SDA, I2C_SCL)){
		Serial.println("couldn't start matrix");
		for(;;);
	}

	input = new InputGPIO();
	InputGPIO::getInstance()->preregisterButtons({BTN_1, BTN_2, BTN_3, BTN_4, BTN_5});
	LoopManager::addListener(input);

}

Input* SynthiaImpl::getInput() const{
	return input;
}

