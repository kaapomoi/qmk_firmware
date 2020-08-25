/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#ifdef OLED_DRIVER_ENABLE
  #define OLED_DISPLAY_128X64
  #define OLED_FONT_END 127
#endif

#ifdef RGBLIGHT_ENABLE
  #define RGBLED_NUM 20
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8  
  #define RGBLIGHT_LED_MAP {0,1,2,9,8,7,4,3,5,6,19,18,17,10,11,12,15,16,14,13} // Orients Kyria LEDs to a circle around both halves.
#endif

#ifdef ENCODER_ENABLE
  // EC11K encoders have a different resolution than other EC11 encoders.
  // When using the default resolution of 4, if you notice your encoder skipping
  // every other tick, lower the resolution to 2.
  #define ENCODER_RESOLUTION 2
#endif

#define PERMISSIVE_HOLD
#define TAPPING_TERM 222

#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define NO_ACTION_ONESHOT
  