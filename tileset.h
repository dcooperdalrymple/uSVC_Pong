#ifndef TILESET_H_
#define TILESET_H_

#include <stdint.h>

#define MAXTILEINDEX 14
#define TILESIZEX 8
#define TILESIZEY 8
extern const uint8_t tileData[MAXTILEINDEX][TILESIZEX * TILESIZEY];

#endif
