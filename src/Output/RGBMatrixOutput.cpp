#include "RGBMatrixOutput.h"

RGBMatrixOutput::RGBMatrixOutput(uint16_t width, uint16_t height) : MatrixOutput(width, height){

}

void RGBMatrixOutput::set(AW9523* expander, const std::array<PixelMapping, 5>& map){
	this->expander = expander;
	this->map = map;
}

void RGBMatrixOutput::init(){
	for(int i = 0; i < 5; i++){
		expander->pinMode(map[i].pinR, AW9523::LED);
		expander->pinMode(map[i].pinG, AW9523::LED);
		expander->pinMode(map[i].pinB, AW9523::LED);

		expander->dim(map[i].pinR, 0);
		expander->dim(map[i].pinG, 0);
		expander->dim(map[i].pinB, 0);
	}
}

void RGBMatrixOutput::push(const MatrixPixelData& data){
	// TODO: optimize pushing to a single transaction
	for(int i = 0; i < 5; i++){
		const uint8_t x = min(i, data.getWidth() - 1);
		const uint8_t y = min(i, data.getHeight() - 1);
		MatrixPixel pixel = data.get(x, y);
		pixel.i = 100;
		expander->dim(map[i].pinR, pixel.r * pixel.i / 255);
		expander->dim(map[i].pinB, pixel.g * pixel.i / 255);
		expander->dim(map[i].pinG, pixel.b * pixel.i / 255);
	}
}
