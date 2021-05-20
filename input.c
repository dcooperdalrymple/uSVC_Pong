#include "input.h"

void clearInput(input_t *input) {
    input->prevFlags = input->flags;
    input->flags = 0;
}

void clearControls(controls_t *controls) {
    clearInput(&controls->player);
    clearInput(&controls->opponent);
}

void checkInput(controls_t *controls) {
    do {
        if (usbHidBootKeyboardIsInstalled()) {
            usbKeyboardPoll();
        }
        if (usbHidGenericGamepadIsInstalled()) {
            usbHidGenericGamepadPoll();
        }
        usbHostTask();
    } while (getCurrentScanLineNumber() < 523);

    clearControls(controls);

    if (usbHidBootKeyboardIsInstalled()) {
        uint8_t modifiers = 0;
        uint8_t keyBuffer[6];
        memset(keyBuffer, 0, sizeof(keyBuffer));
        usbGetCurrentKeyboardState(keyBuffer, &modifiers);
        // Modifier bits (0->7): lctrl, lshift, lalt, lwindows, rcltr, rshift, ralt, rwindows
        for (uint8_t i = 0; i < sizeof(keyBuffer); i++) {
            handleKey(keyBuffer[i], controls);
        }
    }

    if (usbHidGenericGamepadIsInstalled()) {
        gamePadState_t gps;
        getCurrentGamepadState(&gps);
        handleGamepad(gps, controls);
    }
}

void handleKey(uint8_t code, controls_t *controls) {
    if (code == 0) return;

    // Player
    if (code == USB_KEY_W) controls->player.flags |= INPUT_UP_MASK;
    if (code == USB_KEY_D) controls->player.flags |= INPUT_RIGHT_MASK;
    if (code == USB_KEY_S) controls->player.flags |= INPUT_DOWN_MASK;
    if (code == USB_KEY_A) controls->player.flags |= INPUT_LEFT_MASK;
    if (code == USB_KEY_SPACE) controls->player.flags |= INPUT_START_MASK;

    // Opponent
    if (code == USB_KEY_UP) controls->opponent.flags |= INPUT_UP_MASK;
    if (code == USB_KEY_RIGHT) controls->opponent.flags |= INPUT_RIGHT_MASK;
    if (code == USB_KEY_DOWN) controls->opponent.flags |= INPUT_DOWN_MASK;
    if (code == USB_KEY_LEFT) controls->opponent.flags |= INPUT_LEFT_MASK;
    if (code == USB_KEY_ENTER) controls->opponent.flags |= INPUT_START_MASK;
}

void handleGamepad(gamePadState_t gps, controls_t *controls) {
    if (gps.axes[1] == gps.XYZRxMinimum) controls->player.flags |= INPUT_UP_MASK;
    else if (gps.axes[1] == gps.XYZRxMaximum) controls->player.flags |= INPUT_DOWN_MASK;
    if (gps.axes[0] == gps.XYZRxMinimum) controls->player.flags |= INPUT_LEFT_MASK;
    else if (gps.axes[0] == gps.XYZRxMinimum) controls->player.flags |= INPUT_RIGHT_MASK;
}

uint8_t checkInputFlag(input_t input, uint8_t flag) {
    return (input.flags & (1 << flag)) != 0;
}
uint8_t checkInputFlags(input_t input, uint8_t mask) {
    return (input.flags & mask) != 0;
}

uint8_t checkInputPrevFlag(input_t input, uint8_t flag) {
    return (input.prevFlags & (1 << flag)) != 0;
}
uint8_t checkInputPrevFlags(input_t input, uint8_t mask) {
    return (input.prevFlags & mask) != 0;
}

uint8_t checkInputPress(input_t input, uint8_t flag) {
    return checkInputFlag(input, flag) && !checkInputPrevFlag(input, flag);
}
uint8_t checkInputRelease(input_t input, uint8_t flag) {
    return !checkInputFlag(input, flag) && checkInputPrevFlag(input, flag);
}
