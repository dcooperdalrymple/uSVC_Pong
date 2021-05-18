#ifndef PADDLE_H_
#define PADDLE_H_

#include "main.h"
#include <stdint.h>

void initPaddle(paddle_t *data, uint8_t index, uint8_t frame);
void posPaddle(paddle_t *data, int16_t x, int16_t y);
void movPaddle(paddle_t *data, int16_t x, int16_y y);
void drawPaddle(paddle_t data, playfield_t playfield);

#endif
