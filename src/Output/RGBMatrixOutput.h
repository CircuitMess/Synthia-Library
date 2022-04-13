#ifndef SYNTHIA_LIBRARY_RGBMATRIXOUTPUT_H
#define SYNTHIA_LIBRARY_RGBMATRIXOUTPUT_H

#include <Arduino.h>
#include <Devices/ShiftOutput.h>
#include <Devices/Matrix/MatrixOutput.h>

// 10x1: 0-4 track matrix, 5-9 slot matrix
class RGBMatrixOutput : public MatrixOutput {
public:
	struct PixelPin { uint8_t index, pin; };
	struct PixelMapping { PixelPin pinR, pinG, pinB; };

	RGBMatrixOutput();

	void set(ShiftOutput* output, const std::array<PixelMapping, 10>& map);

	void init() override;
	void push(const MatrixPixelData& data) override;

	static void IRAM_ATTR timerInterrupt();

private:
	ShiftOutput* output;
	std::array<PixelMapping, 10> map;

	std::array<std::array<uint8_t, 8>, 4> dutyCyles;
	uint8_t duty = 0;

	hw_timer_t* timer = nullptr;

	static RGBMatrixOutput* rgb;
	static std::vector<std::array<bool, 8>> ledStates;
};


#endif //SYNTHIA_LIBRARY_RGBMATRIXOUTPUT_H
