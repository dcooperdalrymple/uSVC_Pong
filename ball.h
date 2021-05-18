#ifndef BALL_H_
#define BALL_H_

#include "main.h"
#include <stdint.h>

void initBall(ball_t *data, uint8_t index);
void posBall(ball_t *data, int16_t x, int16_t y);
void velBall(ball_t *data, int16_t x, int16_t y);
void angleBall(ball_t *data, int16_t angle, int16_t speed);
void updateBall(ball_t *data, paddle_t paddleLeft, paddle_t paddleRight);
void drawBall(ball_t data, playfield_t playfield);

#endif
