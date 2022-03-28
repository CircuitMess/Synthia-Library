#include "SlidersMatrixOutput.h"

SlidersMatrixOutput::SlidersMatrixOutput(MatrixOutputBuffer* output) : MatrixPartOutput(output, 2, 8){}

std::pair<uint16_t, uint16_t> SlidersMatrixOutput::map(uint16_t x, uint16_t y){
	if(y < 2){
		return {14 + y, 7 - x};
	}else{
		return {15 - y, 7 - x};
	}
}
