#ifndef SYNTHIA_LIBRARY_SETTINGS_H
#define SYNTHIA_LIBRARY_SETTINGS_H

#include <Arduino.h>

struct SettingsData {
	bool tested = false;

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
