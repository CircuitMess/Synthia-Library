#ifndef SYNTHIA_LIBRARY_NULLOUTPUT_HPP
#define SYNTHIA_LIBRARY_NULLOUTPUT_HPP
/*
 * TODO - Temporary class, delete after actual output is created
 */
#include <Devices/Matrix/MatrixOutput.h>

class NullOutput : public MatrixOutput {
public:
    NullOutput(uint16_t width, uint16_t height) : MatrixOutput(width, height) {}

    void init() override {}

    void push(const MatrixPixelData &data) override {}
};


#endif //SYNTHIA_LIBRARY_NULLOUTPUT_HPP
