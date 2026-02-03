//
// Created by JBohn on 27.01.2026.
//

#ifndef DRIVER_TIMER_H
#define DRIVER_TIMER_H

#include <stdbool.h>
#include <stdint.h>

#define TIMER0_BASE_ADRESS 0x40008000
#define TIMER1_BASE_ADRESS 0x40009000

// Adress offset from base
#define TIMER_START     0x000
#define TIMER_STOP      0x004
#define TIMER_COUNT     0x008
#define TIMER_CLEAR     0x00C
#define TIMER_CAPTURE(n) (0x040 + (n) * 4) // Capture Regs 0...5, times 4 cause Register Width is 4
#define TIMER_SHORTS     0x200
#define TIMER_MODE      0x504
#define TIMER_BITMODE   0x508
#define TIMER_PRESCALER 0x510
#define TIMER_CC(n)     (0x540 + (n) * 4) // Capture Regs 0...5, times 4 cause Register Width is 4
#define TIMER_EVENTS_COMPARE(n) (0x140 + (n) * 4)

#define TIMER_CLOCK_HZ 16000000UL //  Unsigned Long

typedef enum {
  TIMER_MODE_TIMER = 0,
  TIMER_MODE_COUNT = 1
} timer_mode;

typedef enum{
  TIMER_BITMODE_16BIT = 0,
  TIMER_BITMODE_BITMODE_8BIT = 1,
  TIMER_BITMODE_BITMODE_24BIT = 2,
  TIMER_BITMODE_BITMODE_32BIT = 3
} timer_bitmode;

typedef struct{
  uint32_t base;
  uint8_t timer_id;
  timer_mode mode;
  timer_bitmode bitmode;
  uint8_t prescaler;
} TimerDevice;



TimerDevice* timer_init(uint8_t timer_id, // Timer 1...5
                        timer_mode mode, // TIMER OR COUNTER Mode Selecet
                        timer_bitmode bitmode, //Resolution in Bits
                        uint8_t prescaler); // Prescale Factor for adjusting the frequency

void timer_deinit(TimerDevice *timer);
void timer_start(TimerDevice *timer);
void timer_stop(TimerDevice *timer);
void timer_clear(TimerDevice *timer);
void timer_capture(TimerDevice *timer, uint8_t cc_channel);

uint32_t timer_get_counter(TimerDevice *timer, uint8_t cc_channel);
void timer_set_compare(TimerDevice *timer, uint8_t cc_channel, uint32_t value);

uint32_t timer_get_frequency(TimerDevice *timer);

bool timer_get_event( TimerDevice *timer, uint8_t cc_channel, bool reset );

void timer_trigger( TimerDevice *timer );

void timer_set_clear_shortcut( TimerDevice * timer, uint8_t channel, bool enable );

void timer_set_stop_shortcut( TimerDevice * timer, uint8_t channel, bool enable );

#endif //TIMER_H
