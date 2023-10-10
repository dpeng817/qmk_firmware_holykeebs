/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* Select hand configuration */

#define MASTER_RIGHT

#define POINTING_DEVICE_ROTATION_90
#define PIMORONI

#define PIMORONI_TRACKBALL_SCALE 10

//comment that out if your trackball is on the left side
// #define TRACKBALL_RIGHT

#ifdef TRACKBALL_RIGHT 
    #define POINTING_DEVICE_INVERT_X
    #define POINTING_DEVICE_INVERT_Y
#endif


#define SPLIT_OLED_ENABLE
#define OLED_FONT_H "keyboards/crkbd/lib/glcdfont.c"

#define TAPPING_TERM_PER_KEY
