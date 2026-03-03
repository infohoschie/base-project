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

void EGUnit_init( EGUnit unit );

void EGUnit_registerHandler( EGUnit unit, uint8_t event, EGHandler handler );

void EGUnit_trigger( EGUnit unit, uint8_t event );

#endif
