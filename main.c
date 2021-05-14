/*
 *  USVC Template Project
 *
 *  Change/remove this copyright part when you create your own program!
 *
 *  Copyright 2019-2020 Nicola Wrachien (next-hack.com)
 *
 *  This file is part of next-hack's USCV Template project.
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program  is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  tl;dr
 *  Do whatever you want, this program is free! Though we won't
 *  reject donations https://next-hack.com/index.php/donate/ :)
 *
 */

#include "main.h"

input_t input;
playfield_t playfield;
paddle_t player;
paddle_t opponent;

int main(void) {
	initUsvc(NULL);	// Init uSVC Hardware

	uint32_t lastTime = millis();
	uint32_t timeNow = 0;
	int testLed = 0;

	initObjects();
	initTiles();

	while (1) {
		timeNow = millis();

		waitForVerticalBlank();
		removeAllSprites(0);

		drawPlayfield(&playfield, 0);

		animPaddle(&player, timeNow);
		drawPaddle(player, playfield);
		animPaddle(&opponent, timeNow);
		drawPaddle(opponent, playfield);

		drawSprites();

		if (timeNow - lastTime > 1000UL) {
			setLed(testLed);
			testLed = 1 - testLed;
			lastTime = timeNow;
		}

		checkInput(&input);

		if (checkInputFlag(input, INPUT_UP)) {
			movPlayfield(&playfield, 0, -1);
		}
		if (checkInputFlag(input, INPUT_DOWN)) {
			movPlayfield(&playfield, 0, 1);
		}
		if (checkInputFlag(input, INPUT_RIGHT)) {
			movPlayfield(&playfield, 1, 0);
		}
		if (checkInputFlag(input, INPUT_LEFT)) {
			movPlayfield(&playfield, -1, 0);
		}

	}
}

void initObjects() {
	clearInput(&input);
	initPlayfield(&playfield);
	initPaddle(&player, 0);
	posPaddle(&player, 100, 100);
	initPaddle(&opponent, 1);
	posPaddle(&opponent, 200, 100);
}

void initTiles() {
	memcpy(tiles, tileData, sizeof(tileData));
	setNumberOfRamTiles(MAXTILEINDEX);
	drawPlayfield(&playfield, 1);
}
