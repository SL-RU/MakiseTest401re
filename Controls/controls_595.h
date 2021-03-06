#ifndef controls_595_H
#define controls_595_H 1

#include "controls.h"
#include "gpio.h"

#define controls_595_kdat   GPIOB, GPIO_PIN_5
#define controls_595_kclk   GPIOB, GPIO_PIN_4
#define controls_595_klatch GPIOB, GPIO_PIN_3
#define controls_595_len    8 //how much bits in seraial. 32 is max


//buttons are connected one pin to 595 register and other to the input pin of MCU
typedef struct 
{
    uint8_t enabled;
    uint32_t id; //global id;
    
    GPIO_TypeDef* gpio; //input MCU port
    uint16_t pin;       //input MCU pin

    uint16_t pos; //position in 595 serial sequence starting from 0

    uint8_t polarity_pressed; //if 1 - pressed when readpin = 1, else when 0
    uint8_t pressed;
    uint32_t press_start_time;
} controls_595_ButtonState;

typedef struct
{
    uint8_t enabled;
    uint32_t id; //global id;

    uint16_t pos; //position in 595 serial sequence starting from 0

    uint8_t val; //output value
} controls_595_OutputState;

void controls_595_init(controls_595_ButtonState *buttons,
		       uint8_t buttons_len,
		       controls_595_OutputState *outs,
		       uint8_t outs_len,
		       void (*buttons_handler)(
			   uint32_t id,
			   uint8_t event,
			   uint32_t time));

void controls_595_update();
#endif
