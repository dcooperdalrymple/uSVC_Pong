#include "paddle.h"

void initPaddle(paddle_t *data, uint8_t index) {
    data->index = index;
    data->x = 0;
    data->y = 0;
    data->frame = 1;
}

void posPaddle(paddle_t *data, int16_t x, int16_t y) {
    data->x = x;
    data->y = y;
}

void drawPaddle(paddle_t data, playfield_t playfield) {
    putSprite(data.index, data.x - playfield.x, data.y - playfield.y, SPRITE_FLAGS_HANDLE_CENTER, data.frame);
}

void animPaddle(paddle_t *data, uint32_t time) {
    data->frame++;
    if (data->frame > 8) {
        data->frame = 1;
    }
}
