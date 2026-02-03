// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Definition of Module timer_test.
 **/

#include "timer_test.h"

#include <drivers/timer.h>

void timer_test( UartDevice * uart )
{
  TimerDevice * timer = timer_init( 0, TIMER_MODE_TIMER, TIMER_BITMODE_BITMODE_32BIT, 4 );

  timer_set_compare( timer, 0, 1000000 );

  uart_writeString( uart, "Start Timer\n" );

  timer_start( timer );

  for (;;)
  {
    while ( !(timer_get_event( timer, 0, false )))
    {
      timer_capture( timer, 1);
    }

    timer_get_event( timer, 0, true );
    timer_clear( timer );
    uart_writeString( uart, "Timer Event\n" );
  }
}
