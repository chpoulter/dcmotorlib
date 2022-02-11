#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;

#include "DcMotor.h"
DcMotor dcMotor_D(0x60);


double ___a;
double ___b;

int main()
{
    _uBit.init();
    ___a = 0;
    ___b = 0;

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
            ___a = ___a + 25;
            dcMotor_D.setPercent(1, ___a);
            _uBit.rgb.setColour(MicroBitColor(51, 102, 255, 255));
        } else if ( _uBit.buttonB.isPressed() == true ) {
            ___b = ___b + 25;
            dcMotor_D.setPercent(2, ___b);
            _uBit.rgb.setColour(MicroBitColor(204, 51, 204, 255));
        } else if ( _uBit.io.P0.isTouched() == true ) {
            ___a = 0;
            ___b = 0;
            dcMotor_D.setPercent(1, Direction::Stop, 0);
            dcMotor_D.setPercent(2, Direction::Stop, 0);
            _uBit.rgb.setColour(MicroBitColor(255, 255, 255, 255));
        } else if ( _uBit.io.P12.isTouched() == true ) {
            ___a = ___a - 25;
            dcMotor_D.setPercent(1, ___a);
            _uBit.rgb.setColour(MicroBitColor(204, 0, 0, 255));
        } else if ( _uBit.io.P16.isTouched() == true ) {
            ___b = ___b - 25;
            dcMotor_D.setPercent(2, ___b);
            _uBit.rgb.setColour(MicroBitColor(255, 102, 0, 255));
        }
        _uBit.sleep(250);
        _uBit.rgb.setColour(MicroBitColor(0, 153, 0, 255));
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }

    dcMotor_D.release();

    release_fiber();
}
