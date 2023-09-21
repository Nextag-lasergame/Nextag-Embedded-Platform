/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "NextagEmbeddedPlatform/drivers/serial.h"

int main()
{
    using namespace NextagEmbeddedPlatform;

    auto & serial = Drivers::Serial::serial;

    uint8_t data[] = {'H', 'e', 'l', 'l', 'o', ' ', 'w', 'o', 'r', 'l', 'd', '!'};

    serial.begin(9600);

    for (uint8_t i = 0; i < 12; i++)
    {
        serial.sendByte(data[i]);
    }
}
