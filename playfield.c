#include "playfield.h"

void initPlayfield(playfield_t *data) {
	data->x = 0;
	data->y = 0;

	// Force redraw
	data->_x = -1;
	data->_y = -1;
}

void drawPlayfield(playfield_t *data, uint8_t forceRedraw) {
	int16_t mapX = 0;
    int16_t mapY = 0;
	int16_t tileX = data->x / 8;
	int16_t tileY = data->y / 8;

	if (tileX != data->_x || tileY != data->_y || forceRedraw) {
		data->_x = tileX;
		data->_y = tileY;

		for (int16_t sy = 0; sy < VRAMY; sy++) {
			mapY = (sy + tileY) % MAPSIZEY_TILEMAP;
	        for (int16_t sx = 0; sx < VRAMX; sx++) {
				mapX = (sx + tileX) % MAPSIZEX_TILEMAP;
	            placeTile(sx, sy, tileMap[mapX + MAPSIZEX_TILEMAP * mapY]);
	        }
	    }

		freeSpriteTiles();
	} else {
		restoreBackgroundTiles();
	}

	setXScroll(data->x % 8);
	setYScroll(data->y % 8);
}

void posPlayfield(playfield_t *data, int16_t x, int16_t y) {
	if (x > TILE_SIZE_X * (MAPSIZEX_TILEMAP - VRAMX)) x = TILE_SIZE_X * (MAPSIZEX_TILEMAP - VRAMX);
	else if (x < 0) x = 0;

	if (y > TILE_SIZE_Y * (MAPSIZEY_TILEMAP - VRAMY)) y = TILE_SIZE_Y * (MAPSIZEY_TILEMAP - VRAMY);
	else if (y < 0) y = 0;

	data->x = x;
	data->y = y;
}

void movPlayfield(playfield_t *data, int16_t x, int16_t y) {
	posPlayfield(data, data->x + x, data->y + y);
}
