#ifndef COMMON_H_
#define COMMON_H_

// Playfield

typedef struct {
	int16_t x;
	int16_t y;

	// Previous draw values
	int16_t _x;
	int16_t _y;
} playfield_t;

// Paddle

#define PADDLE_SIZE_X       	16
#define PADDLE_SIZE_Y       	64
#define PADDLE_OFFSET_X     	1
#define PADDLE_OFFSET_Y     	3
#define PADDLE_BOUNDS_TOP   	PADDLE_OFFSET_Y*8
#define PADDLE_BOUNDS_BOTTOM	(MAPSIZEY_TILEMAP-PADDLE_OFFSET_Y)*8-PADDLE_SIZE_Y
#define PADDLE_BOUNDS_LEFT		PADDLE_OFFSET_X*8
#define PADDLE_BOUNDS_RIGHT		(MAPSIZEX_TILEMAP-PADDLE_OFFSET_X)*8-PADDLE_SIZE_X
#define PADDLE_MIDDLE_Y			(PADDLE_BOUNDS_BOTTOM+PADDLE_BOUNDS_TOP)/2
#define PADDLE_HIT_LEFT			(PADDLE_OFFSET_X*8)+PADDLE_SIZE_X
#define PADDLE_HIT_RIGHT		(MAPSIZEX_TILEMAP-PADDLE_OFFSET_X)*8-PADDLE_SIZE_X

typedef struct {
	uint8_t index; // Must be unique and less than MAX_ONSCREEN_SPRITES
	int16_t x;
	int16_t y;
	uint8_t frame;
} paddle_t;

// Ball

#define BALL_SIZE_X			16
#define BALL_SIZE_Y			16
#define BALL_WALL_OFFSET	2
#define BALL_WALL_TOP		BALL_WALL_OFFSET*8
#define BALL_WALL_BOTTOM	(MAPSIZEY_TILEMAP-BALL_WALL_OFFSET)*8-BALL_SIZE_Y
#define BALL_START_X		(MAPSIZEX_TILEMAP*8-BALL_SIZE_X)/2
#define BALL_START_Y		(MAPSIZEY_TILEMAP*8-BALL_SIZE_Y)/2

typedef struct {
	uint16_t index;
	int16_t x;
	int16_t y;
	int16_t vx;
	int16_t vy;
} ball_t;

// Input

#define INPUT_UP 0
#define INPUT_UP_MASK (1<<INPUT_UP)
#define INPUT_RIGHT 1
#define INPUT_RIGHT_MASK (1<<INPUT_RIGHT)
#define INPUT_DOWN 2
#define INPUT_DOWN_MASK (1<<INPUT_DOWN)
#define INPUT_LEFT 3
#define INPUT_LEFT_MASK (1<<INPUT_LEFT)

typedef struct {
	uint8_t flags; // Bits 0->7: up, right, down, left, ...
} input_t;

#endif
