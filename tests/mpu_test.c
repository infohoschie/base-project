// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief MPU Test Routines.
 **/

#include "mpu_test.h"

#include <drivers/mpu.h>

void mpu_test( UartDevice * const uart )
{
  MPUInfo info;
  MPU_getInfo( &info );

  uart_writeString( uart, "MPU separate: " );
  uart_writeString( uart, info.separate ? "yes\n" : "no\n" );
  uart_writeString( uart, "MPU # D-Regions: " );
  uart_writeNumber( uart, info.numberOfDRegions );
  uart_writeByte( uart, '\n' );
  uart_writeString( uart, "MPU # I-Regions: " );
  uart_writeNumber( uart, info.numberOfIRegions );
  uart_writeByte( uart, '\n' );

  for ( uint32_t i = 0; i < info.numberOfDRegions; ++i )
  {
    MPU_RegionConfig config;
    MPU_getRegion( i, &config );
    uart_writeString( uart, "MPU Regions: " );
    uart_writeNumber( uart, i );
    uart_writeByte( uart, '\n' );
    uart_writeString( uart, "Base Address: " );
    uart_writeNumber( uart, config.baseAddress );
    uart_writeByte( uart, '\n' );
    uart_writeString( uart, "AP: " );
    uart_writeNumber( uart, config.accessPermission );
    uart_writeByte( uart, '\n' );
    uart_writeString( uart, "XN: " );
    uart_writeString( uart, config.executeNever ? "yes\n" : "no\n" );
  }
}
