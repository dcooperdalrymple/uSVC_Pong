#ifndef PY_SPRITES_H_
#define PY_SPRITES_H_

#include "usvc_kernel/usvc_kernel.h"

#define SPRITEDATA_NUMPIXELS 2304
#define FRAMEDATA_NUMFRAMES 3
#define ANIMDATA_NUMANIM 2
#define ENTITYDATA_NUMENTITIES 2

#define BALL 0

#define PADDLE 1

#define BALL_FRAMEINDEX 0x0000
#define BALL_NUMFRAMES 0x0001

#define PADDLE_FRAMEINDEX 0x0001
#define PADDLE_NUMFRAMES 0x0002

typedef struct {
    uint16_t frameIndex;
    uint8_t numFrames;
} anim_t;

extern const uint8_t spriteData[SPRITEDATA_NUMPIXELS];
extern const frame_t frameData[FRAMEDATA_NUMFRAMES];
extern const anim_t animData[ANIMDATA_NUMANIM];
extern const anim_t* entityData[ENTITYDATA_NUMENTITIES];
extern const uint16_t entityAnimStartIndex[ENTITYDATA_NUMENTITIES];

#endif
