// SPDX-License-Identifier: MPL-2.0
/**
 * @file
 * @copyright
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
 * If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 *
 * @author Thomas Vogt
 *
 * @brief Declaration of Module Strings.
 **/

#ifndef UTILS_STRINGS_H
#define UTILS_STRINGS_H

#include <stdint.h>

/**
 * Converts a 32-bit unsigned integer into a null-terminated decimal string.
 *
 * This function takes a 32-bit unsigned integer as input and converts it
 * into its equivalent decimal representation as a string.
 * The resulting string is stored in the provided buffer, which must be large
 * enough to hold the number and the null-terminator.
 * The conversion does not handle formatting such as padding or leading zeros.
 *
 * If the input buffer is NULL, the function performs no operation and
 * returns immediately.
 *
 * @param[out] buffer
 *   A non-null pointer to a character array where the resulting string will be
 *   stored.
 *   The caller must ensure that the buffer is adequately sized to hold the
 *   converted number plus the null-terminator.
 * @param[in] number
 *   The 32-bit unsigned integer to be converted into a string.
 **/
void Strings_numberToString( char * buffer, uint32_t number );

#endif
