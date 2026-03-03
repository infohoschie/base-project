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

#include "nvic.h"

#include <drivers/register_access.h>

#include <stddef.h>

typedef struct EventGeneratorUnit
{
  EGHandler handler[ 16 ];
} EventGeneratorUnit;

EventGeneratorUnit eventGeneratorUnit[ EGUCount ];

void static EventGeneratorUnit_handle( EGUnit unit );

// Interrupt Handler for EGU0
void Interrupt20Handler( void )
{
  EventGeneratorUnit_handle( EGU0 );
}

// Interrupt Handler for EGU1
void Interrupt21Handler( void )
{
  EventGeneratorUnit_handle( EGU1 );
}

// Interrupt Handler for EGU2
void Interrupt22Handler( void )
{
  EventGeneratorUnit_handle( EGU2 );
}

// Interrupt Handler for EGU3
void Interrupt23Handler( void )
{
  EventGeneratorUnit_handle( EGU3 );
}

// Interrupt Handler for EGU4
void Interrupt24Handler( void )
{
  EventGeneratorUnit_handle( EGU4 );
}

// Interrupt Handler for EGU5
void Interrupt25Handler( void )
{
  EventGeneratorUnit_handle( EGU5 );
}

void EGUnit_init( EGUnit unit )
{
  // Enable Interrupt in NVIC (Depending on EGU)
  const uint8_t interruptSet = NVIC_INT_SET( 20 + unit );
  const uint8_t interruptBit = NVIC_INT_BIT( 20 + unit );

  register_write( NVIC_ISER_N( interruptSet ), 1U << interruptBit );
}

void EGUnit_registerHandler( EGUnit unit, uint8_t event, EGHandler handler )
{
  eventGeneratorUnit[ unit ].handler[ event ] = handler;

  if ( NULL != handler)
  {
    // Enable Event Interrupt
    register_write( EGU_OFFSET_N( unit ) | EGU_INTENSET, 1U << event );
  }
  else
  {
    // Disable Event Interrupt
    register_write( EGU_OFFSET_N( unit ) | EGU_INTENCLR, 1U << event );
  }
}

void EGUnit_trigger( EGUnit unit, uint8_t event )
{
  // Set Trigger Task
  register_write( EGU_OFFSET_N( unit ) | EGU_TASKS_TRIGGER_N( event ), 1U );
}

void static EventGeneratorUnit_handle( EGUnit unit )
{
  for ( uint8_t eventIndex = 0; eventIndex < 16; ++eventIndex )
  {
    if ( register_read( EGU_OFFSET_N( unit ) | EGU_EVENTS_TRIGGERED_N( eventIndex ) ) != 0 )
    {
      if ( NULL != eventGeneratorUnit[ unit ].handler[ eventIndex ] )
      {
        eventGeneratorUnit[ unit ].handler[ eventIndex ]();
      }
      register_write( EGU_OFFSET_N( unit ) | EGU_EVENTS_TRIGGERED_N( eventIndex ), 0 );
    }
  }

  const uint8_t interruptSet = NVIC_INT_SET( 20 + unit );
  const uint8_t interruptBit = NVIC_INT_BIT( 20 + unit );
  register_write( NVIC_ICPR_N( interruptSet ), 1U << interruptBit );
}
