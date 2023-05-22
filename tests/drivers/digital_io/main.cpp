/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include <test_utils/serial.h>

#include <NextagEmbeddedPlatform/drivers/digital_io.h>

#include <avr/sleep.h>
#include <unity.h>

using namespace NextagEmbeddedPlatform::Drivers;

struct pinData
{
    volatile uint8_t & direction;
    volatile uint8_t & pin;
    volatile uint8_t & port;
    uint8_t bit;
    Pins pinEnum;
};

static pinData pins[] =
    {
        {DDRB, PINB, PORTB, 0, Pins::B0},
        {DDRB, PINB, PORTB, 1, Pins::B1},
        {DDRB, PINB, PORTB, 2, Pins::B2},
        {DDRB, PINB, PORTB, 3, Pins::B3},
        {DDRB, PINB, PORTB, 4, Pins::B4},
        {DDRB, PINB, PORTB, 5, Pins::B5},
        {DDRB, PINB, PORTB, 6, Pins::B6},
        {DDRB, PINB, PORTB, 7, Pins::B7},

        {DDRC, PINC, PORTC, 0, Pins::C0},
        {DDRC, PINC, PORTC, 1, Pins::C1},
        {DDRC, PINC, PORTC, 2, Pins::C2},
        {DDRC, PINC, PORTC, 3, Pins::C3},
        {DDRC, PINC, PORTC, 4, Pins::C4},
        {DDRC, PINC, PORTC, 5, Pins::C5},
        {DDRC, PINC, PORTC, 6, Pins::C6},

        {DDRD, PIND, PORTD, 0, Pins::D0},
        {DDRD, PIND, PORTD, 1, Pins::D1},
        {DDRD, PIND, PORTD, 2, Pins::D2},
        {DDRD, PIND, PORTD, 3, Pins::D3},
        {DDRD, PIND, PORTD, 4, Pins::D4},
        {DDRD, PIND, PORTD, 5, Pins::D5},
        {DDRD, PIND, PORTD, 6, Pins::D6},
        {DDRD, PIND, PORTD, 7, Pins::D7},
};

void setUp()
{
    DDRB = 0;
    PORTB = 0;
    PINB = 0;
    DDRC = 0;
    PORTC = 0;
    PINC = 0;
    DDRD = 0;
    PORTD = 0;
    PIND = 0;
}

void tearDown()
{
}

void directionIsSetCorrectly()
{
    for (const auto & pin : pins)
    {
        DigitalIO digitalIo(pin.pinEnum);

        digitalIo.setPinMode(Mode::OUTPUT);
        TEST_ASSERT_BIT_HIGH(pin.bit, pin.direction);

        digitalIo.setPinMode(Mode::INPUT);
        TEST_ASSERT_BIT_LOW(pin.bit, pin.direction);
    }
}

void setStateSetsCorrectButInOutputRegister()
{
    for (const auto & pin : pins)
    {
        DigitalIO digitalIo(pin.pinEnum);

        digitalIo.setState(State::HIGH);
        TEST_ASSERT_BIT_HIGH(pin.bit, pin.port);

        digitalIo.setState(State::LOW);
        TEST_ASSERT_BIT_LOW(pin.bit, pin.port);
    }
}

void getStateGetsCorrectStateFromInputRegister()
{
    for (const auto & pin : pins)
    {
        DigitalIO digitalIo(pin.pinEnum);
        digitalIo.setPinMode(Mode::OUTPUT);

        pin.port = 1 << pin.bit;
        TEST_ASSERT_EQUAL(State::HIGH, digitalIo.getState());

        pin.port = 0;
        TEST_ASSERT_EQUAL(State::LOW, digitalIo.getState());
    }
}

int main()
{
    NextagEmbeddedPlatform::TestUtils::initTestSerial();

    UNITY_BEGIN();
    RUN_TEST(directionIsSetCorrectly);
    RUN_TEST(setStateSetsCorrectButInOutputRegister);
    RUN_TEST(getStateGetsCorrectStateFromInputRegister);
    UNITY_END();

    sleep_cpu();
}