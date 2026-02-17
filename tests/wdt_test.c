// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author infohoschie
 *
 * @brief @todo Add brief description.
 **/

#include "wdt_test.h"

#include <drivers/Wdt.h>

static UartDevice * intUart;

void Interrupt16_Handler( void );

void Interrupt16_Handler( void )
{
  uart_writeString( intUart, "Last Will\n" );
}

void Wdt_test( UartDevice * const uart )
{
  intUart = uart;
  Wdt_initialise( 100000, true, 2 );

  uart_writeString( uart, "WDT Test\n" );

  Wdt_start();

  for ( ;; )
  {
    for ( char readChar = 0; readChar == 0; readChar = uart_readByte( uart ) )
    {
      ;
    }

    uart_writeString( uart, "WDT Trigger\n" );

    Wdt_reloadRequest( 0 );
    Wdt_reloadRequest( 1 );
  }
}
