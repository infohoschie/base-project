/**
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * Thomas Vogt
 **/

#include "entry_c.h"

#include <stdint.h>

/**
 * @brief Zeros the BSS Section.
 **/
static void zeroBss( void );

/**
 * @brief Copies Data Section from Flash to RAM.
 **/
static void copyData( void );

__attribute__((used)) void entry_c( void )
{
  zeroBss();
  copyData();

  extern int main( void ); // TODO: make it better!!!

  main();

  // endless loop
  for (;;)
  {
  }
}
static void zeroBss( void )
{
  // Symbol is located on start of BSS Section
  extern uint32_t __bss_start__;
  // Symbol is located on end of BSS Section
  extern uint32_t __bss_end__;

  /* loop over BSS Section and set to Zero */
  for ( uint32_t * bssPos = &__bss_start__; bssPos < &__bss_end__; ++bssPos )
  {
    *bssPos = 0U;
  }
}

static void copyData( void )
{
  // Symbol is located on start of Data Section
  extern uint32_t __data_start__;
  // Symbol is located on end of Data Section
  extern uint32_t __data_end__;
  // Symbol is located on start of LMA Data Section located in Flash
  extern const uint32_t __data_start_rom__;

  // Source of Data (in Flash)
  uint32_t const * dataCopyPos = &__data_start_rom__;

  /* loop over Data Section and copy data from flash */
  for ( uint32_t * dataPos = &__data_start__; dataPos < &__data_end__; ++dataPos )
  {
    *dataPos = *dataCopyPos;
    ++dataCopyPos;
  }
}
