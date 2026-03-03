// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author infohoschie
 *
 * @brief @todo Add brief description.
 **/

#ifndef DRIVERS_MPU_H
#define DRIVERS_MPU_H

#include <stdint.h>

typedef struct MPUInfo
{
  bool separate;
  uint8_t numberOfDRegions;
  uint8_t numberOfIRegions;
} MPUInfo;

typedef struct MPU_Attributes
{
  bool executeNever;
  uint8_t accessPermission;
} MPU_Attributes;

typedef struct MPU_RegionConfig
{
  uint32_t baseAddress;
  uint32_t size;
  uint8_t enable;
} MPU_RegionConfig;

void MPU_initialise( void );

void MPU_getInfo( MPUInfo *info );

void MPU_enable( void );

void MPU_setRegion( uint8_t regionIndex, MPU_RegionConfig const * config );

void MPU_getRegion( uint8_t regionIndex, MPU_RegionConfig * config );

#endif
