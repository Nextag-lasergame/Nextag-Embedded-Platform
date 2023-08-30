/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/serial.h"

#include <util/delay.h>

int main()
{
    using namespace NextagEmbeddedPlatform;

    Drivers::Serial serial{};

    serial.begin(9600);

<<<<<<< Updated upstream
    for(;;)
=======
    serial.println("Hello world");

    for (;;)
>>>>>>> Stashed changes
    {
    }
}
