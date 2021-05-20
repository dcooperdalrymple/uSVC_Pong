#ifndef PADDLE_H_
#define PADDLE_H_

#include "main.h"
#include <stdint.h>

void initPaddle(paddle_t *data, uint8_t index, uint8_t frame, int32_t x);
void posPaddle(paddle_t *data, int32_t y);
void movPaddle(paddle_t *data, int32_t y);
void drawPaddle(paddle_t data, playfield_t playfield);

#endif
