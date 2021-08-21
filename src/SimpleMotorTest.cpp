/*
 * DC Motor Lib
 *
 * Copyright (C) 2021 Christian Poulter
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#define _GNU_SOURCE

#include "MicroBit.h"
#include "NEPODefs.h"
#include <list>
#include <array>
#include <stdlib.h>
MicroBit _uBit;
#include "DcMotor.h"
DcMotor dcMotor;

double ___speed;
double ___oldspeed;

int main()
{
    _uBit.init();
    ___speed = 0;
    ___oldspeed = -1;

    dcMotor.init();
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
            dcMotor.set(Motor::M1, ___speed);
            _uBit.rgb.setColour(MicroBitColor(0, 153, 0, 255));
        }
        _uBit.sleep(500);
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    dcMotor.release();
    release_fiber();
}
