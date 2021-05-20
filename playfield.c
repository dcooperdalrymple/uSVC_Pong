#include "playfield.h"

void initPlayfield(playfield_t *data) {
	data->pos.x = 0;
	data->pos.y = 0;

	// Force redraw
	data->tileX = -1;
	data->tileY = -1;
}

void drawPlayfield(playfield_t *data, uint8_t forceRedraw) {
	int16_t posX = data->pos.x >> FRACTIONAL_PART;
	int16_t posY = data->pos.y >> FRACTIONAL_PART;
	int16_t tileX = posX / 8;
	int16_t tileY = posY / 8;

	if (tileX != data->tileX || tileY != data->tileY || forceRedraw) {
		data->tileX = tileX;
		data->tileY = tileY;

		int16_t mapX = 0;
	    int16_t mapY = 0;
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

	setXScroll(posX % 8);
	setYScroll(posY % 8);
}

void posPlayfield(playfield_t *data, vector_t pos) {
	if (pos.x > ((MAPSIZEX_TILEMAP * TILE_SIZE_X - SCREEN_SIZE_X) << FRACTIONAL_PART)) {
		pos.x = ((MAPSIZEX_TILEMAP * TILE_SIZE_X - SCREEN_SIZE_X) << FRACTIONAL_PART);
	} else if (pos.x < 0) {
		pos.x = 0;
	}

	if (pos.y > ((MAPSIZEY_TILEMAP * TILE_SIZE_Y - SCREEN_SIZE_Y) << FRACTIONAL_PART)) {
		pos.y = ((MAPSIZEY_TILEMAP * TILE_SIZE_Y - SCREEN_SIZE_Y) << FRACTIONAL_PART);
	} else if (pos.y < 0) {
		pos.y = 0;
	}

	data->pos.x = pos.x;
	data->pos.y = pos.y;
}

void movPlayfield(playfield_t *data, vector_t delta) {
	delta.x = data->pos.x + delta.x;
	delta.y = data->pos.y + delta.y;
	posPlayfield(data, delta);
}

void focusPlayfield(playfield_t *data, vector_t pos) {
	pos.x = (pos.x / (MAPSIZEX_TILEMAP * TILE_SIZE_X)) * (MAPSIZEX_TILEMAP * TILE_SIZE_X - SCREEN_SIZE_X);
	pos.y = (pos.y / (MAPSIZEY_TILEMAP * TILE_SIZE_Y)) * (MAPSIZEY_TILEMAP * TILE_SIZE_Y - SCREEN_SIZE_Y);
	posPlayfield(data, pos);
}
