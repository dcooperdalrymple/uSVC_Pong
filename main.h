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
#ifndef MAIN_H_
#define MAIN_H_

#include "usvc_kernel/usvc_kernel.h"

#include "tileset.h"
#include "tilemap.h"
#include "common.h"

#include "input.h"
#include "playfield.h"
#include "paddle.h"
#include "ball.h"

void initObjects();
void initTiles();

#endif /* MAIN_H_ */
