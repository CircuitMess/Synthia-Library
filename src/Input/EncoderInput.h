#ifndef SYNTHIA_LIBRARY_ENCODERINPUT_H
#define SYNTHIA_LIBRARY_ENCODERINPUT_H

#include <Loop/LoopListener.h>
#include "../Pins.hpp"
#include <vector>
#include "../WithListeners.h"

class EncoderInput;

class SynthiaEncoderListener {
	friend EncoderInput;

private:

	virtual void leftEncMove(int8_t amount);
	virtual void rightEnctMove(int8_t amount);
};

class EncoderInput : public LoopListener, public WithListeners<SynthiaEncoderListener> {

public:
	EncoderInput();

	void begin();

	void loop(uint _time) override;

	int getRightEncValue() const;

	int getLeftEncValue() const;

private:
	int leftEncCounter = 0;
	int rightEncCounter = 0;

	int currentStateLeft;
	int currentStateRight;
	int previousStateLeft;
	int previousStateRight;

};

#endif //SYNTHIA_LIBRARY_ENCODERINPUT_H
