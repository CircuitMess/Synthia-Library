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
		slotAW->pinMode(i, AW9523::LED);
		slotAW->dim(i, 0);

		trackAW->pinMode(i, AW9523::LED);
		trackAW->dim(i, 0);
	}
}

void RGBMatrixOutput::push(const MatrixPixelData& data){
	AW9523* expanders[] = { trackAW, slotAW };

	for(int i = 0; i < 10; i++){
		auto pinR = map[i].pinR;
		auto pinG = map[i].pinG;
		auto pinB = map[i].pinB;
		auto pixel = data.get(i, 0);
		pixel.i = ::map(pixel.i, 0, 255, 1, 5);

		expanders[pinR.index]->dim(pinR.pin, std::round((float) (pixel.r * pixel.i) / 255.0f));
		expanders[pinG.index]->dim(pinG.pin, std::round((float) (pixel.g * pixel.i) / 255.0f));
		expanders[pinB.index]->dim(pinB.pin, std::round((float) (pixel.b * pixel.i) / 255.0f));
	}
}
