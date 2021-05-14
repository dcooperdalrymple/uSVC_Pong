#ifndef COMMON_H_
#define COMMON_H_

typedef struct {
	int16_t x;
	int16_t y;

	// Previous draw values
	int16_t _x;
	int16_t _y;
} playfield_t;

typedef struct {
	uint8_t index; // Must be unique and less than MAX_ONSCREEN_SPRITES
	int16_t x;
	int16_t y;
	uint8_t frame;
} paddle_t;

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
