// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Definition of Module Strings.
 **/

#include "Strings.h"

#include <stddef.h>

/**
 * @brief Computes the number of decimal digits required to represent a given
 *   unsigned 32-bit integer.
 *
 * This function calculates the number of base-10 digits in the decimal
 * representation of the input number.
 * For example, the number 12345 has 5 decimal digits.
 *
 * @param[in] number
 *   The unsigned 32-bit integer for which the number of decimal digits is to be
 *   calculated.
 *
 * @return The number of decimal digits required to represent the input number.
 **/
static uint8_t Strings_numberOfDecDigits( uint32_t number );

/**
 * @brief Converts a single decimal digit into its character representation.
 *
 * This function receives a decimal digit (0-9) and returns its ASCII character
 * equivalent.
 * If the input digit is greater than 9, a placeholder character `X` is returned
 * as an error indicator.
 *
 * @param[in] digit
 *   The decimal digit to be converted.
 *   This value must be in the range 0-9 for valid conversion.
 *
 * @return The ASCII character representing the input digit, or `X` if the
 *   input digit is outside the valid range.
 **/
static char Strings_digitToChar( uint8_t digit );

void Strings_numberToString( char * const buffer, uint32_t number )
{
  if ( NULL == buffer )
  {
    return;
  }

  const uint8_t numberOfDigits = Strings_numberOfDecDigits( number );

  for ( uint8_t i = 0; i < numberOfDigits; ++i )
  {
    buffer[ numberOfDigits - 1 - i ] = Strings_digitToChar( number % 10 );
    number /= 10;
  }

  buffer[ numberOfDigits ] = '\0';
}

static uint8_t Strings_numberOfDecDigits( uint32_t number )
{
  uint8_t numberOfDigits = 1;

  while ( number > 9 )
  {
    number /= 10;
    ++numberOfDigits;
  }

  return numberOfDigits;
}

static char Strings_digitToChar( const uint8_t digit )
{
  if ( digit > 9 )
  {
    return 'X';
  }

  return '0' + digit;
}
