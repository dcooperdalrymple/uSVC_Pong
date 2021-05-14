#ifndef PLAYFIELD_H_
#define PLAYFIELD_H_

#include "main.h"
#include <stdint.h>

#define MAPSIZEX_LEVEL1 80
#define MAPSIZEY_LEVEL1 50
extern const uint16_t gameMap_level1[MAPSIZEY_LEVEL1 * MAPSIZEX_LEVEL1];
//extern const level_t gameMap_level1Obj;

void initPlayfield(playfield_t *data);
void drawPlayfield(playfield_t *data, uint8_t forceRedraw);
void posPlayfield(playfield_t *data, int16_t x, int16_t y);
void movPlayfield(playfield_t *data, int16_t x, int16_t y);

#endif
