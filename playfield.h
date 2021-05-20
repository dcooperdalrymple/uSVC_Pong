#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

#include "main.h"
#include <stdint.h>

void initPlayfield(playfield_t *data);
void drawPlayfield(playfield_t *data, uint8_t forceRedraw);
void posPlayfield(playfield_t *data, vector_t pos);
void movPlayfield(playfield_t *data, vector_t delta);
void focusPlayfield(playfield_t *data, vector_t pos);

#endif
