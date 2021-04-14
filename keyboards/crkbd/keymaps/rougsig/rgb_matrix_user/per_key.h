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

static Color layout_key_color[4][54] = {
    {
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
            cyan,    cyan,    cyan,    cyan,     cyan,   cyan,                        cyan,    cyan,   cyan,   cyan,   cyan,   cyan,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            green,  cyan, cyan,   cyan,    cyan,    cyan,                               cyan,    cyan,   cyan,   cyan,   cyan,   red,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            blue,   cyan, cyan,   cyan,    cyan,    cyan,                               cyan,    cyan,   cyan,   cyan,   cyan,   green,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
            blue,   cyan, cyan,   cyan,    cyan,    cyan,                               cyan,    cyan,   cyan,   cyan,   cyan,   red,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                 blue,    magenta,     yellow,      yellow,   magenta,    blue
                                            //`--------------------------'  `--------------------------'
    },
    {
        //,-----------------------------------------------------.                    ,-----------------------------------------------------.
             red,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             red,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
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
             green,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             green,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
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
             blue,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             blue,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
             white,    white,   white,   white,   white,   white,                       white,    white,   white,   white,   white,   white,
        //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                                  white,   white,  white,      white,   white,    white
                                            //`--------------------------'  `--------------------------'
    }
};

#define L_BASE 0
#define L_LOWER 2
#define L_RAISE 4
#define L_ADJUST 8

static uint8_t layer_state_layout(void) {
    uint8_t layer = 0;
    switch (layer_state) {
        case L_BASE:
            layer = 0;
            break;
        case L_LOWER:
            layer = 1;
            break;
        case L_RAISE:
            layer = 2;
            break;
        case L_ADJUST:
        case L_ADJUST|L_LOWER:
        case L_ADJUST|L_RAISE:
        case L_ADJUST|L_LOWER|L_RAISE:
            layer = 3;
            break;
    }
    return layer;
}

static bool per_key(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        Color c = layout_key_color[layer_state_layout()][layout_key_layout[i + (is_master ? 0 : 27)] - 1];
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
