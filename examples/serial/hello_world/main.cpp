/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/serial.h"

#include <util/delay.h>

int main()
{
    using namespace NextagEmbeddedPlatform;

    auto & serial = Drivers::Serial::serial;

    serial.begin(9600);

    serial.println("Hello world");

    for (;;)
    {
    }
}
