#ifndef PADDLE_H_
#define PADDLE_H_

#include "main.h"
#include <stdint.h>

void initPaddle(paddle_t *data, uint8_t index);
void posPaddle(paddle_t *data, int16_t x, int16_t y);
void drawPaddle(paddle_t data, playfield_t playfield);
void animPaddle(paddle_t *data, uint32_t time);

#endif
