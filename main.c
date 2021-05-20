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

controls_t controls;
playfield_t playfield;
paddle_t player;
paddle_t opponent;
ball_t ball;
uint8_t paused;
uint8_t started;

int main(void) {
	initUsvc(NULL);	// Init uSVC Hardware

	uint32_t lastTime = millis();
	uint32_t timeNow = 0;
	int testLed = 0;
	vector_t vec = { .x = 0, .y = 0 };
	paused = 1;
	started = 0;

	#if !NO_USB
	usbSetKeyboardInstallationCompleteCallback(seedRandom);
	#endif

	initObjects();
	initTiles();

	while (1) {
		timeNow = millis();

		waitForVerticalBlank();
		removeAllSprites(0);

		drawPlayfield(&playfield, 0);
		drawPaddle(player, playfield);
		drawPaddle(opponent, playfield);
		drawBall(ball, playfield);

		drawSprites();

		if (timeNow - lastTime > 1000UL) {
			setLed(testLed);
			testLed = 1 - testLed;
			lastTime = timeNow;
		}

		checkInput(&controls);

		if (checkInputRelease(controls.player, INPUT_START) || checkInputRelease(controls.opponent, INPUT_START)) {
			if (paused && !started) {
				startBall();
				started = 1;
			}
			paused = !paused ? 1 : 0;
		}

		if (!paused) {

			if (checkInputFlag(controls.player, INPUT_UP)) {
				movPaddle(&player, -2 << FRACTIONAL_PART);
			}
			if (checkInputFlag(controls.player, INPUT_DOWN)) {
				movPaddle(&player, 2 << FRACTIONAL_PART);
			}

			if (checkInputFlag(controls.opponent, INPUT_UP)) {
				movPaddle(&opponent, -2 << FRACTIONAL_PART);
			}
			if (checkInputFlag(controls.opponent, INPUT_DOWN)) {
				movPaddle(&opponent, 2 << FRACTIONAL_PART);
			}

			updateBall(&ball, player, opponent);

		}

		vec.x = ball.pos.x + ((BALL_SIZE_X / 2) << FRACTIONAL_PART);
		vec.y = ball.pos.y + ((BALL_SIZE_Y / 2) << FRACTIONAL_PART);
		focusPlayfield(&playfield, ball.pos);
	}
}

void initObjects(void) {
	clearControls(&controls);

	initPlayfield(&playfield);

	initPaddle(&player, 0, PADDLE_FRAMEINDEX, (PADDLE_BOUNDS_LEFT << FRACTIONAL_PART));
	posPaddle(&player, (PADDLE_MIDDLE_Y << FRACTIONAL_PART));
	initPaddle(&opponent, 1, (PADDLE_FRAMEINDEX+1), (PADDLE_BOUNDS_RIGHT << FRACTIONAL_PART));
	posPaddle(&opponent, (PADDLE_MIDDLE_Y << FRACTIONAL_PART));

	initBall(&ball, 3);
}

void initTiles(void) {
	memcpy(tiles, tileData, sizeof(tileData));
	setNumberOfRamTiles(MAXTILEINDEX);
	drawPlayfield(&playfield, 1);
}

void seedRandom(void) {
	srand(millis());
}

void startBall(void) {
	seedRandom();

	vector_t vec = {
		.x = BALL_START_X << FRACTIONAL_PART,
	    .y = BALL_START_Y << FRACTIONAL_PART
	};
	posBall(&ball, vec);

	int8_t angle = 0;
	uint8_t random = (uint8_t)(rand() & 0x07);
	switch (random) {
		case 0:
			angle = 45;
			break;
		case 1:
			angle = -45;
			break;
		case 2:
			angle = 30;
			break;
		case 3:
			angle = -30;
			break;
		case 4:
			angle = 25;
			break;
		case 5:
			angle = -25;
			break;
		case 6:
			angle = 15;
			break;
		case 7:
			angle = -15;
			break;

	}
	angleBall(&ball, angle, (BALL_START_SPEED << FRACTIONAL_PART));
}
