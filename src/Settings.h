#ifndef SYNTHIA_LIBRARY_SETTINGS_H
#define SYNTHIA_LIBRARY_SETTINGS_H

#include <Arduino.h>

//contains the raw readings for the sliders' actual range
struct SlidersCalibration {
	uint16_t sliderLeftUp = 2500;
	uint16_t sliderRightUp = 2500;
	uint16_t sliderLeftDown = 1100;
	uint16_t sliderRightDown = 1100;
};

struct SettingsData {
	bool tested = false;
	SlidersCalibration calibration;
};

class SettingsImpl {
public:
	bool begin();

	void store();

	SettingsData& get();

	void reset();

private:
	SettingsData data;
};

extern SettingsImpl Settings;

#endif //SYNTHIA_LIBRARY_SETTINGS_H
