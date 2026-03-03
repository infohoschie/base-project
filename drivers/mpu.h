// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Declaration of Module MPU.
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

typedef struct MPU_RegionConfig
{
  uint32_t baseAddress;
  uint32_t size;
  uint8_t srdFlags;
  bool bFlag;
  bool cFlag;
  bool sFlag;
  uint8_t tex;
  uint8_t accessPermission;
  bool executeNever;
  bool enable;
} MPU_RegionConfig;

#define MPU_TYPE    0xE000ED90
#define MPU_CTRL    0xE000ED94
#define MPU_RNR     0xE000ED98
#define MPU_RBAR    0xE000ED9C
#define MPU_RASR    0xE000EDA0
#define MPU_RBAR_A1 0xE000EDA4
#define MPU_RASR_A1 0xE000EDA8
#define MPU_RBAR_A2 0xE000EDAC
#define MPU_RASR_A2 0xE000EDB0
#define MPU_RBAR_A3 0xE000EDB4
#define MPU_RASR_A3 0xE000EDB8

#define MPU_RASR_ENABLE_MASK 0x00000001U
#define MPU_RASR_SIZE_MASK   0x0000003EU
#define MPU_RASR_SIZE_SHIFT  1U
#define MPU_RASR_SRD_MASK    0x0000FF00U
#define MPU_RASR_SRD_SHIFT   8U
#define MPU_RASR_B_MASK      0x00010000U
#define MPU_RASR_B_SHIFT     16U
#define MPU_RASR_C_MASK      0x00020000U
#define MPU_RASR_C_SHIFT     17U
#define MPU_RASR_S_MASK      0x00040000U
#define MPU_RASR_S_SHIFT     18U
#define MPU_RASR_TEX_MASK    0x00780000U
#define MPU_RASR_TEX_SHIFT   19U
#define MPU_RASR_AP_MASK     0x07000000U
#define MPU_RASR_AP_SHIFT    24U
#define MPU_RASR_XN_MASK     0x10000000U
#define MPU_RASR_XN_SHIFT    28U

void MPU_initialise( void );

void MPU_getInfo( MPUInfo *info );

void MPU_enable( void );

void MPU_setRegion( uint8_t regionIndex, MPU_RegionConfig const * config );

void MPU_getRegion( uint8_t regionIndex, MPU_RegionConfig * config );

#endif
