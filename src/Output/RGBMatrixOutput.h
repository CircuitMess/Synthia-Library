#ifndef SYNTHIA_LIBRARY_RGBMATRIXOUTPUT_H
#define SYNTHIA_LIBRARY_RGBMATRIXOUTPUT_H

#include <Arduino.h>
#include <Devices/AW9523.h>
#include <Devices/Matrix/MatrixOutput.h>

class RGBMatrixOutput : public MatrixOutput {
public:
	struct PixelMapping { uint8_t pinR, pinG, pinB; };

	RGBMatrixOutput(uint16_t width, uint16_t height);

	void set(AW9523* expander, const std::array<PixelMapping, 5>& map);

	void init() override;
	void push(const MatrixPixelData& data) override;

private:
	AW9523* expander;
	std::array<PixelMapping, 5> map;

};


#endif //SYNTHIA_LIBRARY_RGBMATRIXOUTPUT_H
