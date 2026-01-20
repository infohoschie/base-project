// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Definiton of Module Random.
 **/

#include "random.h"

#include <drivers/register_access.h>

#include <stdint.h>

/**
 * @brief Enables the generation of random numbers
 *
 * This is done by writing a `1` to the `START_TASK` of the RNG peripheral.
 */
void rng_init( void )
{
  // Write a '1' to the Start Task, to start the generation of random numbers
  register_write( ( RNG_BASE_ADDRESS | RNG_START ), RNG_TASK_START );
}

uint8_t rng_getRandomValue( void )
{
  // Wait for Value Ready
  for (
    volatile uint32_t valueReady = register_read( ( RNG_BASE_ADDRESS | RNG_VALRDY ) );
    valueReady == 0U;
    valueReady = register_read( ( RNG_BASE_ADDRESS | RNG_VALRDY ) ) )
  {
  }

  register_write( ( RNG_BASE_ADDRESS | RNG_VALRDY ), 0 );

  // Read 32-Bit Register containing the RNG Value
  uint32_t randomValue = register_read( ( RNG_BASE_ADDRESS | RNG_VALUE ) );

  // its actual just 8-Bit, so cast it.
  return (uint8_t)randomValue;
}
