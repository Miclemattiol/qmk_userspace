#include "keyboard.h"
#include "quantum.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case DF(WIN_LAYER):
        if (record->event.pressed) {
            set_single_persistent_default_layer(WIN_LAYER);
        }
        return false;

    case DF(MAC_LAYER):
        if (record->event.pressed) {
            set_single_persistent_default_layer(MAC_LAYER);
        }
        return false;

    case DF(GAMING_LAYER):
        if (record->event.pressed) {
            set_single_persistent_default_layer(GAMING_LAYER);
        }
        return false;

    }
    return true;
}
