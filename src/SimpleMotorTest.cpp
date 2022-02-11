#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;

#include "DcMotor.h"
DcMotor dcMotor_D(0x60);



double ___speed;
double ___oldspeed;

int main()
{
    _uBit.init();
    ___speed = 0;
    ___oldspeed = -1;

    dcMotor_D.init();

    _uBit.display.clear();
    _uBit.rgb.setColour(MicroBitColor(0, 153, 0, 255));
    while ( true ) {
        if ( _uBit.buttonA.isPressed() ) {
            ___speed = ___speed + 10;
        }
        if ( _uBit.buttonB.isPressed() ) {
            ___speed = ___speed - 10;
        }
        if ( ___speed < 0 ) {
            ___speed = 100;
        }
        if ( ___speed > 100 ) {
            ___speed = 0;
        }
        if ( !( ___speed == ___oldspeed ) ) {
            _uBit.rgb.setColour(MicroBitColor(255, 0, 0, 255));
            ___oldspeed = ___speed;
            _uBit.display.scroll(ManagedString(round(___speed / ((float) 10))));
            dcMotor_D.setPercent(1, ___speed);
            _uBit.rgb.setColour(MicroBitColor(0, 153, 0, 255));
        }
        _uBit.sleep(500);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }

    dcMotor_D.release();

    release_fiber();
}

