/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

#include <drivers/uart.h>
#include <drivers/random.h>

#include <stdbool.h>
#include <stdint.h>

const uint32_t roData[ 2] = { 1,2};
uint32_t rwData[ 4] = { 3,4, 5, 6};

uint32_t bssData[ 8];

UartDevice * uart1;
UartDevice * uart2;

int main( void )
{
  uart1 = uart_init();
  //uart2 = uart_init();

  rng_init();

  uart_writeByte( uart1, 'H');
  uart_writeByte( uart1, 'e');
  uart_writeByte( uart1, 'l');
  uart_writeByte( uart1, 'l');
  uart_writeByte( uart1, 'o');
  uart_writeByte( uart1, '\n');

  uart_writeString( uart1, "Hello World\n" );

  uart_writeString( uart1, "NULL: " );
  uart_writeNumber( uart1, 0 );
  uart_writeByte( uart1, '\n');

  uart_writeString( uart1, "The Answer to the Ultimate Question of Life, the Universe, and Everything: " );
  uart_writeNumber( uart1, 42 );
  uart_writeByte( uart1, '\n');

  uart_writeString( uart1, "Max uint32_t: " );
  uart_writeNumber( uart1, UINT32_MAX );
  uart_writeByte( uart1, '\n');

  for ( uint32_t i = 0; i < 10; ++i)
  {
    uart_writeString( uart1, "Random Value " );
    uart_writeNumber( uart1, i );
    uart_writeString( uart1, ": " );
    uart_writeNumber( uart1, rng_getRandomValue() );
    uart_writeByte( uart1, '\n');
  }

  extern void SysTick_init( void );
  SysTick_init();

  return 0;
}

void print_rng( void )
{
  uart_writeString( uart2, "Random Value: " );
  uart_writeNumber( uart2, rng_getRandomValue() );
  uart_writeByte( uart2, '\n');
}
