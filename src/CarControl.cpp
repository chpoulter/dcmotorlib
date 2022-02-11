#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;

#include "DcMotor.h"
DcMotor dcMotor_D(0x60);

void checkAndWrite();


double ___Motor1;
double ___Motor2;

int main()
{
    _uBit.init();
    ___Motor1 = 0;
    ___Motor2 = 0;
    _uBit.display.setDisplayMode(DISPLAY_MODE_GREYSCALE);
    dcMotor_D.init();

    _uBit.rgb.off();
    _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
    while (true) {
        if ( _uBit.buttonA.isPressed() == true ) {
            break;
        }
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    _uBit.sleep(2000);
    _uBit.rgb.setColour(MicroBitColor(255, 255, 51, 255));
    while ( true ) {
        if ( _uBit.buttonA.isPressed() == true ) {
            ___Motor1 += 5;
            ___Motor2 += -5;
            checkAndWrite();
            _uBit.rgb.setColour(MicroBitColor(51, 255, 255, 255));
        } else if ( _uBit.buttonB.isPressed() == true ) {
            ___Motor1 += -5;
            ___Motor2 += 5;
            checkAndWrite();
            _uBit.rgb.setColour(MicroBitColor(0, 0, 153, 255));
        } else if ( _uBit.io.P0.isTouched() == true ) {
            ___Motor1 = 0;
            ___Motor2 = 0;
            checkAndWrite();
            _uBit.rgb.setColour(MicroBitColor(255, 255, 255, 255));
        } else if ( _uBit.io.P12.isTouched() == true ) {
            ___Motor1 += 25;
            ___Motor2 += 25;
            checkAndWrite();
            _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
        } else if ( _uBit.io.P16.isTouched() == true ) {
            ___Motor1 += -25;
            ___Motor2 += -25;
            checkAndWrite();
            _uBit.rgb.setColour(MicroBitColor(102, 0, 204, 255));
        }
        _uBit.sleep(250);
        _uBit.rgb.setColour(MicroBitColor(0, 153, 0, 255));
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }

    dcMotor_D.release();

    release_fiber();
}

void checkAndWrite() {
    ___Motor1 = min(max(___Motor1, -100), 100);
    ___Motor2 = min(max(___Motor2, -100), 100);
    dcMotor_D.setPercent(1, ___Motor1);
    dcMotor_D.setPercent(2, Direction::Stop, 0);
    _uBit.display.clear();
    for (int ___i = 0; ___i < ___Motor1 / ((float) 20); ___i += 1) {
        _uBit.display.image.setPixelValue(0, ___i, (5) * _SET_BRIGHTNESS_MULTIPLIER);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    for (int ___k = 0; ___k < ___Motor1 / ((float) -20); ___k += 1) {
        _uBit.display.image.setPixelValue(1, ___k, (5) * _SET_BRIGHTNESS_MULTIPLIER);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    for (int ___j = 0; ___j < ___Motor2 / ((float) 20); ___j += 1) {
        _uBit.display.image.setPixelValue(4, ___j, (5) * _SET_BRIGHTNESS_MULTIPLIER);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    for (int ___m = 0; ___m < ___Motor2 / ((float) -20); ___m += 1) {
        _uBit.display.image.setPixelValue(3, ___m, (5) * _SET_BRIGHTNESS_MULTIPLIER);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
}
