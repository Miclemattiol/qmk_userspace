#include <stdio.h>
#include "action_layer.h"
#include "keyboard.h"
#include "modifiers.h"
#include "oled_driver.h"
#include "progmem.h"
#include "quantum.h"
#include "wpm.h"

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
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
    oled_write_P(PSTR("WPM\n"), false);
    oled_write(get_u8_str(get_current_wpm(), ' '), false);
    oled_write_P(PSTR("\n\n"), false);
}

void left_display(void) {
    uint8_t modifiers = get_mods();
    oled_write_P(PSTR("SHIFT"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR("CTRL\n"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR("ALT\n"), (modifiers & MOD_MASK_ALT));
    oled_write_P(default_layer_switch(PSTR("WIN\n"), PSTR("CMD\n"), PSTR("")), (modifiers & MOD_MASK_GUI));
}

void right_display(void) {
    print_wpm();

    oled_write_P(PSTR("LAYER"), false);
    if (get_highest_layer(layer_state) < N_LAYER) {
        oled_write_P(PSTR("0"), false);
    } else {
        char layer_str[4];
        sprintf(layer_str, "%d", get_highest_layer(layer_state) - (N_LAYER - 1));
        oled_write(layer_str, false);
    }
    oled_write_P(PSTR("\n"), false);
}

bool oled_task_user(void) {
    // Gestione manuale del timeout
    if (last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return false;
    }

    oled_on();
    oled_clear();

    oled_write_P(default_layer_switch(PSTR("WIN\n"), PSTR("MAC\n"), PSTR("GAME\n")), false);
    oled_write_P(PSTR("\n\n"), false);

    if (is_keyboard_left()) {
        left_display();
    } else {
        right_display();
    }

    return false;
}


#endif
