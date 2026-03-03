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

#include "egu_test.h"

#include <drivers/EventGeneratorUnit.h>

#include <stddef.h>

static void handler_egu0_0( void );

static void handler_egu2_1( void );

UartDevice * uartg = NULL;

void egu_test_init( UartDevice * uart )
{
  uartg = uart;

  EGUnit_init( EGU0 );
  EGUnit_init( EGU2 );

  EGUnit_registerHandler( EGU0, 0, handler_egu0_0 );
  EGUnit_registerHandler( EGU2, 1, handler_egu2_1 );
}

void egu_test_trigger( void )
{
  EGUnit_trigger( EGU0, 0 );
}

static void handler_egu0_0( void )
{
  uart_writeString( uartg, "EGU 0 Event 0\n" );
  EGUnit_trigger( EGU2, 1 );
}

static void handler_egu2_1( void )
{
  uart_writeString( uartg, "EGU 2 Event 1\n" );
}
