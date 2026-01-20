/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

#include "drivers/uart.h"

#include <stdbool.h>
#include <stdint.h>

const uint32_t roData[ 2] = { 1,2};
uint32_t rwData[ 4] = { 3,4, 5, 6};

uint32_t bssData[ 8];

int main( void )
{
  uart_init();
  uart_writeByte( 'H');
  uart_writeByte( 'e');
  uart_writeByte( 'l');
  uart_writeByte( 'l');
  uart_writeByte( 'o');
  uart_writeByte( '\n');
  return 0;
}
