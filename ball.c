#include "ball.h"

void initBall(ball_t *data, uint8_t index) {
    data->index = index;
    data->pos.x = BALL_START_X << FRACTIONAL_PART;
    data->pos.y = BALL_START_Y << FRACTIONAL_PART;
    data->vel.x = 0;
    data->vel.y = 0;
}

void posBall(ball_t *data, vector_t pos) {
    data->pos.x = pos.x;
    data->pos.y = pos.y;
}

void velBall(ball_t *data, vector_t vel) {
    data->vel.x = vel.x;
    data->vel.y = vel.y;
}

void angleBall(ball_t *data, int8_t angle, int32_t speed) {
    data->vel.x = FIXED_MULFRACT(speed, sinTable[angle]);
    data->vel.y = FIXED_MULFRACT(speed, sinTable[(angle + 256) & 1023]);
}

void updateBall(ball_t *data, paddle_t paddleLeft, paddle_t paddleRight) {
    data->pos.x = data->pos.x + data->vel.x;
    data->pos.y = data->pos.y + data->vel.y;

    if (data->pos.y < (BALL_WALL_TOP << FRACTIONAL_PART)) {
        data->pos.y = (BALL_WALL_TOP << FRACTIONAL_PART);
        if (data->vel.y < 0) data->vel.y *= -1;
    } else if (data->pos.y > (BALL_WALL_BOTTOM << FRACTIONAL_PART)) {
        data->pos.y = (BALL_WALL_BOTTOM << FRACTIONAL_PART);
        if (data->vel.y > 0) data->vel.y *= -1;
    }

    if (data->pos.x < (PADDLE_HIT_LEFT << FRACTIONAL_PART) && data->pos.x + (BALL_SIZE_X << FRACTIONAL_PART) > ((PADDLE_HIT_LEFT - PADDLE_SIZE_X) << FRACTIONAL_PART)) {
        if (data->pos.y + (BALL_SIZE_Y << FRACTIONAL_PART) > paddleLeft.pos.y && data->pos.y < paddleLeft.pos.y + (PADDLE_SIZE_Y << FRACTIONAL_PART)) {
            //data->pos.x = (PADDLE_HIT_LEFT << FRACTIONAL_PART);
            if (data->vel.x < 0) data->vel.x *= -1;
        }
    } else if (data->pos.x + (BALL_SIZE_X << FRACTIONAL_PART) > (PADDLE_HIT_RIGHT << FRACTIONAL_PART) && data->pos.x < ((PADDLE_HIT_RIGHT + PADDLE_SIZE_X) << FRACTIONAL_PART)) {
        if (data->pos.y + (BALL_SIZE_Y << FRACTIONAL_PART) > paddleRight.pos.y && data->pos.y < paddleRight.pos.y + (PADDLE_SIZE_Y << FRACTIONAL_PART)) {
            //data->pos.x = ((PADDLE_HIT_RIGHT - BALL_SIZE_X) << FRACTIONAL_PART);
            if (data->vel.x > 0) data->vel.x *= -1;
        }
    }
}

void drawBall(ball_t data, playfield_t playfield) {
    putSprite(data.index, ((data.pos.x - playfield.pos.x) >> FRACTIONAL_PART), ((data.pos.y - playfield.pos.y) >> FRACTIONAL_PART), SPRITE_FLAGS_HANDLE_TOPLEFT, BALL_FRAMEINDEX);
}
