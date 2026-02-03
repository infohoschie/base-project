//
// Created by JBohn on 27.01.2026.
//

#include "timer.h"

#include <drivers/register_access.h>
#include <drivers/nvic.h>

#include <utils/Strings.h>

#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

#define MAX_NUMBER_OF_TIMERS 6
TimerDevice timers[MAX_NUMBER_OF_TIMERS];
size_t number_of_timers = 0;

TimerDevice * timer_init(uint8_t timer_id,
                        timer_mode mode, // Datatype definded in ENUM
                        timer_bitmode bitmode, // Datatype definded in ENUM
                        uint8_t prescaler)
{
  if (number_of_timers >= MAX_NUMBER_OF_TIMERS)
  {
    return NULL;
  }

  // Allocate memory in the Heap for timer
  TimerDevice * const timer = &timers[number_of_timers];
  ++number_of_timers;

  // Baseadress on timer_id (-> zugriff auf Struct über Zeiger)
  if (timer_id == 0){
    timer->base = TIMER0_BASE_ADRESS;
  }else  if (timer_id == 1) {
    timer->base = TIMER1_BASE_ADRESS;
  }

  timer->timer_id = timer_id;
  timer->mode = mode;
  timer->bitmode = bitmode;
  timer->prescaler = prescaler;

  register_write((uint32_t)(timer->base) + TIMER_STOP, 1);
  register_write((uint32_t)(timer->base) + TIMER_CLEAR, 1 );
  register_write((uint32_t)(timer->base) + TIMER_MODE, mode);
  register_write((uint32_t)(timer->base) + TIMER_BITMODE, bitmode );
  register_write((uint32_t)(timer->base) + TIMER_PRESCALER, prescaler);

  return timer;
}

void timer_start(TimerDevice * timer) {
  if (timer != NULL) {
    register_write(timer->base + TIMER_START, 1);
  }
}

void timer_stop(TimerDevice *timer) {
  if (timer != NULL){
    register_write(timer->base + TIMER_STOP, 1);
  }
}

void timer_clear(TimerDevice *timer) {
  if (timer != NULL){
    register_write(timer->base + TIMER_CLEAR, 1);
  }
}

void timer_capture(TimerDevice *timer, uint8_t cc_channel)
{
  if (timer != NULL){
    register_write(timer->base + TIMER_CAPTURE(cc_channel), 1);
  }
}

// Get the Current timer Counter Value
uint32_t timer_get_counter(TimerDevice *timer,uint8_t cc_channel){
  if (timer == NULL){
    return 0;
  }
  return register_read(timer->base + TIMER_CC(cc_channel));
}

// set a Comparevalue for a specific CC Channel (reaches from 0-5)
void timer_set_compare(TimerDevice *timer, uint8_t cc_channel ,uint32_t compare_value){
  if (timer != NULL && cc_channel <6)
  {
    register_write(timer->base + TIMER_CC(cc_channel), compare_value);
  }
}

// Calculates the adjusted frequency through prescaler
uint32_t timer_get_frequency(TimerDevice *timer)
{
  if (timer == NULL || timer->prescaler == 0){
    return 0;
  }
  return TIMER_CLOCK_HZ / timer-> prescaler;
}

bool timer_get_event( TimerDevice *timer, uint8_t cc_channel, bool reset )
{
  if (timer == NULL || cc_channel >= 6){
    return false;
  }

  const uint32_t event_register = register_read( timer->base + TIMER_EVENTS_COMPARE(cc_channel) );

  if ( reset )
  {
    register_write( timer->base + TIMER_EVENTS_COMPARE(cc_channel), 0 );
  }

  return event_register != 0 ;
}

void timer_trigger( TimerDevice *timer )
{
  if ( NULL != timer )
  {
    register_write( timer->base + TIMER_COUNT, 1 );
  }
}

void timer_set_clear_shortcut( TimerDevice * timer, uint8_t channel, bool enable )
{
  uint32_t shorts = register_read( timer->base + TIMER_SHORTS );

  shorts = ( shorts & ~( 1 << channel ) ) | ( ( enable ? 1 : 0 ) << channel );

  register_write( timer->base + TIMER_SHORTS, shorts );
}

void timer_set_stop_shortcut( TimerDevice * timer, uint8_t channel, bool enable )
{
  uint32_t shorts = register_read( timer->base + TIMER_SHORTS );

  shorts = ( shorts & ~( 1 << ( 8+ channel) ) ) | ( ( enable ? 1 : 0 ) << (8+channel) );

  register_write( timer->base + TIMER_SHORTS, shorts );
}
