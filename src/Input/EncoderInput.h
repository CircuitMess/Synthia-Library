#ifndef SYNTHIA_LIBRARY_ENCODERINPUT_H
#define SYNTHIA_LIBRARY_ENCODERINPUT_H

#include <Loop/LoopListener.h>
#include "../WithListeners.h"

class EncoderInput;

class EncoderListener {
friend EncoderInput;

private:
	virtual void leftEncMove(int8_t amount);
	virtual void rightEncMove(int8_t amount);

};

class EncoderInput : public LoopListener, public WithListeners<EncoderListener> {
public:
	EncoderInput();

	void begin();
	void loop(uint time) override;

private:
	int prevStateLeft = 0;
	int prevStateRight = 0;

};

#endif //SYNTHIA_LIBRARY_ENCODERINPUT_H
