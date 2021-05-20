#ifndef BALL_H_
#define BALL_H_

#include "main.h"
#include <stdint.h>
#include "sinTable.h"
#include "fastApproxMath.h"

void initBall(ball_t *data, uint8_t index);
void posBall(ball_t *data, vector_t pos);
void velBall(ball_t *data, vector_t vel);
void angleBall(ball_t *data, int8_t angle, int32_t speed);
void updateBall(ball_t *data, paddle_t paddleLeft, paddle_t paddleRight);
void drawBall(ball_t data, playfield_t playfield);

#endif
