#include QMK_KEYBOARD_H


#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case 1:
                oled_write_P(PSTR("Symbols\n"), false);
                break;
            case 2:
                oled_write_P(PSTR("Numbers\n"), false);
                break;
            case 3:
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
    } else {
        // Display secondario (lato destro)
        oled_write_P(PSTR("Lily58\n"), false);
        oled_write_P(PSTR("Aurora\n"), false);
    }

    return true;
}


#endif
