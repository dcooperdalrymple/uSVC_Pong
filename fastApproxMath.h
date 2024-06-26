/*
 *  RedBalls (not in the UrbanDictionary definintion!):
 *  A clone of the popular Worms game, runnin on uChip Simple VGA Console
 *  a simple Cortex M0+ console with 32 kB of RAM!
 *
 *  Copyright 2019-2020 Nicola Wrachien (next-hack.com)
 *
 *  This file is part of next-hack's RedBalls.
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
 *
 * fastApproxMath.h/c: this files allows a quick evaluation of atan2 and sqrt
 * with a decent level of precision.
 */
#ifndef FASTAPPROXMATH_H_
#define FASTAPPROXMATH_H_
#include "stdint.h"
#include "atanTable.h"
#include "sqrtTable.h"
typedef struct
{
	int32_t x;
	int32_t y;
} vector_t;
#define FIXED_PI 0x80000000
#define FIXED_MUL(a, b) ( ( ((int64_t) (a)) * ((int64_t) (b)) ) >> 16)		// used to multiply a 16.16 by a 16.16
#define FIXED_MULFRACT(a, b) ( ( ((int64_t) (a) * (int64_t) (b))) >> 15)		// used to multiply a 16.16 by a 1.15

int32_t fastApproxAtan2(int32_t x, int32_t y);
uint32_t fastApproximateSqrt(uint32_t x);

#endif /* FASTAPPROXMATH_H_ */
