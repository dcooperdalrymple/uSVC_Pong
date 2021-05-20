#include "paddle.h"

void initPaddle(paddle_t *data, uint8_t index, uint8_t frame, int32_t x) {
    data->index = index;
    data->pos.x = x;
    data->pos.y = 0;
    data->frame = frame;
}

void posPaddle(paddle_t *data, int32_t y) {
    if (y < (PADDLE_BOUNDS_TOP << FRACTIONAL_PART)) {
        y = (PADDLE_BOUNDS_TOP << FRACTIONAL_PART);
    } else if (y > (PADDLE_BOUNDS_BOTTOM << FRACTIONAL_PART)) {
        y = (PADDLE_BOUNDS_BOTTOM << FRACTIONAL_PART);
    }

    data->pos.y = y;
}

void movPaddle(paddle_t *data, int32_t y) {
    posPaddle(data, data->pos.y + y);
}

void drawPaddle(paddle_t data, playfield_t playfield) {
    putSprite(data.index, ((data.pos.x - playfield.pos.x) >> FRACTIONAL_PART), ((data.pos.y - playfield.pos.y) >> FRACTIONAL_PART), SPRITE_FLAGS_HANDLE_TOPLEFT, data.frame);
}
