/*
 * Copyright © 2022 Tim Herreijgers
 * Licensed using the MIT license
 */

#include "test_utils/serial.h"

#include <avr/io.h>
#include <avr/sleep.h>
#include <stdio.h>

namespace NextagEmbeddedPlatform::TestUtils
{

#define BAUD   250000
#define MYUBRR F_CPU / 16 / BAUD - 1

static void usart_init(uint16_t ubrr);
static void usart_putchar(char data);
static int usart_putchar_printf(char var, FILE * stream);

static FILE mystdout = {
    .flags = _FDEV_SETUP_WRITE,
    .put = usart_putchar_printf};

void initTestSerial()
{
    stdout = &mystdout;
    usart_init(MYUBRR);
}

void usart_init(uint16_t ubrr)
{
    // Set baud rate
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    // Set frame format: 8data, 1stop bit
    UCSR0C = (1 << UMSEL00) | (3 << UCSZ00);
}
void usart_putchar(char data)
{
    // Wait for empty transmit buffer
    while (!(UCSR0A & (_BV(UDRE0))))
        ;
    // Start transmission
    UDR0 = data;
}

int usart_putchar_printf(char var, FILE * stream)
{
    // translate \n to \r for br@y++ terminal
    if (var == '\n') usart_putchar('\r');
    usart_putchar(var);
    return 0;
}

} // namespace NextagEmbeddedPlatform::TestUtils