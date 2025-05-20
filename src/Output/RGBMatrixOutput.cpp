#include <Util/Timer.h>
#include "RGBMatrixOutput.h"

RGBMatrixOutput::RGBMatrixOutput() : MatrixOutput(10, 1){

}

void RGBMatrixOutput::set(AW9523* slotAW, AW9523* trackAW, const std::array<PixelMapping, 10>& map){
	this->slotAW = slotAW;
	this->trackAW = trackAW;
	this->map = map;
}

void RGBMatrixOutput::init(){
	for(int i = 0; i < 16; ++i){
		slotAW->pinMode(i, AW9523::OUT);
		slotAW->write(i, true);

		trackAW->pinMode(i, AW9523::OUT);
		trackAW->write(i, true);
	}
}

void RGBMatrixOutput::push(const MatrixPixelData& data){
	AW9523* expanders[] = { trackAW, slotAW };

	for(int i = 0; i < 10; i++){
		auto pinR = map[i].pinR;
		auto pinG = map[i].pinG;
		auto pinB = map[i].pinB;
		auto pixel = data.get(i, 0);

		expanders[pinR.index]->write(pinR.pin, (pixel.r * pixel.i / 255) < (255 / 2));
		expanders[pinG.index]->write(pinG.pin, (pixel.g * pixel.i / 255) < (255 / 2));
		expanders[pinB.index]->write(pinB.pin, (pixel.b * pixel.i / 255) < (255 / 2));
	}
}
