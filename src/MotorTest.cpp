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


double ___a;
double ___b;

int main()
{
    _uBit.init();
    ___a = 0;
    ___b = 0;

    dcMotor.init();
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
            dcMotor.set(Motor::M1, ___a);
            _uBit.rgb.setColour(MicroBitColor(51, 102, 255, 255));
        } else if ( _uBit.buttonB.isPressed() == true ) {
            ___b = ___b + 25;
            dcMotor.set(Motor::M2, ___b);
            _uBit.rgb.setColour(MicroBitColor(204, 51, 204, 255));
        } else if ( _uBit.io.P0.isTouched() == true ) {
            ___a = 0;
            ___b = 0;
            dcMotor.set(Motor::M1, ___a);
            dcMotor.set(Motor::M2, ___b);
            _uBit.rgb.setColour(MicroBitColor(255, 255, 255, 255));
        } else if ( _uBit.io.P12.isTouched() == true ) {
            ___a = ___a - 25;
            dcMotor.set(Motor::M1, ___a);
            _uBit.rgb.setColour(MicroBitColor(204, 0, 0, 255));
        } else if ( _uBit.io.P16.isTouched() == true ) {
            ___b = ___b - 25;
            dcMotor.set(Motor::M2, ___b);
            _uBit.rgb.setColour(MicroBitColor(255, 102, 0, 255));
        }
        _uBit.sleep(1000);
        _uBit.rgb.setColour(MicroBitColor(0, 153, 0, 255));
        _uBit.sleep(_ITERATION_SLEEP_TIMEOUT);
    }
    dcMotor.release();
    release_fiber();
}
