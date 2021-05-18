#include "input.h"

void clearInput(input_t *input) {
    input->flags = 0;
}

void checkInput(input_t *input) {
    do {
        if (usbHidBootKeyboardIsInstalled()) {
            usbKeyboardPoll();
        }
        if (usbHidGenericGamepadIsInstalled()) {
            usbHidGenericGamepadPoll();
        }
        usbHostTask();
    } while (getCurrentScanLineNumber() < 523);

    clearInput(input);

    if (usbHidBootKeyboardIsInstalled()) {
        uint8_t modifiers = 0;
        uint8_t keyBuffer[6];
        memset(keyBuffer, 0, sizeof(keyBuffer));
        usbGetCurrentKeyboardState(keyBuffer, &modifiers);
        // Modifier bits (0->7): lctrl, lshift, lalt, lwindows, rcltr, rshift, ralt, rwindows
        for (uint8_t i = 0; i < sizeof(keyBuffer); i++) {
            handleKey(keyBuffer[i], input);
        }
    }

    if (usbHidGenericGamepadIsInstalled()) {
        gamePadState_t gps;
        getCurrentGamepadState(&gps);
        handleGamepad(gps, input);
    }
}

void handleKey(uint8_t code, input_t *input) {
    if (code == 0) return;
    if (code == USB_KEY_W || code == USB_KEY_UP) input->flags |= INPUT_UP_MASK;
    if (code == USB_KEY_D || code == USB_KEY_RIGHT) input->flags |= INPUT_RIGHT_MASK;
    if (code == USB_KEY_S || code == USB_KEY_DOWN) input->flags |= INPUT_DOWN_MASK;
    if (code == USB_KEY_A || code == USB_KEY_LEFT) input->flags |= INPUT_LEFT_MASK;
}

void handleGamepad(gamePadState_t gps, input_t *input) {
    if (gps.axes[1] == gps.XYZRxMinimum) input->flags |= INPUT_UP_MASK;
    else if (gps.axes[1] == gps.XYZRxMaximum) input->flags |= INPUT_DOWN_MASK;
    if (gps.axes[0] == gps.XYZRxMinimum) input->flags |= INPUT_LEFT_MASK;
    else if (gps.axes[0] == gps.XYZRxMinimum) input->flags |= INPUT_RIGHT_MASK;
}

uint8_t checkInputFlag(input_t input, uint8_t flag) {
    return (input.flags & (1 << flag)) != 0;
}
uint8_t checkInputFlags(input_t input, uint8_t mask) {
    return (input.flags & mask) != 0;
}
