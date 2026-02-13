#include <stdio.h>
#include <string.h>
#include "action_layer.h"
#include "keyboard.h"
#include "modifiers.h"
#include "oled_driver.h"
#include "progmem.h"
#include "quantum.h"
#include "wpm.h"

#include QMK_KEYBOARD_H


#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // if (!is_keyboard_master()) {
    //     return OLED_ROTATION_180;
    // }

    oled_clear();

    return rotation;
}

const void* default_layer_switch(const void* win, const void* mac, const void* gam) {
    switch (get_highest_layer(default_layer_state)) {
        case WIN_LAYER:
            return win;
        case MAC_LAYER:
            return mac;
        case GAMING_LAYER:
            return gam;
        default:
            return "";
    }
}



void print_wpm(void) {
    if(is_keyboard_master()) {
        oled_write_P(PSTR("WPM\n"), false);
        char wpm_str[4];
        sprintf(wpm_str, "%d", get_current_wpm());
        oled_write(wpm_str, false);

        oled_write(PSTR("\n\n"), false);
    }
}

bool left_display(void) {
    print_wpm();

    uint8_t modifiers = get_mods();
    oled_write_P(PSTR("SHIFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("CTRL\n"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("ALT\n"), (modifiers & MOD_MASK_ALT));
    oled_write_P(default_layer_switch(PSTR("WIN\n"), PSTR("CMD\n"), PSTR("")), (modifiers & MOD_MASK_GUI));

    return false;
}

bool right_display(void) {
    print_wpm();

    oled_write_P("LAYER", false);
    if (get_highest_layer(layer_state) < N_LAYER) {
        oled_write(PSTR("0"), false);
    } else {
        char layer_str[4];
        sprintf(layer_str, "%d", get_highest_layer(layer_state) - (N_LAYER - 1));
        oled_write(layer_str, false);
    }
    oled_write_P("\n", false);

    return false;
}

bool oled_task_user(void) {
    oled_clear();

    oled_write_P(default_layer_switch(PSTR("WIN\n"), PSTR("MAC\n"), PSTR("GAME\n")), false);
    oled_write_P(PSTR("\n\n"), false);

    return is_keyboard_left() ? left_display() : right_display();
}


#endif
