#include "Synthia.h"
#include "Pins.hpp"
#include <Devices/LEDmatrix/LEDmatrix.h>

SynthiaImpl Synthia;
LEDmatrixImpl LEDmatrix;

void SynthiaImpl::begin(){
	Serial.println(115200);

	if(!LEDmatrix.begin(I2C_SDA, I2C_SCL)){
		Serial.println("couldn't start matrix");
		for(;;);
	}


}
