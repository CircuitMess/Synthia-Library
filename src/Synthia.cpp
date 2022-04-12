#include "Synthia.h"
#include "Pins.hpp"
#include <Loop/LoopManager.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <Devices/Matrix/MatrixOutput.h>
#include "Output/RGBMatrixOutput.h"
#include <Devices/Matrix/MatrixOutputBuffer.h>
#include <Devices/Matrix/MatrixPartOutput.h>


const i2s_pin_config_t i2s_pin_config = {
		.bck_io_num = I2S_BCK,
		.ws_io_num = I2S_WS,
		.data_out_num = I2S_DO,
		.data_in_num = I2S_DI
};

SynthiaImpl Synthia;
SliderInput Sliders;
EncoderInput Encoders;

SynthiaImpl::SynthiaImpl() : trackRGBOutput(1, 5), slotRGBOutput(5, 1), matrixBuffer(&charlie),
							 TrackRGB(SynthiaImpl::trackRGBOutput), SlotRGB(SynthiaImpl::slotRGBOutput),
							 trackOutput(&matrixBuffer), cursorOutput(&matrixBuffer), slidersOutput(&matrixBuffer),
							 TrackMatrix(trackOutput), CursorMatrix(cursorOutput), SlidersMatrix(slidersOutput){

}

void SynthiaImpl::begin(){
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

	input = new InputShift(INP_MISO, INP_CLK, INP_PL, 5);
	input->begin();
	input->preregisterButtons({BTN_1, BTN_2, BTN_3, BTN_4, BTN_5, BTN_ENC_L, BTN_ENC_R});
	LoopManager::addListener(input);

	if(!SPIFFS.begin()){
		Serial.println("couldn't start SPIFFS");
		for(;;);
	}


	Wire.begin(I2C_SDA, I2C_SCL);
	Wire.setClock(400000);

	charlie.init();
	matrixBuffer.init();

	TrackMatrix.begin();
	CursorMatrix.begin();
	SlidersMatrix.begin();


	trackExp = new AW9523(Wire, 0x5A);
	if(!trackExp->begin()){
		printf("Track expander begin error\n");
	}
	trackExp->setCurrentLimit(AW9523::IMAX_1Q);

	slotExp = new AW9523(Wire, 0x5B);
	if(!slotExp->begin()){
		printf("Slot expander begin error\n");
	}
	slotExp->setCurrentLimit(AW9523::IMAX_1Q);

	trackRGBOutput.set(trackExp, {
			RGBMatrixOutput::PixelMapping{14, 15, 13},
			RGBMatrixOutput::PixelMapping{7, 12, 6},
			RGBMatrixOutput::PixelMapping{4, 5, 3},
			RGBMatrixOutput::PixelMapping{1, 2, 0},
			RGBMatrixOutput::PixelMapping{10, 11, 9}
	});
	trackRGBOutput.init();
	TrackRGB.begin();

	slotRGBOutput.set(slotExp, {
			RGBMatrixOutput::PixelMapping{9, 10, 8},
			RGBMatrixOutput::PixelMapping{0, 1, 11},
			RGBMatrixOutput::PixelMapping{3, 4, 2},
			RGBMatrixOutput::PixelMapping{6, 7, 5},
			RGBMatrixOutput::PixelMapping{13, 14, 12}
	});
	slotRGBOutput.init();
	SlotRGB.begin();
}

InputShift* SynthiaImpl::getInput() const{
	return input;
}

AW9523* SynthiaImpl::getSlotExp() const{
	return slotExp;
}

AW9523* SynthiaImpl::getTrackExp() const{
	return trackExp;
}

