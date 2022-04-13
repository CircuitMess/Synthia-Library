#include <Util/Timer.h>
#include "RGBMatrixOutput.h"

RGBMatrixOutput* RGBMatrixOutput::rgb = nullptr;
std::vector<std::array<bool, 8>> RGBMatrixOutput::ledStates(4);

RGBMatrixOutput::RGBMatrixOutput() : MatrixOutput(10, 1){
	rgb = this;
}

void RGBMatrixOutput::set(ShiftOutput* output, const std::array<PixelMapping, 10>& map){
	this->output = output;
	this->map = map;
}

void RGBMatrixOutput::init(){
	output->setAll(true);

	timer = timerBegin(0, 80, true);
	timerAttachInterrupt(timer, &timerInterrupt, true);    // P3= edge triggered

	timerAlarmWrite(timer, 1000 * 8 / 100, true); // 125 Hz, 8 bit resolution
	timerAlarmEnable(timer);
	timerStart(timer);
}

void RGBMatrixOutput::push(const MatrixPixelData& data){
	for(int i = 0; i < 10; i++){
		auto pinR = map[i].pinR;
		auto pinG = map[i].pinG;
		auto pinB = map[i].pinB;
		auto pixel = data.get(i, 0);

		dutyCyles[pinR.index][pinR.pin] = pixel.r * pixel.i / 255;
		dutyCyles[pinG.index][pinG.pin] = pixel.g * pixel.i / 255;
		dutyCyles[pinB.index][pinB.pin] = pixel.b * pixel.i / 255;
	}
}

void IRAM_ATTR RGBMatrixOutput::timerInterrupt(){
	rgb->duty++;

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 8; j++){
			ledStates[i][j] = !(rgb->dutyCyles[i][j] != 0 && rgb->duty <= rgb->dutyCyles[i][j]);
		}
	}

	rgb->output->send(ledStates);
}
