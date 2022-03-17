#include "Synthia.h"
#include "Pins.hpp"
#include <Loop/LoopManager.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include "NullOutput.hpp"

const i2s_pin_config_t i2s_pin_config = {
		.bck_io_num = I2S_BCK,
		.ws_io_num = I2S_WS,
		.data_out_num = I2S_DO,
		.data_in_num = I2S_DI
};

SynthiaImpl Synthia;
SliderInput Sliders;
EncoderInput Encoders;

NullOutput matrixOut(16, 9);
Matrix trackMatrix(matrixOut);
Matrix cursorMatrix(matrixOut);
Matrix sliderMatrix(matrixOut);
Matrix trackRGB(matrixOut);
Matrix slotRGB(matrixOut);
Matrix soloRGB(matrixOut);


SynthiaImpl::SynthiaImpl(){

}

void SynthiaImpl::begin(){
	Serial.begin(115200);

	if(psramFound()){
		Serial.printf("PSRAM init: %s, free: %d B\n", psramInit() ? "Yes" : "No", ESP.getFreePsram());
	}else{
		Serial.println("No PSRAM detected");
	}

	disableCore0WDT();
	disableCore1WDT();

	WiFi.mode(WIFI_OFF);
	btStop();

	Sliders.begin();
	Encoders.begin();

	input = new InputGPIO();
	input->preregisterButtons({BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_ENC_L, BTN_ENC_R});
	LoopManager::addListener(input);

	if(!SPIFFS.begin()){
		Serial.println("couldn't start SPIFFS");
		for(;;);
	}

	trackMatrix.begin();
	cursorMatrix.begin();
	sliderMatrix.begin();
	trackRGB.begin();
	slotRGB.begin();
	soloRGB.begin();
}

Input* SynthiaImpl::getInput() const{
	return input;
}

