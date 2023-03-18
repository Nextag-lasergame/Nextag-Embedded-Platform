//#include <avr/io.h>
//#include <stdio.h>
//#include <avr/sleep.h>
//
//#include <unity.h>
//
//#define BAUD 250000
//#define MYUBRR F_CPU/16/BAUD-1
//
//void usart_init(uint16_t ubrr);
//void usart_putchar( char data );
//int usart_putchar_printf(char var, FILE *stream);
//
//static FILE mystdout = {
//    .flags = _FDEV_SETUP_WRITE,
//    .put = usart_putchar_printf
//};
//
//void setUp()
//{
//}
//
//void tearDown()
//{
//}
//
//void testFunction()
//{
//    TEST_ASSERT_EQUAL_INT(1, 1);
//}
//
//int main( void ) {
//    // setup our stdio stream
//    stdout = &mystdout;
//
//    // fire up the usart
//    usart_init ( MYUBRR );
//
//    UNITY_BEGIN();
//    RUN_TEST(testFunction);
//    UNITY_END();
//
//    sleep_cpu();
//}
//
//void usart_init( uint16_t ubrr) {
//    // Set baud rate
//    UBRR0H = (uint8_t)(ubrr>>8);
//    UBRR0L = (uint8_t)ubrr;
//    // Enable receiver and transmitter
//    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
//    // Set frame format: 8data, 1stop bit
//    UCSR0C = (1<<UMSEL00)|(3<<UCSZ00);
//}
//void usart_putchar(char data) {
//    // Wait for empty transmit buffer
//    while ( !(UCSR0A & (_BV(UDRE0))) );
//    // Start transmission
//    UDR0 = data;
//}
//
//int usart_putchar_printf(char var, FILE *stream) {
//    // translate \n to \r for br@y++ terminal
//    if (var == '\n') usart_putchar('\r');
//    usart_putchar(var);
//    return 0;
//}

#include <avr/io.h>

int main()
{
   DDRB = 0xFF;
}