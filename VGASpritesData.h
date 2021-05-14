#ifndef VGASPRITESDATA_H_
#define VGASPRITESDATA_H_

#include "usvc_kernel/usvc_kernel.h"

#define SPRITEDATA_NUMPIXELS 1632
#define FRAMEDATA_NUMFRAMES 9
#define ANIMDATA_NUMANIM 2
#define ENTITYDATA_NUMENTITIES 2

#define SMILE 0
#define SMILE_SMILE 0

#define COIN 1
#define COIN_ROTATION 0

#define SMILE_SMILE_FRAMEINDEX 0x0000
#define SMILE_SMILE_NUMFRAMES 0x0001

#define COIN_ROTATION_FRAMEINDEX 0x0001
#define COIN_ROTATION_NUMFRAMES 0x0008

typedef struct {
	uint16_t frameIndex; // index to the first frame data
	uint8_t numFrames; // number of frames
} anim_t;

extern const uint8_t spriteData[SPRITEDATA_NUMPIXELS];
extern const frame_t frameData[FRAMEDATA_NUMFRAMES];
extern const anim_t animData[ANIMDATA_NUMANIM];
extern const anim_t* entityData[ENTITYDATA_NUMENTITIES];
extern const uint16_t entityAnimStartIndex[ENTITYDATA_NUMENTITIES]; // this is redundant but by using this, the compiler will save a lot of RAM

#endif
