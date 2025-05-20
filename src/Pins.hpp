#ifndef SYNTHIA_LIBRARY_PINS_HPP
#define SYNTHIA_LIBRARY_PINS_HPP

//I2C bus with IS31 LED driver, first AW9523 expander with track RGBs
#define I2C_SDA_1 22
#define I2C_SCL_1 23

//I2C bus with XL9555 input expander, second AW9523 expander with slot RGBs
#define I2C_SDA_2 5
#define I2C_SCL_2 18

#define BTN_5 4
#define BTN_4 3
#define BTN_3 2
#define BTN_2 1
#define BTN_1 0
#define BTN_ENC_L 17
#define BTN_ENC_R 16

#define ENC_L1 34
#define ENC_L2 35

#define ENC_R1 32
#define ENC_R2 33

#define POT_L 39
#define POT_R 36

#define I2S_BCK 21
#define I2S_WS 4
#define I2S_DO 14
#define I2S_DI 15

//Note: Track RGB LEDs are marked 1-5 (RGBs on both sides are wired together!)
//Slot RGB LEDs are marked 6-10

//First AW9523 expander (track RGBs)
#define LED_G2 0
#define LED_G1 1
#define LED_R5 2
#define LED_R4 3
#define LED_R3 4
#define LED_R2 5
#define LED_R1 6
#define LED_B5 7
#define LED_G5 9
#define LED_G4 10
#define LED_G3 11
#define LED_B4 12
#define LED_B3 13
#define LED_B2 14
#define LED_B1 15


//Second AW9523 expander (slot RGBs)
#define LED_B9 0
#define LED_R9 1
#define LED_G9 2
#define LED_B8 3
#define LED_R8 4
#define LED_G8 5
#define LED_B7 6
#define LED_R7 7
#define LED_B10 9
#define LED_R10 10
#define LED_G10 11
#define LED_G7 12
#define LED_B6 13
#define LED_R6 14
#define LED_G6 15

#endif //SYNTHIA_LIBRARY_PINS_HPP
