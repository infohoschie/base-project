// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Definition of Module Watchdog (WDT).
 **/

#include "Wdt.h"

#include <drivers/register_access.h>
#include <drivers/WdtRegisters.h>
#include <drivers/nvic.h>

void Wdt_initialise( const uint32_t crValue, const bool intEnable, const uint8_t enableReloadRequestRegister )
{
  register_write( WDT_BASE_ADDRESS | WDT_CRV_OFFSET, crValue );

  if ( intEnable )
  {
    register_write( WDT_BASE_ADDRESS | WDT_INTENSET_OFFSET, 1U );
    register_write( Interrupt_Set_Enable, Interrupt_ID16 );
  }

  uint32_t rrEnableValue = 0U;
  for ( uint8_t i = 0; i < enableReloadRequestRegister; ++i )
  {
    rrEnableValue |= ( 1U << i );
  }
  register_write( WDT_BASE_ADDRESS | WDT_RREN_OFFSET, rrEnableValue );
}

void Wdt_start( void )
{
  register_write( WDT_BASE_ADDRESS | WDT_TASKS_START_OFFSET, 1U );
}

void Wdt_reloadRequest( uint8_t reloadRequestRegister )
{
  register_write( WDT_BASE_ADDRESS | WDT_RR_OFFSET( reloadRequestRegister ), 0x6E524635U );
}
