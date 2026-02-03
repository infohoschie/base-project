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


TimerDevice * timer_init(uint8_t timer_id,
                        timer_mode mode, // Datatype definded in ENUM
                        timer_bitmode bitmode, // Datatype definded in ENUM
                        uint8_t prescaler)
{

  // Allocate memory in the Heap for timer
  TimerDevice *timer = (TimerDevice*)malloc(sizeof(TimerDevice));
  if (timer == NULL)
  {
    return NULL;
  }

  // Baseadress on timer_id (-> zugriff auf Struct über Zeiger)
  if (timer_id == 0){
    timer->base = (volatile uint32_t*)TIMER0_BASE_ADRESS;
  }else  if (timer_id == 1) {
    timer->base = (volatile uint32_t*)TIMER1_BASE_ADRESS;
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


void timer_deinit(TimerDevice *timer) {
  if (timer != NULL)
    timer_stop(timer);
    free(timer);      // free allocated Memory
}


void timer_start(TimerDevice *timer) {
  if (timer != NULL) {
    register_write((uint32_t)(timer->base) + TIMER_START, 1);
  }
}

void timer_stop(TimerDevice *timer) {
  if (timer != NULL){
    register_write((uint32_t)(timer->base) + TIMER_STOP, 1);
  }
}

void timer_clear(TimerDevice *timer) {
  if (timer != NULL){
    register_write((uint32_t)(timer->base) + TIMER_CLEAR, 1);
  }
}

// Get the Current timer Counter Value
uint32_t timer_get_counter(TimerDevice *timer){
  if (timer == NULL){
    return 0;
  }
  return register_read((uint32_t)(timer->base) + TIMER_CC(0));
}

// set a Comparevalue for a specific CC Channel (reaches from 0-5)
void timer_set_compare(TimerDevice *timer, uint8_t cc_channel ,uint32_t compare_value){
  if (timer != NULL && cc_channel <6)
  {
    register_write((uint32_t)(timer->base) + TIMER_CC(cc_channel), compare_value);
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
