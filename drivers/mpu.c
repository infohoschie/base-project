// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Defintion of Module MPU.
 **/

#include "mpu.h"

#include <stddef.h>
#include <drivers/register_access.h>

void MPU_getInfo( MPUInfo *info )
{
  if (NULL == info)
  {
    return;
  }

  const uint32_t mpuType = register_read( MPU_TYPE );
  info->separate = ( mpuType & 0x1U ) != 0;
  info->numberOfDRegions = (uint8_t)( ( mpuType >> 8 ) & 0xFFU );
  info->numberOfIRegions = (uint8_t)( ( mpuType >> 16 ) & 0xFFU );
}

void MPU_getRegion( const uint8_t regionIndex, MPU_RegionConfig * const config )
{
  if (NULL == config)
  {
    return;
  }

  register_write( MPU_RNR, regionIndex );

  const uint32_t regionBaseAddressRegister = register_read( MPU_RBAR );
  config->baseAddress = regionBaseAddressRegister & 0xFFFFFFE0;

  const uint32_t regionAttributeStatusRegister = register_read( MPU_RASR );
  config->enable = ( regionAttributeStatusRegister & MPU_RASR_ENABLE_MASK ) != 0;
  config->size = (uint8_t)( ( regionAttributeStatusRegister & MPU_RASR_SIZE_MASK ) >> MPU_RASR_SIZE_SHIFT );
  config->srdFlags = (uint8_t)( ( regionAttributeStatusRegister & MPU_RASR_SRD_MASK ) >> MPU_RASR_SRD_SHIFT );
  config->bFlag = ( regionAttributeStatusRegister & MPU_RASR_B_MASK ) != 0;
  config->cFlag = ( regionAttributeStatusRegister & MPU_RASR_C_MASK ) != 0;
  config->sFlag = ( regionAttributeStatusRegister & MPU_RASR_S_MASK ) != 0;
  config->tex = (uint8_t)( ( regionAttributeStatusRegister & MPU_RASR_TEX_MASK ) >> MPU_RASR_TEX_SHIFT );
  config->accessPermission = (uint8_t)( ( regionAttributeStatusRegister & MPU_RASR_AP_MASK ) >> MPU_RASR_AP_SHIFT );
  config->executeNever = ( regionAttributeStatusRegister & MPU_RASR_XN_MASK ) != 0;
}
