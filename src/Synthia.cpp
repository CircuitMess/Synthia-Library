#include "Synthia.h"
#include <WiFi.h>
#include <Devices/Matrix/MatrixOutput.h>
#include "Output/RGBMatrixOutput.h"
#include <Devices/Matrix/MatrixOutputBuffer.h>
#include <Devices/Matrix/MatrixPartOutput.h>
#include <unordered_map>

const i2s_pin_config_t i2s_pin_config = {
		.bck_io_num = I2S_BCK,
		.ws_io_num = I2S_WS,
		.data_out_num = I2S_DO,
		.data_in_num = I2S_DI
};

SynthiaImpl Synthia;
SliderInput Sliders;
EncoderInput Encoders;

SynthiaImpl::SynthiaImpl() : charlieBuffer(&charlie), trackOutput(&charlieBuffer), cursorOutput(&charlieBuffer), slidersOutput(&charlieBuffer),
							 TrackMatrix(trackOutput), CursorMatrix(cursorOutput), SlidersMatrix(slidersOutput),
							 RGBBuffer(&RGBOutput), slotRGBOutput(&RGBBuffer), trackRGBOutput(&RGBBuffer),
							 TrackRGB(trackRGBOutput), SlotRGB(slotRGBOutput), aw9523Slot(Wire), aw9523Track(Wire1){

}

void SynthiaImpl::begin(){
	if(psramFound()){
		Serial.printf("PSRAM init: %s, free: %d B\n", psramInit() ? "Yes" : "No", ESP.getFreePsram());
	}else{
		Serial.println("No PSRAM detected");
	}

	disableCore0WDT();
	disableCore1WDT();

	analogReadResolution(10);
	analogSetAttenuation(ADC_11db);

	WiFi.mode(WIFI_OFF);
	btStop();

	Settings.begin();
	Sliders.begin();
	Encoders.begin();

	Wire.begin(I2C_SDA_2, I2C_SCL_2);
	Wire.setClock(400000);

	inputExpander.begin(0b0100000, I2C_SDA_2, I2C_SCL_2);

	input = new InputI2C(&inputExpander);
	input->preregisterButtons({BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_ENC_L, BTN_ENC_R});
	LoopManager::addListener(input);


	Wire1.begin(I2C_SDA_1, I2C_SCL_1);
	Wire1.setClock(400000);


	if(!SPIFFS.begin()){
		Serial.println("couldn't start SPIFFS");
		for(;;);
	}


	charlie.init();
	charlie.setBrightness(Settings.get().brightness);

	TrackMatrix.begin();
	CursorMatrix.begin();
	SlidersMatrix.begin();

	aw9523Track.begin();
	aw9523Slot.begin();


	RGBOutput.set(&aw9523Slot, &aw9523Track, {
		RGBMatrixOutput::PixelMapping{ { 0, LED_R1 }, { 0, LED_G1 }, { 0, LED_B1 } },
		RGBMatrixOutput::PixelMapping{ { 0, LED_R2 }, { 0, LED_G2 }, { 0, LED_B2 } },
		RGBMatrixOutput::PixelMapping{ { 0, LED_R3 }, { 0, LED_G3 }, { 0, LED_B3 } },
		RGBMatrixOutput::PixelMapping{ { 0, LED_R4 }, { 0, LED_G4 }, { 0, LED_B4 } },
		RGBMatrixOutput::PixelMapping{ { 0, LED_R5 }, { 0, LED_G5 }, { 0, LED_B5 } },
		RGBMatrixOutput::PixelMapping{ { 1, LED_R6 }, { 1, LED_G6 }, { 1, LED_B6 } },
		RGBMatrixOutput::PixelMapping{ { 1, LED_R7 }, { 1, LED_G7 }, { 1, LED_B7 } },
		RGBMatrixOutput::PixelMapping{ { 1, LED_R8 }, { 1, LED_G8 }, { 1, LED_B8 } },
		RGBMatrixOutput::PixelMapping{ { 1, LED_R9 }, { 1, LED_G9 }, { 1, LED_B9 } },
		RGBMatrixOutput::PixelMapping{ { 1, LED_R10 }, { 1, LED_G10 }, { 1, LED_B10 } }
	});
	RGBOutput.init();

	TrackRGB.begin();
	SlotRGB.begin();
}

Input* SynthiaImpl::getInput() const{
	return input;
}


int SynthiaImpl::btnToSlot(uint8_t i){
	static const std::unordered_map<uint8_t, uint8_t> map = {
			{ BTN_1, 0 },
			{ BTN_2, 1 },
			{ BTN_3, 2 },
			{ BTN_4, 3 },
			{ BTN_5, 4 },
	};

	auto pair = map.find(i);
	if(pair == map.end()) return -1;
	return pair->second;
}

int SynthiaImpl::slotToBtn(uint8_t i){
	static const std::unordered_map<uint8_t, uint8_t> map = {
			{ 0, BTN_1 },
			{ 1, BTN_2 },
			{ 2, BTN_3 },
			{ 3, BTN_4 },
			{ 4, BTN_5 },
	};

	auto pair = map.find(i);
	if(pair == map.end()) return -1;
	return pair->second;
}

void SynthiaImpl::clearMatrices(){
	for(auto matrix : { Synthia.TrackMatrix, Synthia.SlidersMatrix, Synthia.CursorMatrix, Synthia.SlotRGB, Synthia.TrackRGB }){
		matrix.stopAnimations();
		matrix.clear();
		matrix.push();
	}
}

IS31FL3731& SynthiaImpl::getCharlie(){
	return charlie;
}
