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
 * atanTable.h/c: this file is (mostly) generated automatically by the uChip Game MapEditor.
 */
#include "atanTable.h"
#include <stdint.h>
const int16_t approxAtanTable[NUMBER_OF_ATAN_ENTRIES] =
{

	0x8000, 0x80A4, 0x8149, 0x81EF, 0x8297, 0x833F, 0x83EA, 0x8495, 0x8542, 0x85F0, 0x86A0, 0x8750, 0x8803, 0x88B6, 0x896B, 0x8A22,
	0x8ADA, 0x8B93, 0x8C4E, 0x8D0A, 0x8DC8, 0x8E87, 0x8F48, 0x900A, 0x90CD, 0x9192, 0x9259, 0x9321, 0x93EB, 0x94B6, 0x9583, 0x9651,
	0x9721, 0x97F2, 0x98C5, 0x999A, 0x9A70, 0x9B47, 0x9C21, 0x9CFC, 0x9DD8, 0x9EB6, 0x9F96, 0xA077, 0xA15A, 0xA23F, 0xA325, 0xA40D,
	0xA4F7, 0xA5E2, 0xA6CF, 0xA7BD, 0xA8AE, 0xA99F, 0xAA93, 0xAB88, 0xAC7F, 0xAD77, 0xAE71, 0xAF6D, 0xB06A, 0xB169, 0xB26A, 0xB36C,
	0xB470, 0xB576, 0xB67D, 0xB786, 0xB890, 0xB99C, 0xBAAA, 0xBBB9, 0xBCCA, 0xBDDC, 0xBEF0, 0xC006, 0xC11D, 0xC235, 0xC34F, 0xC46B,
	0xC588, 0xC6A7, 0xC7C6, 0xC8E8, 0xCA0B, 0xCB2F, 0xCC54, 0xCD7B, 0xCEA4, 0xCFCD, 0xD0F8, 0xD224, 0xD352, 0xD480, 0xD5B0, 0xD6E1,
	0xD814, 0xD947, 0xDA7B, 0xDBB1, 0xDCE7, 0xDE1F, 0xDF58, 0xE091, 0xE1CC, 0xE307, 0xE443, 0xE580, 0xE6BE, 0xE7FC, 0xE93C, 0xEA7C,
	0xEBBC, 0xECFD, 0xEE3F, 0xEF82, 0xF0C5, 0xF208, 0xF34C, 0xF490, 0xF5D4, 0xF719, 0xF85E, 0xF9A4, 0xFAE9, 0xFC2F, 0xFD75, 0xFEBB,
	0x0000, 0x0145, 0x028B, 0x03D1, 0x0517, 0x065C, 0x07A2, 0x08E7, 0x0A2C, 0x0B70, 0x0CB4, 0x0DF8, 0x0F3B, 0x107E, 0x11C1, 0x1303,
	0x1444, 0x1584, 0x16C4, 0x1804, 0x1942, 0x1A80, 0x1BBD, 0x1CF9, 0x1E34, 0x1F6F, 0x20A8, 0x21E1, 0x2319, 0x244F, 0x2585, 0x26B9,
	0x27EC, 0x291F, 0x2A50, 0x2B80, 0x2CAE, 0x2DDC, 0x2F08, 0x3033, 0x315C, 0x3285, 0x33AC, 0x34D1, 0x35F5, 0x3718, 0x383A, 0x3959,
	0x3A78, 0x3B95, 0x3CB1, 0x3DCB, 0x3EE3, 0x3FFA, 0x4110, 0x4224, 0x4336, 0x4447, 0x4556, 0x4664, 0x4770, 0x487A, 0x4983, 0x4A8A,
	0x4B90, 0x4C94, 0x4D96, 0x4E97, 0x4F96, 0x5093, 0x518F, 0x5289, 0x5381, 0x5478, 0x556D, 0x5661, 0x5752, 0x5843, 0x5931, 0x5A1E,
	0x5B09, 0x5BF3, 0x5CDB, 0x5DC1, 0x5EA6, 0x5F89, 0x606A, 0x614A, 0x6228, 0x6304, 0x63DF, 0x64B9, 0x6590, 0x6666, 0x673B, 0x680E,
	0x68DF, 0x69AF, 0x6A7D, 0x6B4A, 0x6C15, 0x6CDF, 0x6DA7, 0x6E6E, 0x6F33, 0x6FF6, 0x70B8, 0x7179, 0x7238, 0x72F6, 0x73B2, 0x746D,
	0x7526, 0x75DE, 0x7695, 0x774A, 0x77FD, 0x78B0, 0x7960, 0x7A10, 0x7ABE, 0x7B6B, 0x7C16, 0x7CC1, 0x7D69, 0x7E11, 0x7EB7, 0x7F5C
};