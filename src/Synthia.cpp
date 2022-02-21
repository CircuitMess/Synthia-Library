#include "Synthia.h"
#include "Pins.hpp"
#include <Loop/LoopManager.h>
#include <SPIFFS.h>
#include <WiFi.h>

const i2s_pin_config_t i2s_pin_config = {
		.bck_io_num = I2S_BCK,
		.ws_io_num = I2S_WS,
		.data_out_num = I2S_DO,
		.data_in_num = I2S_DI
};

LEDmatrixImpl LEDmatrix;

SynthiaImpl Synthia;

SynthiaImpl::SynthiaImpl(){}

void SynthiaImpl::begin(){
	Serial.println(115200);

	if(psramFound()){
		Serial.printf("PSRAM init: %s, free: %d B\n", psramInit() ? "Yes" : "No", ESP.getFreePsram());
	}else{
		Serial.println("No PSRAM detected");
	}


	disableCore0WDT();
	disableCore1WDT();

	WiFi.mode(WIFI_OFF);
	btStop();


	if(!LEDmatrix.begin(I2C_SDA, I2C_SCL)){
		Serial.println("couldn't start matrix");
		for(;;);
	}

	if(!SPIFFS.begin()){
		Serial.println("couldn't start SPIFFS");
		for(;;);
	}

	input = new InputGPIO();
//	InputGPIO::getInstance()->preregisterButtons({BTN_1, BTN_2, BTN_3, BTN_4, BTN_5});
	LoopManager::addListener(input);

}

Input* SynthiaImpl::getInput() const{
	return input;
}

