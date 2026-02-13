#include <stdio.h>
#include "action_layer.h"
#include "modifiers.h"
#include "oled_driver.h"
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

char* default_layer_switch(char* win, char* mac) {
    switch (get_highest_layer(default_layer_state)) {
        case 0:
            return win;
        case 1:
            return mac;
        default:
            return "";
    }
}

bool left_display(void) {

    uint8_t modifiers = get_mods();
    oled_write_P(PSTR("SHIFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("CTRL\n"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("ALT\n"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(default_layer_switch("WIN\n", "CMD\n")), (modifiers & MOD_MASK_GUI));
    return false;
}

bool right_display(void) {

    oled_write_P(PSTR(" WPM\n "), false);
    oled_write(get_u8_str(get_current_wpm(), '0'), false);

    oled_write(PSTR("\n\n"), false);

    return false;
}

bool oled_task_user(void) {
    oled_clear();

    oled_write_P(PSTR(default_layer_switch(" WIN", " MAC")), false);
    oled_write_P(PSTR("\n\n"), false);

    return is_keyboard_left() ? left_display() : right_display();
}


#endif
