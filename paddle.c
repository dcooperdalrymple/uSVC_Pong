#include "paddle.h"

void initPaddle(paddle_t *data, uint8_t index, uint8_t frame) {
    data->index = index;
    data->x = 0;
    data->y = 0;
    data->frame = frame;
}

void posPaddle(paddle_t *data, int16_t x, int16_t y) {
    data->x = x;
    data->y = y;
}

void movPaddle(paddle_t *data, int16_t x, int16_t y) {
    posPaddle(data, data->x + x, data->y + y);
}

void drawPaddle(paddle_t data, playfield_t playfield) {
    putSprite(data.index, data.x - playfield.x, data.y - playfield.y, SPRITE_FLAGS_HANDLE_TOPLEFT, data.frame);
}
