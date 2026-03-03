// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Declaration of Module Event Generator Unit (EGU).
 **/

#ifndef DRIVERS_EVENTGENERATORUNIT_H
#define DRIVERS_EVENTGENERATORUNIT_H

#include <stdint.h>

typedef enum EGUnit
{
  EGU0,
  EGU1,
  EGU2,
  EGU3,
  EGU4,
  EGU5,
  EGUCount
} EGUnit;

typedef void (*EGHandler)( void );

#define EGU0_OFFSET 0x40014000U
#define EGU1_OFFSET 0x40015000U
#define EGU2_OFFSET 0x40016000U
#define EGU3_OFFSET 0x40017000U
#define EGU4_OFFSET 0x40018000U
#define EGU5_OFFSET 0x40019000U

#define EGU_OFFSET_N( egu ) ( 0x40014000U  + ( egu  * 0x1000U ) )

#define EGU_TASKS_TRIGGER_N( event )    ( 0x000U + ( event  * 4U ) )
#define EGU_EVENTS_TRIGGERED_N( event ) ( 0x100U + ( event  * 4U ) )

#define EGU_INTEN     0x300U
#define EGU_INTENSET  0x304U
#define EGU_INTENCLR  0x308U

void EGUnit_init( EGUnit unit );

void EGUnit_registerHandler( EGUnit unit, uint8_t event, EGHandler handler );

void EGUnit_trigger( EGUnit unit, uint8_t event );

#endif
