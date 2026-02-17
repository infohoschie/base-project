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
  TimerDevice * timer0 = timer_init( 0, TIMER_MODE_TIMER, TIMER_BITMODE_BITMODE_32BIT, 4 );
  TimerDevice * timer1 = timer_init( 1, TIMER_MODE_COUNT, TIMER_BITMODE_BITMODE_32BIT, 0 );

  timer_set_compare( timer0, 0, 1000000 );
  timer_set_clear_shortcut( timer0, 0, true ); // SHORTS not supported

  uart_writeString( uart, "Start Timer\n" );

  timer_start( timer0 );
  timer_start( timer1 );
  for (;;)
  {
    while ( !(timer_get_event( timer0, 0, false )))
    {
      timer_capture( timer0, 1);
    }


    timer_get_event( timer0, 0, true );
    timer_clear( timer0 );
    timer_trigger( timer1 );
    timer_capture( timer1, 0);
    uart_writeString( uart, "Timer Event " );
    uart_writeNumber( uart, timer_get_counter( timer1, 0 ) );
    uart_writeString( uart, "\n" );
  }
}
