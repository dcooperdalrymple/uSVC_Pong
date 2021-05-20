#ifndef COMMON_H_
#define COMMON_H_

#define FRACTIONAL_PART			16

// Input

#define INPUT_UP 0
#define INPUT_UP_MASK (1<<INPUT_UP)
#define INPUT_RIGHT 1
#define INPUT_RIGHT_MASK (1<<INPUT_RIGHT)
#define INPUT_DOWN 2
#define INPUT_DOWN_MASK (1<<INPUT_DOWN)
#define INPUT_LEFT 3
#define INPUT_LEFT_MASK (1<<INPUT_LEFT)
#define INPUT_START 4
#define INPUT_START_MASK (1<<INPUT_START)

typedef struct {
	uint8_t flags;
	uint8_t prevFlags;
} input_t;

typedef struct {
	input_t player;
	input_t opponent;
} controls_t;

// Playfield

typedef struct {
	vector_t pos; // Not using FRACTIONAL_PART calculations

	// Previous draw values
	int16_t tileX;
	int16_t tileY;
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
	vector_t pos;
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
#define BALL_START_SPEED	4

typedef struct {
	uint16_t index;
	vector_t pos;
	vector_t vel;
} ball_t;

#endif
