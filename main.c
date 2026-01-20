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

int main( void )
{
  uart_init();
  rng_init();

  uart_writeByte( 'H');
  uart_writeByte( 'e');
  uart_writeByte( 'l');
  uart_writeByte( 'l');
  uart_writeByte( 'o');
  uart_writeByte( '\n');

  uart_writeString( "Hello World\n" );

  uart_writeString( "NULL: " );
  uart_writeNumber( 0 );
  uart_writeByte( '\n');

  uart_writeString( "The Answer to the Ultimate Question of Life, the Universe, and Everything: " );
  uart_writeNumber( 42 );
  uart_writeByte( '\n');

  uart_writeString( "Max uint32_t: " );
  uart_writeNumber( UINT32_MAX );
  uart_writeByte( '\n');

  for ( uint32_t i = 0; i < 10; ++i)
  {
    uart_writeString( "Random Value " );
    uart_writeNumber( i );
    uart_writeString( ": " );
    uart_writeNumber( rng_getRandomValue() );
    uart_writeByte( '\n');
  }

  extern void SysTick_init( void );
  SysTick_init();

  return 0;
}

void print_rng( void )
{
  uart_writeString( "Random Value: " );
  uart_writeNumber( rng_getRandomValue() );
  uart_writeByte( '\n');
}
