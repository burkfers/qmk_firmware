/* Copyright 2021 Gizmo Engineering
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
<<<<<<< HEAD
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[RGB_MATRIX_LED_COUNT] = {
=======
const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT] = {
>>>>>>> develop
    {0, C1_8, C2_8, C3_8},     //0 led1
    {0, C1_7, C2_7, C3_7},     //1 led2
    {0, C1_6, C2_6, C3_6},     //2 led3
    {0, C1_5, C2_5, C3_5},     //3 led4
    {0, C1_4, C2_4, C3_4},     //4 led5
    {0, C1_3, C2_3, C3_3},     //5 led6
    {0, C1_2, C2_2, C4_3},     //6 led7
    {0, C1_1, C3_2, C4_2},     //7 led7b
    {0, C9_1, C8_1, C7_1},     //8 led8
    {0, C9_2, C8_2, C7_2},     //9 led9
    {0, C9_3, C8_3, C7_3},     //10 led10
    {0, C9_4, C8_4, C7_4},     //11 led11
    {0, C9_5, C8_5, C7_5},     //12 led12
    {0, C9_6, C8_6, C7_6},     //13 led13
    {0, C9_7, C8_7, C6_6},     //14 led14
    {0, C9_8, C7_7, C6_7},     //15 led15
    {0, C1_16, C2_16, C3_16},  //16 led16
    {0, C1_15, C2_15, C3_15},  //17 led17
    {0, C1_14, C2_14, C3_14},  //18 led18
    {0, C1_13, C2_13, C3_13},  //19 led19
    {0, C1_12, C2_12, C3_12},  //20 led20
    {0, C1_11, C2_11, C3_11},  //21 led21
    {0, C1_10, C2_10, C4_11},  //22 led22
    {0, C9_9, C8_9, C7_9},     //23 led23
    {0, C9_10, C8_10, C7_10},  //24 led24 missing on [default]
    {0, C9_11, C8_11, C7_11},  //25 led25 missing on [1x2u, 12x5]
    {0, C9_12, C8_12, C7_12},  //26 led26
    {0, C9_13, C8_13, C7_13},  //27 led27
    {0, C9_14, C8_14, C7_14},  //28 led28
    {0, C9_15, C8_15, C6_14},  //29 led29
    {0, C9_16, C7_15, C6_15},  //30 led30 missing on [default, 1x2u]
    {1, C1_8, C2_8, C3_8},     //31 led31
    {1, C1_7, C2_7, C3_7},     //32 led32
    {1, C1_6, C2_6, C3_6},     //33 led33
    {1, C1_5, C2_5, C3_5},     //34 led34
    {1, C1_4, C2_4, C3_4},     //35 led35 missing on [default, 1x2u]
    {1, C1_3, C2_3, C3_3},     //36 led36 missing on [default, 12x5]
    {1, C1_2, C2_2, C4_3},     //37 led37
    {1, C1_1, C3_2, C4_2},     //38 led37b
    {1, C9_1, C8_1, C7_1},     //39 led38
    {1, C9_2, C8_2, C7_2},     //40 led39
    {1, C9_3, C8_3, C7_3},     //41 led40 missing on [default]
    {1, C9_4, C8_4, C7_4},     //42 led41 missing on [1x2u, 12x5]
    {1, C9_5, C8_5, C7_5},     //43 led42
    {1, C9_6, C8_6, C7_6},     //44 led43
    {1, C9_7, C8_7, C6_6},     //45 led44
    {1, C9_8, C7_7, C6_7},     //46 led45
    {1, C1_16, C2_16, C3_16},  //47 led46
    {1, C1_15, C2_15, C3_15},  //48 led47
    {1, C1_14, C2_14, C3_14},  //49 led48
    {1, C1_13, C2_13, C3_13},  //50 led49
    {1, C1_12, C2_12, C3_12},  //51 led50
    {1, C1_11, C2_11, C3_11},  //52 led51
    {1, C1_10, C2_10, C4_11},  //53 led52
    {1, C1_9, C3_10, C4_10},   //54 led52b
    {1, C9_9, C8_9, C7_9},     //55 led53
    {1, C9_10, C8_10, C7_10},  //56 led54
    {1, C9_11, C8_11, C7_11},  //57 led55
    {1, C9_12, C8_12, C7_12},  //58 led56
    {1, C9_13, C8_13, C7_13},  //59 led57
    {1, C9_14, C8_14, C7_14},  //60 led58
    {1, C9_15, C8_15, C6_14},  //61 led59
    {1, C9_16, C7_15, C6_15},  //62 led60
};

led_config_t g_led_config = { {
    // Key Matrix to LED Index
//   1, 6,  10, 15, 20, 26,     31,     37,  42, 47, 52,  56
    {0, 5,  10, 15, 20, 26,     31,     37,  43, 48, 53,  58},
//   2, 7,  11, 16, 21, 27,     32,     37b, 43, 48, 52b,  57
    {1, 6,  11, 16, 21, 27,     32,     38,  44, 49, 54,  59},
//   3, 7b, 12, 17, 22, 28,     33,     38,  44, 49, 53,  58
    {2, 7,  12, 17, 22, 28,     33,     39,  45, 50, 55,  60},
//   4, 8,  13, 18, 23, 29,     34,     39,  45, 50, 54,  59
    {3, 8,  13, 18, 23, 29,     34,     40,  46, 51, 56,  61},
//   5, 9,  14, 19, 25, NO_LED, NO_LED, 41,  46, 51, 55,  60
    {4, 9,  14, 19, 25, NO_LED, NO_LED, 42,  47, 52, 57,  62},
}, {
    // LED Index to Physical Position
    {0, 0}, // 0
    {0, 16}, // 1
    {0, 32}, // 2
    {0, 48}, // 3
    {0, 64}, // 4

    {21, 0}, // 5
    {21, 16}, // 6
    {21, 32}, // 7
    {21, 48}, // 8
    {21, 64}, // 9

    {41, 0}, // 10
    {41, 16}, // 11
    {41, 32}, // 12
    {41, 48}, // 13
    {41, 64}, // 14

    {61, 0}, // 15
    {61, 16}, // 16
    {61, 32}, // 17
    {61, 48}, // 18
    {61, 64}, // 19

    {82, 0}, // 20
    {82, 16}, // 21
    {82, 32}, // 22
    {82, 48}, // 23
    {82, 64}, // 24
    {92, 64}, // 25

    {102, 0}, // 26
    {102, 16}, // 27
    {102, 32}, // 28
    {102, 48}, // 29
    {102, 64}, // 30

    {122, 0}, // 31
    {122, 16}, // 32
    {122, 32}, // 33
    {122, 48}, // 34
    {122, 64}, // 35
    {112, 64}, // 36

    {142, 0}, // 37
    {142, 16}, // 38
    {142, 32}, // 39
    {142, 48}, // 40
    {142, 64}, // 41
    {132, 64}, // 42

    {163, 0}, // 43
    {163, 16}, // 44
    {163, 32}, // 45
    {163, 48}, // 46
    {163, 64}, // 47

    {183, 0}, // 48
    {183, 16}, // 49
    {183, 32}, // 50
    {183, 48}, // 51
    {183, 64}, // 52

    {203, 0}, // 53
    {203, 16}, // 54
    {203, 32}, // 55
    {203, 48}, // 56
    {203, 64}, // 57

    {224, 0}, // 58
    {224, 16}, // 59
    {224, 32}, // 60
    {224, 48}, // 61
    {224, 64}, // 62
}, {
    // LED Index to Flag
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04,
    0x04, 0x04, 0x04
} };
#endif
