#ifndef PADDLE_H_
#define PADDLE_H_

#include "main.h"
#include <stdint.h>

void clearInput();
void checkInput();
void handleKey(uint8_t code, input_t *input);
uint8_t checkInputFlag(input_t input, uint8_t flag);
uint8_t checkInputFlags(input_t input, uint8_t mask);

#endif
