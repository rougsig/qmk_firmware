// !!! DO NOT ADD #pragma once !!! //
RGB_MATRIX_EFFECT(per_key)

#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#include "../../../rev1/legacy/legacy.h"

#define MODS_SHIFT (get_mods() & MOD_BIT(KC_LSHIFT) || get_mods() & MOD_BIT(KC_RSHIFT))
#define MODS_CTRL (get_mods() & MOD_BIT(KC_LCTL) || get_mods() & MOD_BIT(KC_RCTRL))
#define MODS_ALT (get_mods() & MOD_BIT(KC_LALT) || get_mods() & MOD_BIT(KC_RALT))

static uint8_t layout_key_layout[54] = {
    1,  2,  3,  4,  5,  6,
    51, 42, 30, 18,
    17, 29, 41, 50, 49,
    40, 28, 16,
    15, 27, 39,
    38, 26, 14,
    13, 25, 37,

    7,  8,  9,  10, 11, 12,
    52, 43, 31, 19,
    20, 32, 44, 53, 54,
    45, 33, 21,
    22, 34, 46,
    47, 35, 23,
    24, 36, 48
};

static Color layout_key_color[3][54] = {
    {
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            blue,    blue,    blue,    blue,     blue,   blue,                        blue,    blue,   blue,   blue,   blue,   blue,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            orange1, magenta1, white,   green,    red,    yellow,                       yellow,    red,   green,   white,   magenta1,   orange1,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            orange1, magenta1, white,   green,    red,    yellow,                       yellow,    red,   green,   white,   magenta1,   orange1,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            orange1, magenta1, white,   green,    red,    yellow,                       yellow,    red,   green,   white,   magenta1,   orange1,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                 red,    red,     yellow,      yellow,   red,    red
                                            //`--------------------------'  `--------------------------'
    },
    {
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                  white,   white,  white,      white,   white,    white
                                            //`--------------------------'  `--------------------------'
    },
    {
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                  white,   white,  white,      white,   white,    white
                                            //`--------------------------'  `--------------------------'
    }
};

static bool per_key(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        Color c = layout_key_color[0][layout_key_layout[i + (is_master ? 0 : 27)] - 1];
        float v = rgb_matrix_config.hsv.v / 255.0 * (float) RGB_MATRIX_MAXIMUM_BRIGHTNESS / 255.0;
        rgb_matrix_set_color(
            i,
            (uint8_t) c.r * v,
            (uint8_t) c.g * v,
            (uint8_t) c.b * v
        );
    }
    return led_max < DRIVER_LED_TOTAL;
}

#endif  // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
