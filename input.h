#ifndef PADDLE_H_
#define PADDLE_H_

#include "main.h"
#include <stdint.h>

void clearInput(input_t *input);
void clearControls(controls_t *controls);
void checkInput(controls_t *controls);
void handleKey(uint8_t code, controls_t *controls);
void handleGamepad(gamePadState_t gps, controls_t *controls);
uint8_t checkInputFlag(input_t input, uint8_t flag);
uint8_t checkInputFlags(input_t input, uint8_t mask);
uint8_t checkInputPrevFlag(input_t input, uint8_t flag);
uint8_t checkInputPrevFlags(input_t input, uint8_t mask);
uint8_t checkInputPress(input_t input, uint8_t flag);
uint8_t checkInputRelease(input_t input, uint8_t flag);

#endif
