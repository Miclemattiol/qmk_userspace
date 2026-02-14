#include "gpio.h"

void keyboard_pre_init_user(void) {
    // Set our LED pin as output
    gpio_set_pin_output(24);
    // Turn the LED off (high is off, low is on)
    gpio_write_pin_high(24);
}
