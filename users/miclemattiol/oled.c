#include "action_layer.h"
#include "oled_driver.h"
#include QMK_KEYBOARD_H


#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    // if (!is_keyboard_master()) {
    //     return OLED_ROTATION_180;
    // }

    oled_clear();

    return rotation;
}

bool left_display(void) {
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("WIN"), false);
            break;
        case 1:
            oled_write_P(PSTR("MAC"), false);
            break;
    }

    return true;
}

bool right_display(void) {

    // return true;
    switch (get_highest_layer(layer_state)) {
        case 0:
        case 1:
            oled_write_P(PSTR("Base\n"), false);
            break;
        case 2:
            oled_write_P(PSTR("Symbols\n"), false);
            break;
        case 3:
            oled_write_P(PSTR("Numbers\n"), false);
            break;
        case 4:
            oled_write_P(PSTR("RGB\n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef\n"), false);
    }

    uint8_t modifiers = get_mods();
    oled_write_P(PSTR("\nMods: "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));

    return true;
}

bool oled_task_user(void) {
    oled_clear();
    return is_keyboard_left() ? left_display() : right_display();
}


#endif
