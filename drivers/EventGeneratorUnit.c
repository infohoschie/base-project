// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Definition of Module Event Generator Unit (EGU).
 **/

#include "EventGeneratorUnit.h"

typedef struct EventGeneratorUnit
{
  EGHandler handler[ 16 ];
} EventGeneratorUnit;

EventGeneratorUnit eventGeneratorUnit[ EGUCount ];

void Interrupt20_Handler( void )
{

}

void Interrupt21_Handler( void )
{

}

void Interrupt22_Handler( void )
{

}

void Interrupt23_Handler( void )
{

}

void Interrupt24_Handler( void )
{

}

void Interrupt25_Handler( void )
{

}

void EGUnit_init( EGUnit unit )
{
  // Enable Interrupt in NVIC (Depending on EGU)
}

void EGUnit_registerHandler( EGUnit unit, uint8_t event, EGHandler handler )
{
  eventGeneratorUnit[ unit ].handler[ event ] = handler;

  // Enable Event Interrupt

}

void EGUnit_trigger( EGUnit unit, uint8_t event )
{
  // Set Trigger Task
}
