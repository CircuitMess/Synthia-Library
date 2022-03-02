#include "Synthia.h"
#include "Pins.hpp"
#include <Loop/LoopManager.h>

const i2s_pin_config_t i2s_pin_config = {
		.bck_io_num = I2S_BCK,
		.ws_io_num = I2S_WS,
		.data_out_num = I2S_DO,
		.data_in_num = I2S_DI
};

SynthiaImpl Synthia;
SliderInput Sliders;
EncoderInput Encoders;

SynthiaImpl::SynthiaImpl(){

}

void SynthiaImpl::begin(){
	Serial.begin(115200);

	Sliders.begin();
	Encoders.begin();

	input = new InputGPIO();
	input->preregisterButtons({ BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_ENC_L, BTN_ENC_R});
	LoopManager::addListener(input);
}

Input* SynthiaImpl::getInput() const{
	return input;
}

