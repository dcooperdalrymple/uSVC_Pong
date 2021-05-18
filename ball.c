#include "ball.h"

void initBall(ball_t *data, uint8_t index) {
    data->index = index;
    data->x = 0;
    data->y = 0;
    data->vx = 0;
    data->vy = 0;
}

void posBall(ball_t *data, int16_t x, int16_t y) {
    data->x = x << 4;
    data->y = y << 4;
}

void velBall(ball_t *data, int16_t x, int16_t y) {
    data->vx = x;
    data->vy = y;
}

void angleBall(ball_t *data, int16_t angle, int16_t speed) {
}

void updateBall(ball_t *data, paddle_t paddleLeft, paddle_t paddleRight) {
    data->x = data->x + data->vx;
    data->y = data->y + data->vy;

    if (data->y < (BALL_WALL_TOP << 4)) {
        data->y = (BALL_WALL_TOP << 4);
        if (data->vy < 0) data->vy = data->vy * -1;
    } else if (data->y > (BALL_WALL_BOTTOM << 4)) {
        data->y = (BALL_WALL_BOTTOM << 4);
        data->vy = data->vy * -1;
        if (data->vy > 0) data->vy = data->vy * -1;
    }

    if (data->x < (PADDLE_HIT_LEFT << 4)) {
        if (data->y >> 4 + BALL_SIZE_Y > paddleLeft.y && data->y >> 4 < paddleLeft.y + PADDLE_SIZE_Y) {
            data->x = (PADDLE_HIT_LEFT << 4);
            if (data->vx < 0) data->vx = data->vx * -1;
        }
    } else if (data->x > (PADDLE_HIT_RIGHT << 4)) {
        if (data->y >> 4 + BALL_SIZE_Y > paddleRight.y && data->y >> 4 < paddleRight.y + PADDLE_SIZE_Y) {
            data->x = (PADDLE_HIT_RIGHT << 4);
            if (data->vx > 0) data->vx = data->vx * -1;
        }
    }
}

void drawBall(ball_t data, playfield_t playfield) {
    putSprite(data.index, (data.x >> 4) - playfield.x, (data.y >> 4) - playfield.y, SPRITE_FLAGS_HANDLE_TOPLEFT, BALL_FRAMEINDEX);
}
